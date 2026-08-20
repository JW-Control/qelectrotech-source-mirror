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

#include <QApplication>
#include <QDir>
#include <QEvent>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QSettings>
#include <QTimer>

namespace
{
	const QString kManifestSuffix = QStringLiteral(".jwqet.json");

	QJsonObject readJson(const QString &path)
	{
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly))
			return {};

		QJsonParseError parse_error;
		const QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &parse_error);
		if (parse_error.error != QJsonParseError::NoError || !document.isObject())
			return {};
		return document.object();
	}

	bool isUsableCollaborativeWorkingCopy(const QString &path)
	{
		if (path.trimmed().isEmpty())
			return false;

		const QFileInfo qet_info(path);
		if (!qet_info.isFile() || qet_info.suffix().compare(QStringLiteral("qet"), Qt::CaseInsensitive) != 0)
			return false;

		const QString normalized = QDir::fromNativeSeparators(qet_info.absoluteFilePath());
		if (!normalized.contains(QStringLiteral("/02_WORKING/"), Qt::CaseInsensitive))
			return false;

		const QString manifest_path = qet_info.absoluteFilePath() + kManifestSuffix;
		if (!QFileInfo::exists(manifest_path))
			return false;

		const QJsonObject manifest = readJson(manifest_path);
		if (manifest.value(QStringLiteral("workflow_version")).toInt() < 2)
			return false;

		const QString status = manifest.value(QStringLiteral("status")).toString();
		return status == QStringLiteral("checked_out")
			|| status == QStringLiteral("submitted")
			|| status == QStringLiteral("refresh_required");
	}

	QString findLastCollaborativeWorkingCopy()
	{
		QSettings settings;

		// Prefer the explicit local pointer once this feature has run at least
		// once on this PC.
		const QString remembered = settings.value(
				QStringLiteral("jwcollab/last_working_path")).toString();
		if (isUsableCollaborativeWorkingCopy(remembered))
			return QFileInfo(remembered).absoluteFilePath();

		// Migration path for installations that predate the explicit pointer:
		// QET already stores project recents locally per PC. Pick the most recent
		// collaborative working copy, never a MASTER/PUBLISHED project.
		for (int index = 1; index <= 10; ++index)
		{
			const QString key = QStringLiteral("projects-recentfiles/file%1").arg(index);
			const QString candidate = settings.value(key).toString();
			if (isUsableCollaborativeWorkingCopy(candidate))
				return QFileInfo(candidate).absoluteFilePath();
		}
		return {};
	}

	void rememberWorkingCopy(const QString &path)
	{
		if (!isUsableCollaborativeWorkingCopy(path))
			return;
		QSettings settings;
		settings.setValue(QStringLiteral("jwcollab/last_working_path"),
				QFileInfo(path).absoluteFilePath());
		settings.sync();
	}

	void tryAutoResume(QETDiagramEditor *editor)
	{
		if (!editor || editor->property("jw_collab_auto_resume_tried").toBool())
			return;
		editor->setProperty("jw_collab_auto_resume_tried", true);

		QSettings settings;
		if (!settings.value(QStringLiteral("jwcollab/auto_resume_last_session"), true).toBool())
			return;

		// Respect explicit files passed on the command line and projects that
		// another startup path has already opened.
		if (editor->currentProject())
		{
			rememberWorkingCopy(editor->currentProject()->filePath());
			return;
		}

		const QString working_path = findLastCollaborativeWorkingCopy();
		if (working_path.isEmpty())
			return;

		if (editor->openAndAddProject(working_path))
			rememberWorkingCopy(working_path);
	}

	void observeActiveProject(QETDiagramEditor *editor)
	{
		if (!editor)
			return;
		if (editor->currentProject())
			rememberWorkingCopy(editor->currentProject()->filePath());
	}

	void installEditorAutoResume(QETDiagramEditor *editor)
	{
		if (!editor || editor->property("jw_collab_auto_resume_installed").toBool())
			return;
		editor->setProperty("jw_collab_auto_resume_installed", true);

		// Give QET's normal startup/open-files path time to finish first.
		QTimer::singleShot(450, editor, [editor]() { tryAutoResume(editor); });

		// Keep the local pointer current when the user deliberately switches to
		// another collaborative workspace/profile during the same QET session.
		auto *timer = new QTimer(editor);
		timer->setInterval(2500);
		QObject::connect(timer, &QTimer::timeout, editor,
				[editor]() { observeActiveProject(editor); });
		timer->start();
	}

	class JwAutoResumeInstaller : public QObject
	{
		public:
			explicit JwAutoResumeInstaller(QObject *parent = nullptr) : QObject(parent) {}

		protected:
			bool eventFilter(QObject *watched, QEvent *event) override
			{
				if (event->type() == QEvent::Show)
				{
					if (auto *editor = qobject_cast<QETDiagramEditor *>(watched))
						QTimer::singleShot(0, editor,
								[editor]() { installEditorAutoResume(editor); });
				}
				return QObject::eventFilter(watched, event);
			}
	};

	void installCollaborativeAutoResume()
	{
		if (!qApp)
			return;

		auto *installer = new JwAutoResumeInstaller(qApp);
		qApp->installEventFilter(installer);

		for (QWidget *widget : QApplication::topLevelWidgets())
			if (auto *editor = qobject_cast<QETDiagramEditor *>(widget))
				installEditorAutoResume(editor);
	}
}

Q_COREAPP_STARTUP_FUNCTION(installCollaborativeAutoResume)
