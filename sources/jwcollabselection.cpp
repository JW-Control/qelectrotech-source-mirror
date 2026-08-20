/*
	Copyright 2026 JW Control
	This file is part of the JW Control QElectroTech fork.

	QElectroTech is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.
*/

#include "qetdiagrameditor.h"
#include "qetproject.h"

#include <algorithm>
#include <QAction>
#include <QApplication>
#include <QCoreApplication>
#include <QDateTime>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDir>
#include <QEvent>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QLabel>
#include <QListWidget>
#include <QMenu>
#include <QMessageBox>
#include <QProcess>
#include <QPushButton>
#include <QStandardPaths>
#include <QStringList>
#include <QTimer>
#include <QVBoxLayout>

namespace
{
	struct JwDelivery
	{
		QString manifest_path;
		QString user;
		QDateTime submitted_at;
		QString file_name;
	};

	struct JwMergeResult
	{
		bool parsed = false;
		QJsonObject payload;
		QString error_message;
	};

	QString jwWorkspaceFromProject(const QString &project_path)
	{
		if (project_path.isEmpty())
			return(QString());
		QDir dir = QFileInfo(project_path).absoluteDir();
		for (int i = 0; i < 16; ++i)
		{
			if (dir.exists(QStringLiteral("03_INCOMING")) &&
				dir.exists(QStringLiteral("04_PUBLISHED")))
				return(dir.absolutePath());
			if (!dir.cdUp())
				break;
		}
		return(QString());
	}

	QJsonObject jwReadJson(const QString &path)
	{
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly))
			return(QJsonObject());
		QJsonParseError error;
		const QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &error);
		if (error.error != QJsonParseError::NoError || !document.isObject())
			return(QJsonObject());
		return(document.object());
	}

	QList<JwDelivery> jwLatestDeliveries(const QString &workspace_path)
	{
		QList<JwDelivery> deliveries;
		QDir incoming(QDir(workspace_path).absoluteFilePath(QStringLiteral("03_INCOMING")));
		if (!incoming.exists())
			return(deliveries);

		const QFileInfoList user_dirs = incoming.entryInfoList(
				QDir::Dirs | QDir::NoDotAndDotDot,
				QDir::Name | QDir::IgnoreCase);
		for (const QFileInfo &user_dir_info : user_dirs)
		{
			QDir user_dir(user_dir_info.absoluteFilePath());
			const QFileInfoList manifests = user_dir.entryInfoList(
					QStringList() << QStringLiteral("*.jwqet.json"),
					QDir::Files,
					QDir::Time);
			if (manifests.isEmpty())
				continue;

			const QFileInfo info = manifests.first();
			const QJsonObject json = jwReadJson(info.absoluteFilePath());
			JwDelivery delivery;
			delivery.manifest_path = info.absoluteFilePath();
			delivery.user = json.value(QStringLiteral("user")).toString().trimmed();
			if (delivery.user.isEmpty())
				delivery.user = user_dir_info.fileName();
			delivery.submitted_at = QDateTime::fromString(
					json.value(QStringLiteral("submitted_at")).toString(),
					Qt::ISODate);
			if (!delivery.submitted_at.isValid())
				delivery.submitted_at = info.lastModified();
			delivery.file_name = info.completeBaseName();
			deliveries << delivery;
		}

		std::sort(deliveries.begin(), deliveries.end(), [](const JwDelivery &a, const JwDelivery &b) {
			return(a.submitted_at > b.submitted_at);
		});
		return(deliveries);
	}

	QString jwFindPython()
	{
		const QString configured = qEnvironmentVariable("JW_QET_PYTHON").trimmed();
		if (!configured.isEmpty() && QFileInfo::exists(configured))
			return(QFileInfo(configured).absoluteFilePath());

		const QString app_dir = QCoreApplication::applicationDirPath();
		const QStringList candidates {
			QDir(app_dir).absoluteFilePath(QStringLiteral("python.exe")),
			QDir(app_dir).absoluteFilePath(QStringLiteral("python/python.exe")),
			QStringLiteral("C:/msys64/ucrt64/bin/python.exe")
		};
		for (const QString &candidate : candidates)
		{
			const QFileInfo info(candidate);
			if (info.exists() && info.isFile())
				return(info.absoluteFilePath());
		}
		for (const QString &name : {QStringLiteral("python.exe"), QStringLiteral("python3.exe"), QStringLiteral("python")})
		{
			const QString found = QStandardPaths::findExecutable(name);
			if (!found.isEmpty())
				return(found);
		}
		return(QString());
	}

	QString jwFindTool()
	{
		const QString app_dir = QCoreApplication::applicationDirPath();
		const QString current_dir = QDir::currentPath();
		const QStringList candidates {
			QDir(current_dir).absoluteFilePath(QStringLiteral("tools/qet_collab_session.py")),
			QDir(app_dir).absoluteFilePath(QStringLiteral("tools/qet_collab_session.py")),
			QDir(app_dir).absoluteFilePath(QStringLiteral("../tools/qet_collab_session.py")),
			QDir(app_dir).absoluteFilePath(QStringLiteral("../../tools/qet_collab_session.py")),
			QDir(app_dir).absoluteFilePath(QStringLiteral("../../../tools/qet_collab_session.py"))
		};
		for (const QString &candidate : candidates)
		{
			const QFileInfo info(QDir::cleanPath(candidate));
			if (info.exists() && info.isFile())
				return(info.absoluteFilePath());
		}
		return(QString());
	}

	QString jwOutputPath(const QString &workspace_path)
	{
		QString project_name = QStringLiteral("Proyecto");
		QDir master_dir(QDir(workspace_path).absoluteFilePath(QStringLiteral("00_MASTER")));
		const QFileInfoList masters = master_dir.entryInfoList(
				QStringList() << QStringLiteral("*.qet"), QDir::Files, QDir::Name);
		if (!masters.isEmpty())
			project_name = masters.first().completeBaseName();

		QDir published(QDir(workspace_path).absoluteFilePath(QStringLiteral("04_PUBLISHED")));
		QDir().mkpath(published.absolutePath());
		const QString stamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyyMMdd_HHmmss"));
		return(published.absoluteFilePath(QStringLiteral("%1_COLLAB_%2.qet").arg(project_name, stamp)));
	}

	JwMergeResult jwRunMerge(
			const QString &python,
			const QString &tool,
			const QStringList &manifests,
			const QString &output,
			bool dry_run)
	{
		JwMergeResult result;
		QStringList args;
		args << tool << QStringLiteral("merge") << QStringLiteral("--json");
		if (dry_run)
			args << QStringLiteral("--dry-run");
		else
			args << QStringLiteral("--force");
		args << QStringLiteral("--output") << output;
		args << manifests;

		QProcess process;
		process.setProcessChannelMode(QProcess::SeparateChannels);
		process.start(python, args);
		if (!process.waitForStarted(10000))
		{
			result.error_message = QObject::tr("No se pudo iniciar el motor colaborativo.\n%1").arg(process.errorString());
			return(result);
		}
		if (!process.waitForFinished(120000))
		{
			process.kill();
			process.waitForFinished(3000);
			result.error_message = QObject::tr("El análisis colaborativo excedió el tiempo de espera.");
			return(result);
		}

		const QByteArray out = process.readAllStandardOutput().trimmed();
		const QString err = QString::fromLocal8Bit(process.readAllStandardError()).trimmed();
		QJsonParseError parse_error;
		const QJsonDocument document = QJsonDocument::fromJson(out, &parse_error);
		if (parse_error.error == QJsonParseError::NoError && document.isObject())
		{
			result.parsed = true;
			result.payload = document.object();
			return(result);
		}

		result.error_message = QString::fromUtf8(out).trimmed();
		if (!err.isEmpty())
		{
			if (!result.error_message.isEmpty())
				result.error_message += QStringLiteral("\n");
			result.error_message += err;
		}
		return(result);
	}

	QStringList jwJsonStrings(const QJsonValue &value)
	{
		QStringList result;
		if (!value.isArray())
			return(result);
		for (const QJsonValue &item : value.toArray())
			if (item.isString())
				result << item.toString();
		return(result);
	}

	QString jwFriendlyFolios(const QStringList &keys)
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

	QString jwDetails(const QJsonObject &payload)
	{
		QStringList sections;
		const QStringList warnings = jwJsonStrings(payload.value(QStringLiteral("warnings")));
		const QStringList conflicts = jwJsonStrings(payload.value(QStringLiteral("conflicts")));
		if (!warnings.isEmpty())
			sections << QObject::tr("Advertencias:\n%1").arg(warnings.join(QStringLiteral("\n")));
		if (!conflicts.isEmpty())
			sections << QObject::tr("Conflictos:\n%1").arg(conflicts.join(QStringLiteral("\n")));
		return(sections.join(QStringLiteral("\n\n")));
	}

	QStringList jwSelectManifests(
			QWidget *parent,
			const QList<JwDelivery> &deliveries,
			bool *accepted)
	{
		if (accepted)
			*accepted = false;

		QDialog dialog(parent);
		dialog.setWindowTitle(QObject::tr("Seleccionar entregas colaborativas"));
		dialog.resize(690, 360);
		auto *layout = new QVBoxLayout(&dialog);
		auto *label = new QLabel(
				QObject::tr("Selecciona las entregas que pertenecen a esta publicación.\n"
				            "Se preseleccionó automáticamente la tanda más reciente; puedes cambiarla."),
				&dialog);
		label->setWordWrap(true);
		layout->addWidget(label);

		auto *list = new QListWidget(&dialog);
		list->setSelectionMode(QAbstractItemView::NoSelection);
		layout->addWidget(list, 1);

		QDateTime newest;
		for (const JwDelivery &delivery : deliveries)
			if (!newest.isValid() || delivery.submitted_at > newest)
				newest = delivery.submitted_at;

		for (const JwDelivery &delivery : deliveries)
		{
			const QString when = delivery.submitted_at.isValid()
					? delivery.submitted_at.toString(QStringLiteral("dd/MM/yyyy HH:mm"))
					: QObject::tr("fecha desconocida");
			auto *item = new QListWidgetItem(
					QStringLiteral("%1    —    %2    —    %3")
						.arg(delivery.user, when, QFileInfo(delivery.manifest_path).fileName()),
					list);
			item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
			bool recent = false;
			if (newest.isValid() && delivery.submitted_at.isValid())
				recent = delivery.submitted_at.secsTo(newest) <= 2 * 60 * 60;
			item->setCheckState(recent ? Qt::Checked : Qt::Unchecked);
			item->setData(Qt::UserRole, delivery.manifest_path);
			item->setToolTip(QDir::toNativeSeparators(delivery.manifest_path));
		}

		auto *hint = new QLabel(
				QObject::tr("Las entregas antiguas no se borran: simplemente quedan fuera de esta publicación."),
				&dialog);
		hint->setWordWrap(true);
		layout->addWidget(hint);

		auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
		buttons->button(QDialogButtonBox::Ok)->setText(QObject::tr("Analizar seleccionadas"));
		buttons->button(QDialogButtonBox::Cancel)->setText(QObject::tr("Cancelar"));
		QObject::connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
		QObject::connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
		layout->addWidget(buttons);

		while (dialog.exec() == QDialog::Accepted)
		{
			QStringList selected;
			for (int row = 0; row < list->count(); ++row)
			{
				QListWidgetItem *item = list->item(row);
				if (item->checkState() == Qt::Checked)
					selected << item->data(Qt::UserRole).toString();
			}
			if (!selected.isEmpty())
			{
				if (accepted)
					*accepted = true;
				return(selected);
			}
			QMessageBox::information(
					&dialog,
					QObject::tr("Sin entregas seleccionadas"),
					QObject::tr("Selecciona al menos una entrega para continuar."));
		}
		return(QStringList());
	}

	void jwPublishSelected(QETDiagramEditor *editor)
	{
		QString workspace_path;
		if (editor->currentProject())
			workspace_path = jwWorkspaceFromProject(editor->currentProject()->filePath());
		if (workspace_path.isEmpty())
			workspace_path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

		workspace_path = QFileDialog::getExistingDirectory(
				editor,
				QObject::tr("Seleccionar carpeta colaborativa para publicar"),
				workspace_path);
		if (workspace_path.isEmpty())
			return;

		QDir workspace(workspace_path);
		if (!workspace.exists(QStringLiteral("03_INCOMING")) ||
			!workspace.exists(QStringLiteral("04_PUBLISHED")))
		{
			QMessageBox::warning(editor,
					QObject::tr("Carpeta colaborativa no válida"),
					QObject::tr("La carpeta seleccionada no contiene 03_INCOMING y 04_PUBLISHED."));
			return;
		}

		const QList<JwDelivery> deliveries = jwLatestDeliveries(workspace_path);
		if (deliveries.isEmpty())
		{
			QMessageBox::information(editor,
					QObject::tr("Sin entregas"),
					QObject::tr("No se encontraron entregas en 03_INCOMING."));
			return;
		}

		const QString python = jwFindPython();
		const QString tool = jwFindTool();
		if (python.isEmpty() || tool.isEmpty())
		{
			QMessageBox::warning(editor,
					QObject::tr("Publicación colaborativa no disponible"),
					QObject::tr("No se encontró el motor colaborativo interno o Python."));
			return;
		}

		for (;;)
		{
			bool accepted = false;
			const QStringList manifests = jwSelectManifests(editor, deliveries, &accepted);
			if (!accepted)
				return;

			QStringList users;
			for (const QString &manifest : manifests)
			{
				const QJsonObject json = jwReadJson(manifest);
				QString user = json.value(QStringLiteral("user")).toString().trimmed();
				if (user.isEmpty())
					user = QFileInfo(manifest).dir().dirName();
				users << user;
			}

			const QString output = jwOutputPath(workspace_path);
			QApplication::setOverrideCursor(Qt::WaitCursor);
			const JwMergeResult dry = jwRunMerge(python, tool, manifests, output, true);
			QApplication::restoreOverrideCursor();
			if (!dry.parsed)
			{
				QMessageBox::warning(editor,
						QObject::tr("No se pudo analizar la publicación"), dry.error_message);
				return;
			}

			const QString details = jwDetails(dry.payload);
			if (!dry.payload.value(QStringLiteral("ok")).toBool(false))
			{
				QMessageBox conflict(QMessageBox::Warning,
						QObject::tr("Conflicto colaborativo detectado"),
						QObject::tr("Las entregas seleccionadas presentan un conflicto."),
						QMessageBox::NoButton,
						editor);
				conflict.setInformativeText(
						QObject::tr("Usuarios seleccionados: %1\n\nPuedes volver y cambiar la selección.")
							.arg(users.join(QStringLiteral(", "))));
				if (!details.isEmpty())
					conflict.setDetailedText(details);
				QPushButton *retry = conflict.addButton(QObject::tr("Cambiar selección"), QMessageBox::AcceptRole);
				conflict.addButton(QObject::tr("Cancelar"), QMessageBox::RejectRole);
				conflict.exec();
				if (conflict.clickedButton() == retry)
					continue;
				return;
			}

			const QStringList changed = jwJsonStrings(dry.payload.value(QStringLiteral("changed_diagrams")));
			QMessageBox confirm(QMessageBox::Question,
					QObject::tr("Publicar cambios colaborativos"),
					QObject::tr("El análisis colaborativo terminó correctamente."),
					QMessageBox::NoButton,
					editor);
			confirm.setInformativeText(
					QObject::tr("Entregas: %1\nFolios a publicar: %2\n\n¿Deseas generar el proyecto publicado?")
						.arg(users.join(QStringLiteral(", ")),
							 changed.isEmpty() ? QObject::tr("ninguno") : jwFriendlyFolios(changed)));
			if (!details.isEmpty())
				confirm.setDetailedText(details);
			QPushButton *publish_button = confirm.addButton(QObject::tr("Publicar"), QMessageBox::AcceptRole);
			confirm.addButton(QObject::tr("Cancelar"), QMessageBox::RejectRole);
			confirm.exec();
			if (confirm.clickedButton() != publish_button)
				return;

			QApplication::setOverrideCursor(Qt::WaitCursor);
			const JwMergeResult published = jwRunMerge(python, tool, manifests, output, false);
			QApplication::restoreOverrideCursor();
			if (!published.parsed || !published.payload.value(QStringLiteral("ok")).toBool(false))
			{
				QMessageBox message(QMessageBox::Warning,
						QObject::tr("No se pudo publicar"),
						QObject::tr("La publicación no pudo completarse."),
						QMessageBox::Ok,
						editor);
				const QString publish_details = published.parsed ? jwDetails(published.payload) : published.error_message;
				if (!publish_details.isEmpty())
					message.setDetailedText(publish_details);
				message.exec();
				return;
			}

			const QString published_path = published.payload.value(QStringLiteral("output")).toString(output);
			QMessageBox success(QMessageBox::Information,
					QObject::tr("Proyecto colaborativo publicado"),
					QObject::tr("Se generó correctamente el proyecto con las entregas seleccionadas."),
					QMessageBox::NoButton,
					editor);
			success.setInformativeText(QDir::toNativeSeparators(published_path));
			QPushButton *open_button = success.addButton(QObject::tr("Abrir proyecto publicado"), QMessageBox::AcceptRole);
			success.addButton(QObject::tr("Cerrar"), QMessageBox::RejectRole);
			success.exec();
			if (success.clickedButton() == open_button)
				editor->openAndAddProject(published_path);
			return;
		}
	}

	void jwReplacePublisherAction(QETDiagramEditor *editor)
	{
		if (!editor || editor->property("jw_collab_selection_installed").toBool())
			return;

		QAction *publish_action = nullptr;
		for (QAction *action : editor->findChildren<QAction *>())
		{
			if (action->text().contains(QStringLiteral("Publicar / fusionar cambios colaborativos"), Qt::CaseInsensitive))
			{
				publish_action = action;
				break;
			}
		}
		if (!publish_action)
			return;

		QObject::disconnect(publish_action, nullptr, nullptr, nullptr);
		QObject::connect(publish_action, &QAction::triggered, editor, [editor]() {
			jwPublishSelected(editor);
		});
		publish_action->setStatusTip(
				QObject::tr("Selecciona entregas, analiza conflictos y publica un proyecto colaborativo"));
		editor->setProperty("jw_collab_selection_installed", true);
	}

	class JwSelectionInstaller : public QObject
	{
		public:
			explicit JwSelectionInstaller(QObject *parent = nullptr) : QObject(parent) {}

		protected:
			bool eventFilter(QObject *watched, QEvent *event) override
			{
				if (event->type() == QEvent::Show)
				{
					if (auto *editor = qobject_cast<QETDiagramEditor *>(watched))
					{
						QTimer::singleShot(0, editor, [editor]() {
							jwReplacePublisherAction(editor);
							if (!editor->property("jw_collab_selection_installed").toBool())
								QTimer::singleShot(150, editor, [editor]() { jwReplacePublisherAction(editor); });
						});
					}
				}
				return(QObject::eventFilter(watched, event));
			}
	};

	void jwInstallSelectionPublisher()
	{
		auto *installer = new JwSelectionInstaller(qApp);
		qApp->installEventFilter(installer);
	}
}

Q_COREAPP_STARTUP_FUNCTION(jwInstallSelectionPublisher)
