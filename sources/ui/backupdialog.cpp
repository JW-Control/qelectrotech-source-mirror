/*
	Copyright 2006-2026 The QElectroTech Team
	This file is part of QElectroTech.

	QElectroTech is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	QElectroTech is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with QElectroTech.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "backupdialog.h"
#include "../qetapp.h"
#include "../qetdiagrameditor.h"
#include "../qetproject.h"

#include <QApplication>
#include <QDir>
#include <QEvent>
#include <QFile>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QLabel>
#include <QPushButton>
#include <QSettings>
#include <QTimer>
#include <QVBoxLayout>

namespace
{
	const QString jwAutoResumeManifestSuffix = QStringLiteral(".jwqet.json");

	QJsonObject jwAutoResumeReadJson(const QString &path)
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

	bool jwAutoResumeIsWorkingCopy(const QString &path)
	{
		if (path.trimmed().isEmpty())
			return false;

		const QFileInfo qet_info(path);
		if (!qet_info.isFile() || qet_info.suffix().compare(QStringLiteral("qet"), Qt::CaseInsensitive) != 0)
			return false;

		const QString normalized = QDir::fromNativeSeparators(qet_info.absoluteFilePath());
		if (!normalized.contains(QStringLiteral("/02_WORKING/"), Qt::CaseInsensitive))
			return false;

		const QString manifest_path = qet_info.absoluteFilePath() + jwAutoResumeManifestSuffix;
		if (!QFileInfo::exists(manifest_path))
			return false;

		const QJsonObject manifest = jwAutoResumeReadJson(manifest_path);
		if (manifest.value(QStringLiteral("workflow_version")).toInt() < 2)
			return false;

		const QString status = manifest.value(QStringLiteral("status")).toString();
		return status == QStringLiteral("checked_out")
			|| status == QStringLiteral("submitted")
			|| status == QStringLiteral("refresh_required");
	}

	QString jwAutoResumeLastWorkingCopy()
	{
		QSettings settings;
		const QString remembered = settings.value(
				QStringLiteral("jwcollab/last_working_path")).toString();
		if (jwAutoResumeIsWorkingCopy(remembered))
			return QFileInfo(remembered).absoluteFilePath();

		// Migration path: older builds only stored QET's normal recent-project
		// list. Scan it and select the most recent collaborative WORKING copy.
		for (int index = 1; index <= 10; ++index)
		{
			const QString candidate = settings.value(
					QStringLiteral("projects-recentfiles/file%1").arg(index)).toString();
			if (jwAutoResumeIsWorkingCopy(candidate))
				return QFileInfo(candidate).absoluteFilePath();
		}
		return {};
	}

	void jwAutoResumeRemember(const QString &path)
	{
		if (!jwAutoResumeIsWorkingCopy(path))
			return;
		QSettings settings;
		settings.setValue(QStringLiteral("jwcollab/last_working_path"),
				QFileInfo(path).absoluteFilePath());
		settings.sync();
	}

	void jwAutoResumeTry(QETDiagramEditor *editor)
	{
		if (!editor || editor->property("jw_collab_auto_resume_tried").toBool())
			return;
		editor->setProperty("jw_collab_auto_resume_tried", true);

		QSettings settings;
		if (!settings.value(QStringLiteral("jwcollab/auto_resume_last_session"), true).toBool())
			return;

		// Never override a project explicitly opened by the user or through the
		// command line.
		if (editor->currentProject())
		{
			jwAutoResumeRemember(editor->currentProject()->filePath());
			return;
		}

		const QString working_path = jwAutoResumeLastWorkingCopy();
		if (working_path.isEmpty())
			return;

		if (editor->openAndAddProject(working_path))
			jwAutoResumeRemember(working_path);
	}

	void jwAutoResumeObserve(QETDiagramEditor *editor)
	{
		if (editor && editor->currentProject())
			jwAutoResumeRemember(editor->currentProject()->filePath());
	}

	void jwAutoResumeInstallEditor(QETDiagramEditor *editor)
	{
		if (!editor || editor->property("jw_collab_auto_resume_installed").toBool())
			return;
		editor->setProperty("jw_collab_auto_resume_installed", true);

		// Let QET finish its normal startup/open-files path first.
		QTimer::singleShot(450, editor, [editor]() { jwAutoResumeTry(editor); });

		auto *timer = new QTimer(editor);
		timer->setInterval(2500);
		QObject::connect(timer, &QTimer::timeout, editor,
				[editor]() { jwAutoResumeObserve(editor); });
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
								[editor]() { jwAutoResumeInstallEditor(editor); });
				}
				return QObject::eventFilter(watched, event);
			}
	};

	void jwInstallCollaborativeAutoResume()
	{
		if (!qApp)
			return;

		auto *installer = new JwAutoResumeInstaller(qApp);
		qApp->installEventFilter(installer);

		for (QWidget *widget : QApplication::topLevelWidgets())
			if (auto *editor = qobject_cast<QETDiagramEditor *>(widget))
				jwAutoResumeInstallEditor(editor);
	}
}

Q_COREAPP_STARTUP_FUNCTION(jwInstallCollaborativeAutoResume)

/**
	@brief BackupDialog::BackupDialog
	@param parent parent widget
*/
BackupDialog::BackupDialog(QWidget *parent) :
	QDialog(parent)
{
	/*
	 * JW QET keeps QElectroTech's crash-recovery autosave enabled, but the
	 * upstream editor also asks on every project open whether a timestamped
	 * copy should be created next to the .qet file. In the collaborative
	 * workflow that extra prompt is noisy and redundant with baselines/master
	 * history, so it is disabled by default for the fork.
	 *
	 * The old behaviour can still be restored without rebuilding by setting
	 * QSettings key "jwcontrol/ask_open_backup" to true.
	 */
	QSettings settings;
	const bool ask_open_backup = settings.value(
			QStringLiteral("jwcontrol/ask_open_backup"), false).toBool();
	if (!ask_open_backup)
	{
		setAttribute(Qt::WA_DontShowOnScreen, true);
		QTimer::singleShot(0, this, &QDialog::reject);
		return;
	}

	// qet_es currently leaves the four strings in this dialog unfinished,
	// which makes Qt fall back to the French source text. Keep the normal
	// translation path for every other language, and provide a scoped JW QET
	// fallback only when the application's selected language is Spanish.
	const bool spanish_ui =
		QETApp::langFromSetting().section('_', 0, 0).compare(
			QStringLiteral("es"), Qt::CaseInsensitive) == 0;

	setWindowTitle(
		spanish_ui
			? QStringLiteral("¿Crear una copia de seguridad?")
			: tr("Créer une copie de sauvegarde ?", "window title"));
	setFixedSize(450, 100);

	auto main_layout = new QVBoxLayout(this);

	auto label = new QLabel(
		spanish_ui
			? QStringLiteral("¿Desea crear una copia de seguridad?")
			: tr("Souhaitez-vous créer une copie de sauvegarde ?",
			     "dialog message"));
	label->setWordWrap(true);
	main_layout->addWidget(label);

	main_layout->addStretch();

	auto button_layout = new QHBoxLayout();
	button_layout->addStretch();

	auto yes_button = new QPushButton(
		spanish_ui ? QStringLiteral("Sí") : tr("Oui", "yes button"));
	auto no_button = new QPushButton(
		spanish_ui ? QStringLiteral("No") : tr("Non", "no button"));

	button_layout->addWidget(yes_button);
	button_layout->addWidget(no_button);
	main_layout->addLayout(button_layout);

	connect(yes_button, &QPushButton::clicked, this, &QDialog::accept);
	connect(no_button, &QPushButton::clicked, this, &QDialog::reject);
}

/**
	@brief BackupDialog::~BackupDialog
*/
BackupDialog::~BackupDialog() = default;
