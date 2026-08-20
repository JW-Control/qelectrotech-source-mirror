/*
	Copyright 2026 JW Control
	This file is part of the JW Control QElectroTech fork.

	QElectroTech is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.
*/

#include "diagram.h"
#include "diagramview.h"
#include "projectview.h"
#include "qetdiagrameditor.h"
#include "qetproject.h"

#include <algorithm>
#include <QAction>
#include <QApplication>
#include <QCoreApplication>
#include <QCryptographicHash>
#include <QDateTime>
#include <QDir>
#include <QDomDocument>
#include <QEvent>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QLabel>
#include <QMap>
#include <QMessageBox>
#include <QSaveFile>
#include <QSet>
#include <QStatusBar>
#include <QTextStream>
#include <QTimer>

namespace
{
	const QString kManifestSuffix = QStringLiteral(".jwqet.json");

	QString manifestForQet(const QString &qet_path)
	{
		return(qet_path + kManifestSuffix);
	}

	QString nowIso()
	{
		return(QDateTime::currentDateTime().toString(Qt::ISODate));
	}

	QString timestamp()
	{
		return(QDateTime::currentDateTime().toString(QStringLiteral("yyyyMMdd_HHmmss")));
	}

	QJsonObject readJson(const QString &path)
	{
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly))
			return(QJsonObject());

		QJsonParseError parse_error;
		const QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &parse_error);
		if (parse_error.error != QJsonParseError::NoError || !document.isObject())
			return(QJsonObject());
		return(document.object());
	}

	bool writeJson(const QString &path, const QJsonObject &payload, QString *error_message = nullptr)
	{
		if (!QDir().mkpath(QFileInfo(path).absolutePath()))
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo crear la carpeta interna:\n%1")
						.arg(QDir::toNativeSeparators(QFileInfo(path).absolutePath()));
			return(false);
		}

		QSaveFile file(path);
		if (!file.open(QIODevice::WriteOnly))
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo escribir:\n%1\n%2")
						.arg(QDir::toNativeSeparators(path), file.errorString());
			return(false);
		}
		file.write(QJsonDocument(payload).toJson(QJsonDocument::Indented));
		if (!file.commit())
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo finalizar la escritura:\n%1\n%2")
						.arg(QDir::toNativeSeparators(path), file.errorString());
			return(false);
		}
		return(true);
	}

	QString sha256File(const QString &path)
	{
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly))
			return(QString());
		QCryptographicHash hash(QCryptographicHash::Sha256);
		while (!file.atEnd())
			hash.addData(file.read(1024 * 1024));
		return(QString::fromLatin1(hash.result().toHex()));
	}

	QString workspaceFromPath(const QString &path)
	{
		if (path.isEmpty())
			return(QString());
		QDir directory = QFileInfo(path).absoluteDir();
		for (int level = 0; level < 18; ++level)
		{
			if (directory.exists(QStringLiteral("00_MASTER")) &&
				directory.exists(QStringLiteral("02_WORKING")))
				return(directory.absolutePath());
			if (!directory.cdUp())
				break;
		}
		return(QString());
	}

	QString hiddenRoot(const QString &workspace)
	{
		return(QDir(workspace).absoluteFilePath(QStringLiteral(".jwqet")));
	}

	QString relativeToWorkspace(const QString &path, const QString &workspace)
	{
		return(QDir::fromNativeSeparators(QDir(workspace).relativeFilePath(path)));
	}

	QString resolveMember(const QString &workspace,
			const QJsonObject &manifest,
			const QString &relative_field,
			const QString &absolute_field)
	{
		const QString relative = manifest.value(relative_field).toString().trimmed();
		if (!relative.isEmpty())
		{
			const QString candidate = QDir(workspace).absoluteFilePath(QDir::fromNativeSeparators(relative));
			if (QFileInfo::exists(candidate))
				return(QDir::cleanPath(candidate));
		}

		const QString stored = manifest.value(absolute_field).toString().trimmed();
		if (!stored.isEmpty())
		{
			const QString normalized = QDir::fromNativeSeparators(stored);
			const QStringList markers {
				QStringLiteral("00_MASTER"),
				QStringLiteral("01_BASELINES"),
				QStringLiteral("02_WORKING"),
				QStringLiteral("03_INCOMING"),
				QStringLiteral("04_PUBLISHED"),
				QStringLiteral("05_ARCHIVE"),
				QStringLiteral("06_LOGS"),
				QStringLiteral(".jwqet")
			};
			const QStringList parts = normalized.split('/', Qt::SkipEmptyParts);
			for (int index = 0; index < parts.size(); ++index)
			{
				if (!markers.contains(parts.at(index)))
					continue;
				const QString candidate = QDir(workspace).absoluteFilePath(parts.mid(index).join('/'));
				if (QFileInfo::exists(candidate))
					return(QDir::cleanPath(candidate));
			}
			if (QFileInfo::exists(stored))
				return(QFileInfo(stored).absoluteFilePath());
		}
		return(QString());
	}

	QStringList jsonStringList(const QJsonValue &value)
	{
		QStringList result;
		for (const QJsonValue &item : value.toArray())
			if (item.isString())
				result << item.toString();
		return(result);
	}

	QString friendlyFolios(const QStringList &keys)
	{
		QStringList result;
		for (const QString &key : keys)
		{
			if (key.startsWith(QStringLiteral("order:")))
				result << QObject::tr("Folio %1").arg(key.mid(6));
			else
				result << key;
		}
		return(result.join(QStringLiteral(", ")));
	}

	bool loadXml(const QString &path, QDomDocument *document, QString *error_message = nullptr)
	{
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly))
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo leer el proyecto:\n%1\n%2")
						.arg(QDir::toNativeSeparators(path), file.errorString());
			return(false);
		}
		QString xml_error;
		int line = 0;
		int column = 0;
		if (!document->setContent(&file, &xml_error, &line, &column))
		{
			if (error_message)
				*error_message = QObject::tr("XML inválido en %1:%2:%3\n%4")
						.arg(QDir::toNativeSeparators(path))
						.arg(line)
						.arg(column)
						.arg(xml_error);
			return(false);
		}
		return(true);
	}

	QString diagramKey(const QDomElement &diagram, int position)
	{
		const QString order = diagram.attribute(QStringLiteral("order")).trimmed();
		return(QStringLiteral("order:%1").arg(order.isEmpty() ? QString::number(position) : order));
	}

	QStringList folioKeysFromQet(const QString &path)
	{
		QDomDocument document;
		if (!loadXml(path, &document))
			return(QStringList());

		QStringList result;
		int position = 0;
		for (QDomNode node = document.documentElement().firstChild(); !node.isNull(); node = node.nextSibling())
		{
			if (!node.isElement() || node.toElement().tagName() != QStringLiteral("diagram"))
				continue;
			++position;
			result << diagramKey(node.toElement(), position);
		}
		return(result);
	}

	bool isIgnorableElement(const QDomElement &element)
	{
		const QString tag = element.tagName();
		if (tag == QStringLiteral("elementautonumfoliosequentials") ||
			tag == QStringLiteral("conductorautonumfoliosequentials"))
			return(true);
		if (tag == QStringLiteral("elementInformations") &&
			element.attributes().count() == 0 &&
			element.text().trimmed().isEmpty() &&
			element.firstChildElement().isNull())
			return(true);
		return(false);
	}

	void addCanonicalString(QCryptographicHash &hash, const QString &value)
	{
		const QByteArray data = value.toUtf8();
		hash.addData(QByteArray::number(data.size()));
		hash.addData(":", 1);
		hash.addData(data);
	}

	void addCanonicalElement(QCryptographicHash &hash, const QDomElement &element)
	{
		if (isIgnorableElement(element))
			return;

		addCanonicalString(hash, element.tagName());

		QStringList attribute_names;
		const QDomNamedNodeMap attributes = element.attributes();
		for (int index = 0; index < attributes.count(); ++index)
			attribute_names << attributes.item(index).nodeName();
		attribute_names.sort(Qt::CaseSensitive);
		for (const QString &name : attribute_names)
		{
			const QString value = element.attribute(name);
			// QET writes these explicit false defaults when saving some older files.
			// Treat missing and false as the same semantic value.
			if ((name == QStringLiteral("freezeNewElement") ||
				 name == QStringLiteral("freezeNewConductor")) &&
				value.compare(QStringLiteral("false"), Qt::CaseInsensitive) == 0)
				continue;
			addCanonicalString(hash, name);
			addCanonicalString(hash, value);
		}

		for (QDomNode node = element.firstChild(); !node.isNull(); node = node.nextSibling())
		{
			if (node.isElement())
			{
				addCanonicalElement(hash, node.toElement());
			}
			else if (node.isText() || node.isCDATASection())
			{
				QString text = node.nodeValue();
				text.replace(QStringLiteral("\r\n"), QStringLiteral("\n"));
				text.replace(QLatin1Char('\r'), QLatin1Char('\n'));
				if (!text.trimmed().isEmpty())
					addCanonicalString(hash, text);
			}
		}
	}

	QMap<QString, QByteArray> semanticDiagramFingerprints(const QString &path, QString *error_message = nullptr)
	{
		QDomDocument document;
		if (!loadXml(path, &document, error_message))
			return(QMap<QString, QByteArray>());

		QMap<QString, QByteArray> result;
		int position = 0;
		for (QDomNode node = document.documentElement().firstChild(); !node.isNull(); node = node.nextSibling())
		{
			if (!node.isElement() || node.toElement().tagName() != QStringLiteral("diagram"))
				continue;
			++position;
			QCryptographicHash hash(QCryptographicHash::Sha256);
			addCanonicalElement(hash, node.toElement());
			result.insert(diagramKey(node.toElement(), position), hash.result());
		}
		return(result);
	}

	QStringList changedReservedFolios(const QString &baseline,
			const QString &working,
			const QStringList &reserved,
			QString *error_message = nullptr)
	{
		const QMap<QString, QByteArray> base = semanticDiagramFingerprints(baseline, error_message);
		if (base.isEmpty() && error_message && !error_message->isEmpty())
			return(QStringList());
		const QMap<QString, QByteArray> work = semanticDiagramFingerprints(working, error_message);
		if (work.isEmpty() && error_message && !error_message->isEmpty())
			return(QStringList());

		QStringList changed;
		for (const QString &key : reserved)
		{
			if (!base.contains(key) || !work.contains(key) || base.value(key) != work.value(key))
				changed << key;
		}
		return(changed);
	}

	bool writeSanitizedIncoming(const QString &baseline,
			const QString &working,
			const QStringList &reserved,
			const QString &incoming,
			QString *error_message = nullptr)
	{
		QDomDocument base_document;
		QDomDocument work_document;
		if (!loadXml(baseline, &base_document, error_message) ||
			!loadXml(working, &work_document, error_message))
			return(false);

		QMap<QString, QDomElement> base_diagrams;
		int base_position = 0;
		for (QDomNode node = base_document.documentElement().firstChild(); !node.isNull(); node = node.nextSibling())
		{
			if (!node.isElement() || node.toElement().tagName() != QStringLiteral("diagram"))
				continue;
			++base_position;
			base_diagrams.insert(diagramKey(node.toElement(), base_position), node.toElement());
		}

		QSet<QString> work_keys;
		int work_position = 0;
		QDomElement work_root = work_document.documentElement();
		for (QDomNode node = work_root.firstChild(); !node.isNull(); )
		{
			QDomNode next = node.nextSibling();
			if (node.isElement() && node.toElement().tagName() == QStringLiteral("diagram"))
			{
				++work_position;
				const QString key = diagramKey(node.toElement(), work_position);
				work_keys.insert(key);
				if (!reserved.contains(key))
				{
					if (!base_diagrams.contains(key))
					{
						if (error_message)
							*error_message = QObject::tr("El folio no reservado %1 no existe en la baseline.")
									.arg(friendlyFolios(QStringList() << key));
						return(false);
					}
					const QDomNode replacement = work_document.importNode(base_diagrams.value(key), true);
					work_root.replaceChild(replacement, node);
				}
			}
			node = next;
		}

		for (auto it = base_diagrams.constBegin(); it != base_diagrams.constEnd(); ++it)
		{
			if (!reserved.contains(it.key()) && !work_keys.contains(it.key()))
			{
				if (error_message)
					*error_message = QObject::tr("Falta el folio protegido %1 en la copia de trabajo.")
							.arg(friendlyFolios(QStringList() << it.key()));
				return(false);
			}
		}

		if (!QDir().mkpath(QFileInfo(incoming).absolutePath()))
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo crear la carpeta de entrega:\n%1")
						.arg(QDir::toNativeSeparators(QFileInfo(incoming).absolutePath()));
			return(false);
		}

		QSaveFile file(incoming);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo preparar la entrega:\n%1\n%2")
						.arg(QDir::toNativeSeparators(incoming), file.errorString());
			return(false);
		}
		QTextStream stream(&file);
		work_document.save(stream, 4);
		stream.flush();
		if (!file.commit())
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo finalizar la entrega:\n%1")
						.arg(file.errorString());
			return(false);
		}
		return(true);
	}

	void safeSubmitWorkflow(QETDiagramEditor *editor)
	{
		ProjectView *project_view = editor ? editor->currentProjectView() : nullptr;
		if (!project_view || !project_view->project())
		{
			QMessageBox::information(editor, QObject::tr("Sin proyecto abierto"),
					QObject::tr("Abre primero una copia de trabajo colaborativa."));
			return;
		}

		const QString working_path = project_view->project()->filePath();
		const QString manifest_path = manifestForQet(working_path);
		if (!QFileInfo::exists(manifest_path))
		{
			QMessageBox::information(editor,
					QObject::tr("Proyecto no colaborativo"),
					QObject::tr("El proyecto activo no es una copia de trabajo colaborativa."));
			return;
		}

		QJsonObject manifest = readJson(manifest_path);
		if (manifest.value(QStringLiteral("workflow_version")).toInt() < 2)
		{
			editor->submitCollaborativeChanges();
			return;
		}

		const QString status = manifest.value(QStringLiteral("status")).toString();
		const QString user = manifest.value(QStringLiteral("user")).toString();
		if (status != QStringLiteral("checked_out"))
		{
			QMessageBox::information(editor,
					QObject::tr("Copia no editable"),
					status == QStringLiteral("submitted")
						? QObject::tr("El perfil %1 ya entregó cambios y está esperando publicación.").arg(user)
						: QObject::tr("Esta copia debe actualizarse desde el maestro antes de continuar."));
			return;
		}

		const QETResult saved = project_view->save();
		if (!saved.isOk())
		{
			editor->showError(saved);
			return;
		}
		QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);

		const QString workspace = workspaceFromPath(working_path);
		const QString baseline = resolveMember(workspace, manifest,
				QStringLiteral("baseline_relpath"), QStringLiteral("baseline_path"));
		if (workspace.isEmpty() || baseline.isEmpty())
		{
			QMessageBox::warning(editor,
					QObject::tr("No se pudo verificar la entrega"),
					QObject::tr("No se pudo resolver la baseline colaborativa de esta copia."));
			return;
		}

		const QStringList reserved = jsonStringList(manifest.value(QStringLiteral("reserved_folios")));
		QString error_message;
		const QStringList changed = changedReservedFolios(baseline, working_path, reserved, &error_message);
		if (!error_message.isEmpty())
		{
			QMessageBox::warning(editor, QObject::tr("No se pudo verificar la entrega"), error_message);
			return;
		}
		if (changed.isEmpty())
		{
			QMessageBox::information(editor,
					QObject::tr("Sin cambios en folios reservados"),
					QObject::tr("No se detectaron cambios de usuario en los folios reservados: %1")
						.arg(friendlyFolios(reserved)));
			return;
		}

		QString incoming = resolveMember(workspace, manifest,
				QStringLiteral("incoming_relpath"), QStringLiteral("incoming_path"));
		if (incoming.isEmpty())
		{
			const QString slug = manifest.value(QStringLiteral("user_slug")).toString();
			incoming = QDir(QDir(hiddenRoot(workspace)).absoluteFilePath(QStringLiteral("incoming/%1").arg(slug)))
					.absoluteFilePath(QFileInfo(working_path).fileName());
		}

		if (!writeSanitizedIncoming(baseline, working_path, reserved, incoming, &error_message))
		{
			QMessageBox::warning(editor, QObject::tr("No se pudieron sanear los folios protegidos"), error_message);
			return;
		}

		QJsonObject submitted = manifest;
		submitted.insert(QStringLiteral("status"), QStringLiteral("submitted"));
		submitted.insert(QStringLiteral("submitted_at"), nowIso());
		submitted.insert(QStringLiteral("incoming_path"), QFileInfo(incoming).absoluteFilePath());
		submitted.insert(QStringLiteral("incoming_relpath"), relativeToWorkspace(incoming, workspace));
		submitted.insert(QStringLiteral("working_sha256"), sha256File(working_path));
		submitted.insert(QStringLiteral("incoming_sha256"), sha256File(incoming));
		QJsonArray changed_array;
		for (const QString &folio : changed)
			changed_array.append(folio);
		submitted.insert(QStringLiteral("changed_folios"), changed_array);

		const QString incoming_manifest = manifestForQet(incoming);
		if (!writeJson(incoming_manifest, submitted, &error_message) ||
			!writeJson(manifest_path, submitted, &error_message))
		{
			QMessageBox::warning(editor, QObject::tr("No se pudieron registrar los cambios"), error_message);
			return;
		}

		const QString logs_dir = QDir(hiddenRoot(workspace)).absoluteFilePath(QStringLiteral("logs"));
		QJsonObject log = submitted;
		log.insert(QStringLiteral("manifest_path"), incoming_manifest);
		writeJson(QDir(logs_dir).absoluteFilePath(
				QStringLiteral("%1_submit_guard_%2.json")
					.arg(timestamp(), manifest.value(QStringLiteral("user_slug")).toString())), log);

		QMessageBox::information(editor,
				QObject::tr("Cambios entregados"),
				QObject::tr("Perfil: %1\nFolios entregados: %2\n\n"
				            "Los folios no reservados se restauraron automáticamente desde la baseline antes de preparar la entrega.")
					.arg(user, friendlyFolios(changed)));
	}

	QAction *findSubmitAction(QETDiagramEditor *editor)
	{
		for (QAction *action : editor->findChildren<QAction *>())
			if (action->text().contains(QStringLiteral("Entregar cambios colaborativos"), Qt::CaseInsensitive))
				return(action);
		return(nullptr);
	}

	void applyFolioGuard(QETDiagramEditor *editor, QAction *submit_action)
	{
		if (!editor)
			return;

		QETProject *project = editor->currentProject();
		ProjectView *project_view = editor->currentProjectView();
		if (!project || !project_view)
		{
			if (submit_action)
				submit_action->setEnabled(false);
			return;
		}

		const QString working_path = project->filePath();
		const QString manifest_path = manifestForQet(working_path);
		if (!QFileInfo::exists(manifest_path))
		{
			if (submit_action)
				submit_action->setEnabled(false);
			return;
		}

		const QJsonObject manifest = readJson(manifest_path);
		if (manifest.value(QStringLiteral("workflow_version")).toInt() < 2)
		{
			if (submit_action)
				submit_action->setEnabled(true);
			return;
		}

		const QString status = manifest.value(QStringLiteral("status")).toString();
		const QString user = manifest.value(QStringLiteral("user")).toString();
		const QStringList reserved = jsonStringList(manifest.value(QStringLiteral("reserved_folios")));
		const QStringList keys = folioKeysFromQet(working_path);
		const QList<DiagramView *> views = project_view->diagram_views();

		for (int index = 0; index < views.size(); ++index)
		{
			DiagramView *view = views.at(index);
			if (!view)
				continue;
			const QString key = index < keys.size()
					? keys.at(index)
					: QStringLiteral("order:%1").arg(index + 1);
			const bool locked = status != QStringLiteral("checked_out") || !reserved.contains(key);
			const bool was_locked = view->property("jw_collab_guard_locked").toBool();

			if (locked)
			{
				if (!was_locked || view->isInteractive())
					view->setVisualisationMode();
				view->setAcceptDrops(false);
				if (view->diagram())
					view->diagram()->clearSelection();
				view->setProperty("jw_collab_guard_locked", true);
				view->setToolTip(QObject::tr("Solo visualización: este folio no está reservado para %1.").arg(user));
			}
			else
			{
				if (was_locked)
					view->setSelectionMode();
				view->setAcceptDrops(true);
				view->setProperty("jw_collab_guard_locked", false);
				view->setToolTip(QString());
			}
		}

		if (submit_action)
			submit_action->setEnabled(status == QStringLiteral("checked_out"));

		DiagramView *current = project_view->currentDiagram();
		if (current)
		{
			const int index = views.indexOf(current);
			const QString key = index >= 0 && index < keys.size()
					? keys.at(index)
					: QStringLiteral("order:%1").arg(index + 1);
			const bool locked = current->property("jw_collab_guard_locked").toBool();
			if (QLabel *label = editor->findChild<QLabel *>(QStringLiteral("jwCollabStatusLabel")))
			{
				label->setText(QObject::tr("COLAB: %1 · %2 · %3")
						.arg(user,
							 friendlyFolios(QStringList() << key),
							 locked ? QObject::tr("SOLO LECTURA") : QObject::tr("EDITANDO")));
				label->show();
			}
		}
	}

	void installGuard(QETDiagramEditor *editor)
	{
		if (!editor || editor->property("jw_collab_folio_guard_installed").toBool())
			return;

		// jwcollabselection.cpp installs the profile/reservation workflow. Wait
		// until that module has rebound its actions, then make the guarded submit
		// handler the final connection.
		if (!editor->property("jw_collab_workflow_v2_installed").toBool())
		{
			QTimer::singleShot(200, editor, [editor]() { installGuard(editor); });
			return;
		}

		QAction *submit_action = findSubmitAction(editor);
		if (!submit_action)
		{
			QTimer::singleShot(200, editor, [editor]() { installGuard(editor); });
			return;
		}

		QObject::disconnect(submit_action, nullptr, nullptr, nullptr);
		QObject::connect(submit_action, &QAction::triggered, editor,
				[editor]() { safeSubmitWorkflow(editor); });
		submit_action->setStatusTip(QObject::tr("Entrega únicamente los folios reservados; los demás se protegen y restauran desde la baseline"));

		auto *timer = new QTimer(editor);
		timer->setInterval(150);
		QObject::connect(timer, &QTimer::timeout, editor,
				[editor, submit_action]() { applyFolioGuard(editor, submit_action); });
		timer->start();
		applyFolioGuard(editor, submit_action);

		editor->setProperty("jw_collab_folio_guard_installed", true);
	}

	class JwCollabGuardInstaller : public QObject
	{
		public:
			explicit JwCollabGuardInstaller(QObject *parent = nullptr) : QObject(parent) {}

		protected:
			bool eventFilter(QObject *watched, QEvent *event) override
			{
				if (event->type() == QEvent::Show)
				{
					if (auto *editor = qobject_cast<QETDiagramEditor *>(watched))
					{
						for (int delay : {250, 600, 1200})
							QTimer::singleShot(delay, editor, [editor]() { installGuard(editor); });
					}
				}
				return(QObject::eventFilter(watched, event));
			}
	};

	void installJwCollabGuard()
	{
		auto *installer = new JwCollabGuardInstaller(qApp);
		qApp->installEventFilter(installer);
	}
}

Q_COREAPP_STARTUP_FUNCTION(installJwCollabGuard)
