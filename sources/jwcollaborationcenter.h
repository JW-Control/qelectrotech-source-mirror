/*
	Copyright 2026 JW Control
	This file is part of the JW Control QElectroTech fork.

	QElectroTech is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.
*/
#ifndef JW_COLLABORATION_CENTER_H
#define JW_COLLABORATION_CENTER_H

#include "qetapp.h"
#include "qetdiagrameditor.h"
#include "qetproject.h"
#include "projectview.h"

#include <algorithm>
#include <QAction>
#include <QCryptographicHash>
#include <QDateTime>
#include <QDir>
#include <QDirIterator>
#include <QDockWidget>
#include <QDomDocument>
#include <QFile>
#include <QFileInfo>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QLabel>
#include <QListWidget>
#include <QMap>
#include <QPointer>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>

namespace JWCollaborationCenter
{
	inline QString manifestForQet(const QString &qet_path)
	{
		return qet_path + QStringLiteral(".jwqet.json");
	}

	inline QString workspaceFromPath(const QString &path)
	{
		if (path.trimmed().isEmpty())
			return {};
		QDir directory = QFileInfo(path).absoluteDir();
		for (int level = 0; level < 18; ++level)
		{
			if (directory.exists(QStringLiteral("00_MASTER"))
					&& directory.exists(QStringLiteral("02_WORKING")))
				return directory.absolutePath();
			if (!directory.cdUp())
				break;
		}
		return {};
	}

	inline QString hiddenRoot(const QString &workspace)
	{
		return QDir(workspace).absoluteFilePath(QStringLiteral(".jwqet"));
	}

	inline QString masterPath(const QString &workspace)
	{
		QDir directory(QDir(workspace).absoluteFilePath(QStringLiteral("00_MASTER")));
		const QFileInfoList files = directory.entryInfoList(
				QStringList() << QStringLiteral("*.qet"), QDir::Files, QDir::Name);
		return files.isEmpty() ? QString() : files.first().absoluteFilePath();
	}

	inline QJsonObject readJson(const QString &path)
	{
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly))
			return {};
		QJsonParseError error;
		const QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &error);
		if (error.error != QJsonParseError::NoError || !document.isObject())
			return {};
		return document.object();
	}

	inline QString sha256File(const QString &path)
	{
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly))
			return {};
		QCryptographicHash hash(QCryptographicHash::Sha256);
		while (!file.atEnd())
			hash.addData(file.read(1024 * 1024));
		return QString::fromLatin1(hash.result().toHex());
	}

	inline QStringList stringArray(const QJsonValue &value)
	{
		QStringList result;
		for (const QJsonValue &entry : value.toArray())
		{
			const QString text = entry.toString().trimmed();
			if (!text.isEmpty())
				result << text;
		}
		return result;
	}

	inline QString compactFolio(const QString &key)
	{
		return key.startsWith(QStringLiteral("order:"), Qt::CaseInsensitive)
				? key.mid(QStringLiteral("order:").size()) : key;
	}

	inline QMap<QString, QString> folioLabels(const QString &qet_path)
	{
		QMap<QString, QString> labels;
		QFile file(qet_path);
		if (!file.open(QIODevice::ReadOnly))
			return labels;
		QDomDocument document;
		if (!document.setContent(&file))
			return labels;

		int position = 0;
		for (QDomNode node = document.documentElement().firstChild();
				 !node.isNull(); node = node.nextSibling())
		{
			if (!node.isElement() || node.toElement().tagName() != QStringLiteral("diagram"))
				continue;
			++position;
			const QDomElement diagram = node.toElement();
			const QString order = diagram.attribute(QStringLiteral("order"), QString::number(position));
			const QString title = diagram.attribute(QStringLiteral("title")).trimmed();
			const QString key = QStringLiteral("order:%1").arg(order);
			labels.insert(key, title.isEmpty()
					? QObject::tr("Folio %1").arg(order)
					: QObject::tr("Folio %1 — %2").arg(order, title));
		}
		return labels;
	}

	inline QString statusLabel(const QString &status)
	{
		if (status == QStringLiteral("checked_out"))
			return QObject::tr("EDITANDO");
		if (status == QStringLiteral("submitted"))
			return QObject::tr("ENTREGADO");
		if (status == QStringLiteral("refresh_required"))
			return QObject::tr("NUEVO MAESTRO DISPONIBLE");
		if (status.isEmpty())
			return QObject::tr("SIN SESIÓN");
		return status.toUpper();
	}

	struct DeliveryInfo
	{
		QString user;
		QString slug;
		QDateTime submitted_at;
		QString baseline_sha256;
		bool stale = false;
	};

	inline QList<DeliveryInfo> pendingDeliveries(const QString &workspace, const QString &master_hash)
	{
		QMap<QString, DeliveryInfo> latest;
		const QStringList roots {
			QDir(hiddenRoot(workspace)).absoluteFilePath(QStringLiteral("incoming")),
			QDir(workspace).absoluteFilePath(QStringLiteral("03_INCOMING"))
		};

		for (const QString &root : roots)
		{
			if (!QFileInfo(root).isDir())
				continue;
			QDirIterator iterator(root, QStringList() << QStringLiteral("*.json"),
					QDir::Files, QDirIterator::Subdirectories);
			while (iterator.hasNext())
			{
				const QString path = iterator.next();
				const QJsonObject json = readJson(path);
				if (json.value(QStringLiteral("status")).toString() != QStringLiteral("submitted"))
					continue;

				DeliveryInfo info;
				info.user = json.value(QStringLiteral("user")).toString().trimmed();
				info.slug = json.value(QStringLiteral("user_slug")).toString().trimmed();
				if (info.slug.isEmpty())
					info.slug = info.user;
				if (info.user.isEmpty())
					info.user = info.slug;
				info.submitted_at = QDateTime::fromString(
						json.value(QStringLiteral("submitted_at")).toString(), Qt::ISODate);
				if (!info.submitted_at.isValid())
					info.submitted_at = QFileInfo(path).lastModified();
				info.baseline_sha256 = json.value(QStringLiteral("baseline_sha256")).toString();
				info.stale = !master_hash.isEmpty() && !info.baseline_sha256.isEmpty()
						&& info.baseline_sha256 != master_hash;
				if (!latest.contains(info.slug)
						|| info.submitted_at > latest.value(info.slug).submitted_at)
					latest.insert(info.slug, info);
			}
		}

		QList<DeliveryInfo> result = latest.values();
		std::sort(result.begin(), result.end(), [](const DeliveryInfo &a, const DeliveryInfo &b) {
			return a.submitted_at > b.submitted_at;
		});
		return result;
	}

	class CenterWidget final : public QWidget
	{
		public:
			explicit CenterWidget(QETDiagramEditor *editor, QWidget *parent = nullptr)
				: QWidget(parent), m_editor(editor)
			{
				auto *layout = new QVBoxLayout(this);
				layout->setContentsMargins(8, 8, 8, 8);
				layout->setSpacing(8);

				auto *title = new QLabel(QStringLiteral("<b>%1</b>").arg(QObject::tr("Centro de colaboración")), this);
				title->setWordWrap(true);
				layout->addWidget(title);

				auto *session_group = new QGroupBox(QObject::tr("Sesión"), this);
				auto *session_layout = new QVBoxLayout(session_group);
				m_session = new QLabel(session_group);
				m_session->setWordWrap(true);
				m_session->setTextInteractionFlags(Qt::TextSelectableByMouse);
				session_layout->addWidget(m_session);
				layout->addWidget(session_group);

				m_folios = addListGroup(layout, QObject::tr("Mis folios"), 155);
				m_team = addListGroup(layout, QObject::tr("Equipo"), 125);
				m_deliveries = addListGroup(layout, QObject::tr("Entregas pendientes"), 115);

				auto *buttons = new QHBoxLayout();
				auto *refresh_button = new QPushButton(QObject::tr("Actualizar"), this);
				m_submit = new QPushButton(QObject::tr("Entregar cambios"), this);
				buttons->addWidget(refresh_button);
				buttons->addWidget(m_submit, 1);
				layout->addLayout(buttons);
				layout->addStretch(1);

				connect(refresh_button, &QPushButton::clicked, this, [this]() { refresh(); });
				connect(m_submit, &QPushButton::clicked, this, [this]() { triggerSubmit(); });

				m_timer.setInterval(2500);
				connect(&m_timer, &QTimer::timeout, this, [this]() { refresh(); });
				m_timer.start();
				refresh();
			}

		private:
			QListWidget *addListGroup(QVBoxLayout *layout, const QString &title, int max_height)
			{
				auto *group = new QGroupBox(title, this);
				auto *group_layout = new QVBoxLayout(group);
				auto *list = new QListWidget(group);
				list->setMaximumHeight(max_height);
				group_layout->addWidget(list);
				layout->addWidget(group);
				return list;
			}

			QAction *actionContaining(const QString &needle) const
			{
				if (!m_editor)
					return nullptr;
				for (QAction *action : m_editor->findChildren<QAction *>())
					if (action && action->text().contains(needle, Qt::CaseInsensitive))
						return action;
				return nullptr;
			}

			QETProject *contextProject()
			{
				if (!m_editor)
					return nullptr;

				// QMdiArea::activeSubWindow() becomes null while another desktop
				// window has focus. QETDiagramEditor::currentProject() therefore
				// temporarily returns null even though the project is still open.
				// Keep the last real project context instead of making the center
				// flicker to "No hay un proyecto abierto" every 2.5 seconds.
				if (QETProject *active = m_editor->currentProject())
				{
					m_last_project = active;
					return active;
				}

				if (m_last_project)
				{
					for (ProjectView *view : m_editor->openedProjects())
					{
						if (view && view->project() == m_last_project.data())
							return m_last_project.data();
					}
					m_last_project.clear();
				}

				// Startup fallback: if there is only one project open, there is no
				// ambiguity even when the MDI area has not reported it active yet.
				const QList<ProjectView *> opened = m_editor->openedProjects();
				if (opened.size() == 1 && opened.first() && opened.first()->project())
				{
					m_last_project = opened.first()->project();
					return m_last_project.data();
				}
				return nullptr;
			}

			void triggerSubmit()
			{
				// Trigger the menu action rather than calling QETDiagramEditor's
				// legacy slot directly. jwcollabselection rewires this QAction to
				// the protected v2 submit workflow (folio sanitation + guards).
				if (QAction *action = actionContaining(QStringLiteral("Entregar cambios colaborativos")))
					action->trigger();
				QTimer::singleShot(300, this, [this]() { refresh(); });
			}

			void refresh()
			{
				QETProject *project = contextProject();
				if (!project)
				{
					m_folios->clear();
					m_team->clear();
					m_deliveries->clear();
					m_submit->setEnabled(false);
					m_session->setText(QObject::tr("No hay un proyecto abierto."));
					return;
				}

				m_folios->clear();
				m_team->clear();
				m_deliveries->clear();
				m_submit->setEnabled(false);

				const QString qet_path = project->filePath();
				const QString workspace = workspaceFromPath(qet_path);
				if (workspace.isEmpty())
				{
					m_session->setText(QObject::tr("El proyecto actual no pertenece a un workspace colaborativo JW-QET."));
					return;
				}

				const QJsonObject manifest = readJson(manifestForQet(qet_path));
				const QString user = manifest.value(QStringLiteral("user")).toString().trimmed();
				const QString status = manifest.value(QStringLiteral("status")).toString().trimmed();
				const QString master_hash = sha256File(masterPath(workspace));
				const QString baseline_hash = manifest.value(QStringLiteral("baseline_sha256")).toString();
				const bool master_changed = !master_hash.isEmpty() && !baseline_hash.isEmpty()
						&& master_hash != baseline_hash;

				QString session_text = QObject::tr("<b>Proyecto:</b> %1").arg(QFileInfo(qet_path).fileName());
				if (!user.isEmpty())
					session_text += QObject::tr("<br><b>Perfil:</b> %1").arg(user.toHtmlEscaped());
				session_text += QObject::tr("<br><b>Estado:</b> %1").arg(statusLabel(status));
				session_text += QObject::tr("<br><b>Maestro:</b> %1")
						.arg(master_changed ? QObject::tr("ACTUALIZADO") : QObject::tr("ACTUAL"));
				m_session->setText(session_text);
				m_session->setToolTip(QDir::toNativeSeparators(workspace));

				const QMap<QString, QString> labels = folioLabels(qet_path);
				const QStringList reserved = stringArray(manifest.value(QStringLiteral("reserved_folios")));
				if (reserved.isEmpty())
					m_folios->addItem(QObject::tr("Sin folios reservados"));
				else
					for (const QString &key : reserved)
						m_folios->addItem(labels.value(key, key));

				QMap<QString, QString> profile_names;
				const QJsonObject registry = readJson(
						QDir(hiddenRoot(workspace)).absoluteFilePath(QStringLiteral("profiles.json")));
				for (const QJsonValue &value : registry.value(QStringLiteral("profiles")).toArray())
				{
					const QJsonObject entry = value.toObject();
					const QString slug = entry.value(QStringLiteral("slug")).toString().trimmed();
					const QString name = entry.value(QStringLiteral("name")).toString().trimmed();
					if (!slug.isEmpty())
						profile_names.insert(slug, name.isEmpty() ? slug : name);
				}

				const QJsonObject reservations = readJson(
						QDir(hiddenRoot(workspace)).absoluteFilePath(QStringLiteral("reservations.json")))
						.value(QStringLiteral("profiles")).toObject();
				for (auto it = reservations.begin(); it != reservations.end(); ++it)
				{
					const QJsonObject entry = it.value().toObject();
					const QString name = entry.value(QStringLiteral("user"))
							.toString(profile_names.value(it.key(), it.key()));
					profile_names.insert(it.key(), name);
				}

				if (profile_names.isEmpty())
					m_team->addItem(QObject::tr("Sin perfiles registrados"));
				else
				{
					for (auto it = profile_names.begin(); it != profile_names.end(); ++it)
					{
						const QJsonObject reservation = reservations.value(it.key()).toObject();
						const QStringList keys = stringArray(reservation.value(QStringLiteral("folios")));
						QStringList numbers;
						for (const QString &key : keys)
							numbers << compactFolio(key);
						const bool current = !user.isEmpty()
								&& it.value().compare(user, Qt::CaseInsensitive) == 0;
						const QString prefix = current ? QStringLiteral("● ") : QStringLiteral("○ ");
						const QString folios = numbers.isEmpty()
								? QObject::tr("sin reservas")
								: QObject::tr("folios %1").arg(numbers.join(QStringLiteral(", ")));
						m_team->addItem(prefix + it.value() + QStringLiteral(" — ") + folios);
					}
				}

				const QList<DeliveryInfo> deliveries = pendingDeliveries(workspace, master_hash);
				if (deliveries.isEmpty())
					m_deliveries->addItem(QObject::tr("Sin entregas pendientes"));
				else
				{
					for (const DeliveryInfo &delivery : deliveries)
					{
						QString text = QStringLiteral("%1 — %2")
								.arg(delivery.user,
									 delivery.submitted_at.toString(QStringLiteral("dd/MM HH:mm")));
						if (delivery.stale)
							text += QObject::tr(" — DESACTUALIZADA");
						m_deliveries->addItem(text);
					}
				}

				m_submit->setEnabled(status == QStringLiteral("checked_out")
						&& actionContaining(QStringLiteral("Entregar cambios colaborativos")));
			}

		private:
			QETDiagramEditor *m_editor = nullptr;
			QPointer<QETProject> m_last_project;
			QLabel *m_session = nullptr;
			QListWidget *m_folios = nullptr;
			QListWidget *m_team = nullptr;
			QListWidget *m_deliveries = nullptr;
			QPushButton *m_submit = nullptr;
			QTimer m_timer;
	};

	class Manager final : public QObject
	{
		public:
			explicit Manager(QObject *parent = nullptr) : QObject(parent)
			{
				m_timer.setInterval(900);
				connect(&m_timer, &QTimer::timeout, this, [this]() { ensureEditors(); });
				m_timer.start();
				QTimer::singleShot(0, this, [this]() { ensureEditors(); });
			}

		private:
			void ensureEditors()
			{
				for (QETDiagramEditor *editor : QETApp::diagramEditors())
				{
					if (!editor || editor->findChild<QDockWidget *>(QStringLiteral("jw_collaboration_center")))
						continue;

					auto *dock = new QDockWidget(QObject::tr("Colaboración"), editor);
					dock->setObjectName(QStringLiteral("jw_collaboration_center"));
					dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
					dock->setFeatures(QDockWidget::DockWidgetClosable
							| QDockWidget::DockWidgetMovable
							| QDockWidget::DockWidgetFloatable);
					dock->setMinimumWidth(230);
					dock->setWidget(new CenterWidget(editor, dock));
					dock->toggleViewAction()->setStatusTip(
						QObject::tr("Muestra u oculta el Centro de colaboración JW-QET"));

					editor->addDockWidget(Qt::LeftDockWidgetArea, dock);
					QDockWidget *projects = editor->findChild<QDockWidget *>(QStringLiteral("projects panel"));
					if (projects)
					{
						editor->tabifyDockWidget(projects, dock);
						projects->raise();
					}
					else if (QDockWidget *undo = editor->findChild<QDockWidget *>(QStringLiteral("diagram_undo")))
					{
						editor->tabifyDockWidget(undo, dock);
						undo->raise();
					}
				}
			}

		private:
			QTimer m_timer;
	};

	inline void install(QETApp *app)
	{
		if (!app || app->property("jw_collaboration_center_installed").toBool())
			return;
		new Manager(app);
		app->setProperty("jw_collaboration_center_installed", true);
	}
}

#endif // JW_COLLABORATION_CENTER_H
