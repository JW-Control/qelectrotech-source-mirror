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

#include <QAction>
#include <QApplication>
#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QEvent>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMenu>
#include <QMessageBox>
#include <QProcess>
#include <QPushButton>
#include <QStandardPaths>
#include <QStringList>

namespace
{
	QString jwCollabDetectWorkspace(const QString &project_path)
	{
		if (project_path.isEmpty())
			return(QString());

		QDir directory = QFileInfo(project_path).absoluteDir();
		for (int level = 0; level < 16; ++level)
		{
			if (directory.exists(QStringLiteral("03_INCOMING")) &&
				directory.exists(QStringLiteral("04_PUBLISHED")))
			{
				return(directory.absolutePath());
			}

			if (!directory.cdUp())
				break;
		}
		return(QString());
	}

	QString jwCollabFindSessionTool()
	{
		const QString application_dir = QCoreApplication::applicationDirPath();
		const QString current_dir = QDir::currentPath();
		const QStringList candidates {
			QDir(current_dir).absoluteFilePath(QStringLiteral("tools/qet_collab_session.py")),
			QDir(application_dir).absoluteFilePath(QStringLiteral("tools/qet_collab_session.py")),
			QDir(application_dir).absoluteFilePath(QStringLiteral("../tools/qet_collab_session.py")),
			QDir(application_dir).absoluteFilePath(QStringLiteral("../../tools/qet_collab_session.py")),
			QDir(application_dir).absoluteFilePath(QStringLiteral("../../../tools/qet_collab_session.py"))
		};

		for (const QString &candidate : candidates)
		{
			const QFileInfo info(QDir::cleanPath(candidate));
			if (info.exists() && info.isFile())
				return(info.absoluteFilePath());
		}
		return(QString());
	}

	QString jwCollabFindPython()
	{
		const QString configured = qEnvironmentVariable("JW_QET_PYTHON").trimmed();
		if (!configured.isEmpty() && QFileInfo::exists(configured))
			return(QFileInfo(configured).absoluteFilePath());

		const QString application_dir = QCoreApplication::applicationDirPath();
		const QStringList candidates {
			QDir(application_dir).absoluteFilePath(QStringLiteral("python.exe")),
			QDir(application_dir).absoluteFilePath(QStringLiteral("python/python.exe")),
			QStringLiteral("C:/msys64/ucrt64/bin/python.exe")
		};

		for (const QString &candidate : candidates)
		{
			const QFileInfo info(candidate);
			if (info.exists() && info.isFile())
				return(info.absoluteFilePath());
		}

		for (const QString &name : {QStringLiteral("python.exe"),
									 QStringLiteral("python3.exe"),
									 QStringLiteral("python3"),
									 QStringLiteral("python")})
		{
			const QString executable = QStandardPaths::findExecutable(name);
			if (!executable.isEmpty())
				return(executable);
		}
		return(QString());
	}

	QStringList jwCollabLatestIncomingManifests(const QString &workspace_path)
	{
		QStringList manifests;
		QDir incoming(QDir(workspace_path).absoluteFilePath(QStringLiteral("03_INCOMING")));
		if (!incoming.exists())
			return(manifests);

		const QFileInfoList user_directories = incoming.entryInfoList(
				QDir::Dirs | QDir::NoDotAndDotDot,
				QDir::Name | QDir::IgnoreCase);

		for (const QFileInfo &user_directory_info : user_directories)
		{
			QDir user_directory(user_directory_info.absoluteFilePath());
			const QFileInfoList candidates = user_directory.entryInfoList(
					QStringList() << QStringLiteral("*.jwqet.json"),
					QDir::Files,
					QDir::Time);
			if (!candidates.isEmpty())
				manifests << candidates.first().absoluteFilePath();
		}
		return(manifests);
	}

	QJsonObject jwCollabReadManifest(const QString &manifest_path)
	{
		QFile file(manifest_path);
		if (!file.open(QIODevice::ReadOnly))
			return(QJsonObject());
		QJsonParseError parse_error;
		const QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &parse_error);
		if (parse_error.error != QJsonParseError::NoError || !document.isObject())
			return(QJsonObject());
		return(document.object());
	}

	QString jwCollabUserForManifest(const QString &manifest_path)
	{
		const QJsonObject manifest = jwCollabReadManifest(manifest_path);
		const QString user = manifest.value(QStringLiteral("user")).toString().trimmed();
		if (!user.isEmpty())
			return(user);
		return(QFileInfo(manifest_path).dir().dirName());
	}

	QString jwCollabDefaultOutput(const QString &workspace_path)
	{
		QString project_name = QStringLiteral("Proyecto");
		QDir master_dir(QDir(workspace_path).absoluteFilePath(QStringLiteral("00_MASTER")));
		const QFileInfoList masters = master_dir.entryInfoList(
				QStringList() << QStringLiteral("*.qet"), QDir::Files, QDir::Name);
		if (!masters.isEmpty())
			project_name = masters.first().completeBaseName();

		const QString stamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyyMMdd_HHmmss"));
		QDir published_dir(QDir(workspace_path).absoluteFilePath(QStringLiteral("04_PUBLISHED")));
		if (!published_dir.exists())
			QDir().mkpath(published_dir.absolutePath());

		QString output = published_dir.absoluteFilePath(
				QStringLiteral("%1_COLLAB_%2.qet").arg(project_name, stamp));
		if (!QFileInfo::exists(output))
			return(output);

		const QFileInfo output_info(output);
		for (int index = 2; index < 1000; ++index)
		{
			const QString candidate = output_info.dir().absoluteFilePath(
					QStringLiteral("%1-%2.%3")
						.arg(output_info.completeBaseName())
						.arg(index)
						.arg(output_info.suffix()));
			if (!QFileInfo::exists(candidate))
				return(candidate);
		}
		return(output);
	}

	QStringList jwCollabJsonStrings(const QJsonValue &value)
	{
		QStringList values;
		if (!value.isArray())
			return(values);
		for (const QJsonValue &item : value.toArray())
		{
			if (item.isString())
				values << item.toString();
		}
		return(values);
	}

	QString jwCollabFriendlyDiagramList(const QStringList &keys)
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

	struct JwCollabProcessResult
	{
		bool parsed = false;
		int exit_code = -1;
		QJsonObject payload;
		QString error_message;
	};

	JwCollabProcessResult jwCollabRunMerge(
			const QString &python,
			const QString &tool,
			const QStringList &manifests,
			const QString &output_path,
			bool dry_run)
	{
		JwCollabProcessResult result;
		QStringList arguments;
		arguments << tool
				  << QStringLiteral("merge")
				  << QStringLiteral("--json");
		if (dry_run)
			arguments << QStringLiteral("--dry-run");
		else
			arguments << QStringLiteral("--force");
		arguments << QStringLiteral("--output") << output_path;
		arguments << manifests;

		QProcess process;
		process.setProcessChannelMode(QProcess::SeparateChannels);
		process.start(python, arguments);
		if (!process.waitForStarted(10000))
		{
			result.error_message = QObject::tr("No se pudo iniciar la herramienta colaborativa interna.\n%1")
					.arg(process.errorString());
			return(result);
		}
		if (!process.waitForFinished(120000))
		{
			process.kill();
			process.waitForFinished(3000);
			result.error_message = QObject::tr("La publicación colaborativa excedió el tiempo de espera.");
			return(result);
		}

		result.exit_code = process.exitCode();
		const QByteArray stdout_data = process.readAllStandardOutput().trimmed();
		const QString stderr_text = QString::fromLocal8Bit(process.readAllStandardError()).trimmed();

		QJsonParseError parse_error;
		const QJsonDocument document = QJsonDocument::fromJson(stdout_data, &parse_error);
		if (parse_error.error == QJsonParseError::NoError && document.isObject())
		{
			result.parsed = true;
			result.payload = document.object();
			return(result);
		}

		QString details = QString::fromUtf8(stdout_data).trimmed();
		if (!stderr_text.isEmpty())
		{
			if (!details.isEmpty())
				details += QStringLiteral("\n");
			details += stderr_text;
		}
		result.error_message = details.isEmpty()
				? QObject::tr("La herramienta colaborativa terminó sin devolver un resultado válido.")
				: details;
		return(result);
	}

	QString jwCollabTechnicalDetails(const QJsonObject &payload)
	{
		QStringList sections;
		const QStringList warnings = jwCollabJsonStrings(payload.value(QStringLiteral("warnings")));
		const QStringList conflicts = jwCollabJsonStrings(payload.value(QStringLiteral("conflicts")));
		if (!warnings.isEmpty())
			sections << QObject::tr("Advertencias:\n%1").arg(warnings.join(QStringLiteral("\n")));
		if (!conflicts.isEmpty())
			sections << QObject::tr("Conflictos:\n%1").arg(conflicts.join(QStringLiteral("\n")));
		return(sections.join(QStringLiteral("\n\n")));
	}

	void jwCollabPublish(QETDiagramEditor *editor)
	{
		QString default_workspace;
		if (editor->currentProject())
			default_workspace = jwCollabDetectWorkspace(editor->currentProject()->filePath());
		if (default_workspace.isEmpty())
			default_workspace = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

		const QString workspace_path = QFileDialog::getExistingDirectory(
				editor,
				QObject::tr("Seleccionar carpeta colaborativa para publicar"),
				default_workspace);
		if (workspace_path.isEmpty())
			return;

		QDir workspace(workspace_path);
		if (!workspace.exists(QStringLiteral("03_INCOMING")) ||
			!workspace.exists(QStringLiteral("04_PUBLISHED")))
		{
			QMessageBox::warning(
					editor,
					QObject::tr("Carpeta colaborativa no válida"),
					QObject::tr("La carpeta seleccionada no contiene 03_INCOMING y 04_PUBLISHED."));
			return;
		}

		const QStringList manifests = jwCollabLatestIncomingManifests(workspace_path);
		if (manifests.isEmpty())
		{
			QMessageBox::information(
					editor,
					QObject::tr("Sin entregas pendientes"),
					QObject::tr("No se encontraron entregas colaborativas en 03_INCOMING."));
			return;
		}

		QStringList users;
		for (const QString &manifest : manifests)
			users << jwCollabUserForManifest(manifest);

		const QString python = jwCollabFindPython();
		const QString tool = jwCollabFindSessionTool();
		if (python.isEmpty() || tool.isEmpty())
		{
			QString missing;
			if (python.isEmpty())
				missing += QObject::tr("No se encontró Python para la herramienta colaborativa interna.\n");
			if (tool.isEmpty())
				missing += QObject::tr("No se encontró tools/qet_collab_session.py.\n");
			QMessageBox::warning(
					editor,
					QObject::tr("Publicación colaborativa no disponible"),
					missing.trimmed());
			return;
		}

		const QString output_path = jwCollabDefaultOutput(workspace_path);
		QApplication::setOverrideCursor(Qt::WaitCursor);
		const JwCollabProcessResult dry_run = jwCollabRunMerge(
				python, tool, manifests, output_path, true);
		QApplication::restoreOverrideCursor();

		if (!dry_run.parsed)
		{
			QMessageBox::warning(
					editor,
					QObject::tr("No se pudo analizar la publicación"),
					dry_run.error_message);
			return;
		}

		const bool can_publish = dry_run.payload.value(QStringLiteral("ok")).toBool(false);
		const QStringList changed = jwCollabJsonStrings(
				dry_run.payload.value(QStringLiteral("changed_diagrams")));
		const QString details = jwCollabTechnicalDetails(dry_run.payload);

		if (!can_publish)
		{
			QMessageBox message(QMessageBox::Warning,
					QObject::tr("Conflicto colaborativo detectado"),
					QObject::tr("No se generó ningún proyecto porque las entregas presentan un conflicto."),
					QMessageBox::Ok,
					editor);
			message.setInformativeText(QObject::tr("Usuarios detectados: %1").arg(users.join(QStringLiteral(", "))));
			if (!details.isEmpty())
				message.setDetailedText(details);
			message.exec();
			return;
		}

		QMessageBox confirmation(QMessageBox::Question,
				QObject::tr("Publicar cambios colaborativos"),
				QObject::tr("El análisis colaborativo terminó correctamente."),
				QMessageBox::NoButton,
				editor);
		confirmation.setInformativeText(
				QObject::tr("Entregas: %1\nFolios a publicar: %2\n\n¿Deseas generar el proyecto publicado?")
					.arg(users.join(QStringLiteral(", ")),
						 changed.isEmpty() ? QObject::tr("ninguno") : jwCollabFriendlyDiagramList(changed)));
		if (!details.isEmpty())
			confirmation.setDetailedText(details);
		QPushButton *publish_button = confirmation.addButton(QObject::tr("Publicar"), QMessageBox::AcceptRole);
		confirmation.addButton(QObject::tr("Cancelar"), QMessageBox::RejectRole);
		confirmation.exec();
		if (confirmation.clickedButton() != publish_button)
			return;

		QApplication::setOverrideCursor(Qt::WaitCursor);
		const JwCollabProcessResult publish = jwCollabRunMerge(
				python, tool, manifests, output_path, false);
		QApplication::restoreOverrideCursor();

		if (!publish.parsed || !publish.payload.value(QStringLiteral("ok")).toBool(false))
		{
			const QString publish_details = publish.parsed
					? jwCollabTechnicalDetails(publish.payload)
					: publish.error_message;
			QMessageBox message(QMessageBox::Warning,
					QObject::tr("No se pudo publicar"),
					QObject::tr("La publicación colaborativa no pudo completarse."),
					QMessageBox::Ok,
					editor);
			if (!publish_details.isEmpty())
				message.setDetailedText(publish_details);
			message.exec();
			return;
		}

		const QString published_path = publish.payload.value(QStringLiteral("output")).toString(output_path);
		QMessageBox success(QMessageBox::Information,
				QObject::tr("Proyecto colaborativo publicado"),
				QObject::tr("Se generó correctamente el proyecto con los cambios de todas las entregas."),
				QMessageBox::NoButton,
				editor);
		success.setInformativeText(QDir::toNativeSeparators(published_path));
		QPushButton *open_button = success.addButton(QObject::tr("Abrir proyecto publicado"), QMessageBox::AcceptRole);
		success.addButton(QObject::tr("Cerrar"), QMessageBox::RejectRole);
		success.exec();
		if (success.clickedButton() == open_button)
			editor->openAndAddProject(published_path);
	}

	class JwCollabPublisherInstaller : public QObject
	{
		public:
			explicit JwCollabPublisherInstaller(QObject *parent = nullptr) : QObject(parent) {}

		protected:
			bool eventFilter(QObject *watched, QEvent *event) override
			{
				if (event->type() == QEvent::Show)
				{
					if (auto *editor = qobject_cast<QETDiagramEditor *>(watched))
						installForEditor(editor);
				}
				return(QObject::eventFilter(watched, event));
			}

		private:
			void installForEditor(QETDiagramEditor *editor)
			{
				if (editor->property("jw_collab_publish_installed").toBool())
					return;

				QAction *submit_action = nullptr;
				for (QAction *action : editor->findChildren<QAction *>())
				{
					if (action->text().contains(QStringLiteral("Entregar cambios colaborativos"), Qt::CaseInsensitive))
					{
						submit_action = action;
						break;
					}
				}
				if (!submit_action)
					return;

				QMenu *file_menu = nullptr;
				for (QMenu *menu : editor->findChildren<QMenu *>())
				{
					if (menu->actions().contains(submit_action))
					{
						file_menu = menu;
						break;
					}
				}
				if (!file_menu)
					return;

				auto *publish_action = new QAction(
						submit_action->icon(),
						QObject::tr("Publicar / fusionar cambios colaborativos..."),
						editor);
				publish_action->setStatusTip(
						QObject::tr("Analiza las entregas colaborativas y genera un proyecto publicado sin conflictos"));
				QObject::connect(publish_action, &QAction::triggered, editor, [editor]() {
					jwCollabPublish(editor);
				});

				const QList<QAction *> actions = file_menu->actions();
				const int submit_index = actions.indexOf(submit_action);
				if (submit_index >= 0 && submit_index + 1 < actions.size())
					file_menu->insertAction(actions.at(submit_index + 1), publish_action);
				else
					file_menu->addAction(publish_action);

				editor->setProperty("jw_collab_publish_installed", true);
			}
	};

	void jwInstallCollabPublisher()
	{
		auto *installer = new JwCollabPublisherInstaller(qApp);
		qApp->installEventFilter(installer);
	}
}

Q_COREAPP_STARTUP_FUNCTION(jwInstallCollabPublisher)
