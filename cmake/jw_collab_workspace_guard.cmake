# JW Control - Google Drive workspace safety guard
#
# The collaborative UI predates the workspace marker and historically created
# missing .jwqet directories on demand. On a partially synchronized Google
# Drive mount that is dangerous: Drive can turn a local mkdir("incoming") into
# a second remote folder named "incoming (1)" with a different folder ID.
#
# Keep the upstream-facing source easy to review while generating a guarded
# translation unit in the build tree. Every replacement below is anchored to
# exact source text and configuration fails loudly if the collaboration module
# changes underneath us.

set(_jw_collab_source "${QET_DIR}/sources/jwcollabselection.cpp")
set(_jw_collab_generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated/jwcollab")
set(JW_COLLAB_SELECTION_SOURCE "${_jw_collab_generated_dir}/jwcollabselection.cpp")

file(MAKE_DIRECTORY "${_jw_collab_generated_dir}")
file(READ "${_jw_collab_source}" _jw_collab_content)

function(_jw_collab_replace_exact label old_text new_text)
    string(FIND "${_jw_collab_content}" "${old_text}" _jw_collab_index)
    if(_jw_collab_index EQUAL -1)
        message(FATAL_ERROR
            "JW collaboration guard: anchor '${label}' was not found in "
            "${_jw_collab_source}. Refusing to build an unguarded workflow.")
    endif()
    string(REPLACE "${old_text}" "${new_text}" _jw_collab_content "${_jw_collab_content}")
    set(_jw_collab_content "${_jw_collab_content}" PARENT_SCOPE)
endfunction()

set(_anchor_helpers [=[
		return(true);
	}

	QString sha256File(const QString &path)
]=])
set(_replacement_helpers [=[
		return(true);
	}

	const QString kWorkspaceSchema = QStringLiteral("jw-qet-workspace.v1");

	QString workspaceMarkerPath(const QString &workspace)
	{
		return(QDir(hiddenRoot(workspace)).absoluteFilePath(QStringLiteral("workspace.json")));
	}

	QStringList duplicateWorkspaceEntries(const QString &workspace)
	{
		QStringList duplicates;

		const QRegularExpression root_duplicate(
				QStringLiteral("^(?:\\.jwqet|00_MASTER|01_BASELINES|02_WORKING|03_INCOMING|04_PUBLISHED|05_ARCHIVE|06_LOGS) \\(\\d+\\)$"),
				QRegularExpression::CaseInsensitiveOption);
		QDir root(workspace);
		for (const QFileInfo &info : root.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::Name))
		{
			if (root_duplicate.match(info.fileName()).hasMatch())
				duplicates << info.fileName();
		}

		QDir internal(hiddenRoot(workspace));
		if (internal.exists())
		{
			const QRegularExpression internal_duplicate(
					QStringLiteral("^(?:baselines|incoming|logs|history) \\(\\d+\\)$|^(?:profiles|reservations|workspace) \\(\\d+\\)\\.json$"),
					QRegularExpression::CaseInsensitiveOption);
			for (const QFileInfo &info : internal.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::Name))
			{
				if (internal_duplicate.match(info.fileName()).hasMatch())
					duplicates << QStringLiteral(".jwqet/%1").arg(info.fileName());
			}
		}
		return(duplicates);
	}

	bool initializeWorkspaceMarker(QWidget *parent, const QString &workspace)
	{
		const QString internal = hiddenRoot(workspace);
		const QStringList required_existing_dirs {
			QDir(internal).absoluteFilePath(QStringLiteral("baselines")),
			QDir(internal).absoluteFilePath(QStringLiteral("incoming")),
			QDir(internal).absoluteFilePath(QStringLiteral("logs"))
		};
		QStringList missing;
		for (const QString &path : required_existing_dirs)
		{
			if (!QFileInfo(path).isDir())
				missing << QDir::toNativeSeparators(path);
		}
		if (!missing.isEmpty())
		{
			QMessageBox message(QMessageBox::Warning,
					QObject::tr("Workspace colaborativo aún no sincronizado"),
					QObject::tr("JW QET no creará carpetas internas que todavía no aparecen en esta PC."),
					QMessageBox::Ok,
					parent);
			message.setInformativeText(QObject::tr(
					"Espera a que Google Drive termine de sincronizar y vuelve a intentarlo.\n\nFalta:\n%1")
						.arg(missing.join(QStringLiteral("\n"))));
			message.exec();
			return(false);
		}

		QString error_message;
		const QString history_master = QDir(internal).absoluteFilePath(QStringLiteral("history/master"));
		if (!QDir().mkpath(history_master))
		{
			QMessageBox::warning(parent,
					QObject::tr("No se pudo inicializar el workspace"),
					QObject::tr("No se pudo preparar el historial interno:\n%1")
						.arg(QDir::toNativeSeparators(history_master)));
			return(false);
		}

		if (!QFileInfo::exists(profilesPath(workspace)))
		{
			QJsonObject profiles;
			profiles.insert(QStringLiteral("schema"), QStringLiteral("jw-qet-profiles.v1"));
			profiles.insert(QStringLiteral("profiles"), QJsonArray());
			if (!writeJson(profilesPath(workspace), profiles, &error_message))
			{
				QMessageBox::warning(parent, QObject::tr("No se pudo inicializar el workspace"), error_message);
				return(false);
			}
		}

		if (!QFileInfo::exists(reservationsPath(workspace)))
		{
			QJsonObject reservations;
			reservations.insert(QStringLiteral("schema"), QStringLiteral("jw-qet-reservations.v1"));
			reservations.insert(QStringLiteral("profiles"), QJsonObject());
			if (!writeJson(reservationsPath(workspace), reservations, &error_message))
			{
				QMessageBox::warning(parent, QObject::tr("No se pudo inicializar el workspace"), error_message);
				return(false);
			}
		}

		QJsonObject marker;
		marker.insert(QStringLiteral("schema"), kWorkspaceSchema);
		marker.insert(QStringLiteral("workflow_version"), 2);
		marker.insert(QStringLiteral("guard_version"), 1);
		marker.insert(QStringLiteral("initialized_at"), nowIso());
		if (!writeJson(workspaceMarkerPath(workspace), marker, &error_message))
		{
			QMessageBox::warning(parent, QObject::tr("No se pudo inicializar el workspace"), error_message);
			return(false);
		}
		return(true);
	}

	bool ensureWorkspaceReady(QWidget *parent, const QString &workspace)
	{
		if (workspace.trimmed().isEmpty() || !QFileInfo(workspace).isDir())
		{
			QMessageBox::warning(parent,
					QObject::tr("Carpeta colaborativa no válida"),
					QObject::tr("No se pudo resolver la carpeta colaborativa en esta PC."));
			return(false);
		}

		const QStringList duplicates = duplicateWorkspaceEntries(workspace);
		if (!duplicates.isEmpty())
		{
			QMessageBox message(QMessageBox::Critical,
					QObject::tr("Workspace colaborativo inconsistente"),
					QObject::tr("Se detectaron carpetas o archivos duplicados por sincronización."),
					QMessageBox::Ok,
					parent);
			message.setInformativeText(QObject::tr(
					"JW QET no realizará cambios para evitar dividir el estado colaborativo.\n\n"
					"Consolida los duplicados desde Google Drive y vuelve a intentarlo."));
			message.setDetailedText(duplicates.join(QStringLiteral("\n")));
			message.exec();
			return(false);
		}

		const QString internal = hiddenRoot(workspace);
		if (!QFileInfo(internal).isDir())
		{
			QMessageBox::warning(parent,
					QObject::tr("Workspace colaborativo aún no sincronizado"),
					QObject::tr("No aparece la carpeta .jwqet en esta PC. JW QET no la creará automáticamente.\n\n"
					            "Espera a que Google Drive termine de sincronizar y vuelve a intentarlo."));
			return(false);
		}

		const QString marker_path = workspaceMarkerPath(workspace);
		if (!QFileInfo::exists(marker_path))
			return(initializeWorkspaceMarker(parent, workspace));

		const QJsonObject marker = readJson(marker_path);
		if (marker.value(QStringLiteral("schema")).toString() != kWorkspaceSchema)
		{
			QMessageBox::critical(parent,
					QObject::tr("Workspace colaborativo inconsistente"),
					QObject::tr("workspace.json no es válido o todavía está sincronizándose. JW QET no realizará cambios."));
			return(false);
		}

		const QStringList required_paths {
			QDir(internal).absoluteFilePath(QStringLiteral("baselines")),
			QDir(internal).absoluteFilePath(QStringLiteral("incoming")),
			QDir(internal).absoluteFilePath(QStringLiteral("logs")),
			QDir(internal).absoluteFilePath(QStringLiteral("history/master")),
			profilesPath(workspace),
			reservationsPath(workspace)
		};
		QStringList missing;
		for (const QString &path : required_paths)
		{
			if (!QFileInfo::exists(path))
				missing << QDir::toNativeSeparators(path);
		}
		if (!missing.isEmpty())
		{
			QMessageBox message(QMessageBox::Warning,
					QObject::tr("Workspace colaborativo aún no sincronizado"),
					QObject::tr("workspace.json ya existe, pero esta PC todavía no ve toda la estructura canónica."),
					QMessageBox::Ok,
					parent);
			message.setInformativeText(QObject::tr(
					"JW QET no recreará lo que falta. Espera a Google Drive y vuelve a intentarlo."));
			message.setDetailedText(missing.join(QStringLiteral("\n")));
			message.exec();
			return(false);
		}
		return(true);
	}

	QString sha256File(const QString &path)
]=])
_jw_collab_replace_exact("workspace helper insertion" "${_anchor_helpers}" "${_replacement_helpers}")

set(_anchor_session [=[
	bool createOrContinueSession(QETDiagramEditor *editor, const QString &master, const QString &workspace,
			const QString &user, const QStringList &reserved)
	{
		const QString slug = userSlug(user);
]=])
set(_replacement_session [=[
	bool createOrContinueSession(QETDiagramEditor *editor, const QString &master, const QString &workspace,
			const QString &user, const QStringList &reserved)
	{
		if (!ensureWorkspaceReady(editor, workspace))
			return(false);

		const QString slug = userSlug(user);
]=])
_jw_collab_replace_exact("session guard" "${_anchor_session}" "${_replacement_session}")

set(_anchor_checkout [=[
		if (workspace.isEmpty())
			return;

		bool profile_ok = false;
]=])
set(_replacement_checkout [=[
		if (workspace.isEmpty())
			return;
		if (!ensureWorkspaceReady(editor, workspace))
			return;

		bool profile_ok = false;
]=])
_jw_collab_replace_exact("checkout guard" "${_anchor_checkout}" "${_replacement_checkout}")

set(_anchor_submit [=[
		const QString workspace = workspaceFromPath(working_path);
		const QString baseline = resolveMember(workspace, manifest,
]=])
set(_replacement_submit [=[
		const QString workspace = workspaceFromPath(working_path);
		if (!ensureWorkspaceReady(editor, workspace))
			return;
		const QString baseline = resolveMember(workspace, manifest,
]=])
_jw_collab_replace_exact("submit guard" "${_anchor_submit}" "${_replacement_submit}")

set(_anchor_publish [=[
		if (workspace.isEmpty())
			return;

		const QString master = masterPath(workspace);
]=])
set(_replacement_publish [=[
		if (workspace.isEmpty())
			return;
		if (!ensureWorkspaceReady(editor, workspace))
			return;

		const QString master = masterPath(workspace);
]=])
_jw_collab_replace_exact("publish guard" "${_anchor_publish}" "${_replacement_publish}")

set(_anchor_tmp [=[
			const QString temp_dir = QDir(hiddenRoot(workspace)).absoluteFilePath(QStringLiteral("tmp"));
			QDir().mkpath(temp_dir);
			const QString temp_output = QDir(temp_dir).absoluteFilePath(QStringLiteral("merge_%1.qet").arg(timestamp()));
]=])
set(_replacement_tmp [=[
			const QString workspace_token = QString::fromLatin1(
					QCryptographicHash::hash(workspace.toUtf8(), QCryptographicHash::Sha256).toHex().left(12));
			const QString temp_dir = QDir(QStandardPaths::writableLocation(QStandardPaths::TempLocation))
					.absoluteFilePath(QStringLiteral("JWControl/JWQET/%1").arg(workspace_token));
			if (!QDir().mkpath(temp_dir))
			{
				QMessageBox::warning(editor,
						QObject::tr("No se pudo preparar la publicación"),
						QObject::tr("No se pudo crear la carpeta temporal local:\n%1")
							.arg(QDir::toNativeSeparators(temp_dir)));
				return;
			}
			const QString temp_output = QDir(temp_dir).absoluteFilePath(QStringLiteral("merge_%1.qet").arg(timestamp()));
]=])
_jw_collab_replace_exact("local publish temp" "${_anchor_tmp}" "${_replacement_tmp}")

set(_anchor_open_validation [=[
		const QString path = editor->currentProject()->filePath();
		const QString manifest_path = manifestForQet(path);
]=])
set(_replacement_open_validation [=[
		const QString path = editor->currentProject()->filePath();
		const QString workspace = workspaceFromPath(path);
		if (!workspace.isEmpty() && !editor->property("jw_workspace_guard_checked").toBool())
		{
			editor->setProperty("jw_workspace_guard_checked", true);
			if (!ensureWorkspaceReady(editor, workspace))
			{
				label->setText(QObject::tr("COLAB: workspace bloqueado · revisa sincronización de Google Drive"));
				label->show();
				return;
			}
		}
		const QString manifest_path = manifestForQet(path);
]=])
_jw_collab_replace_exact("open workspace validation" "${_anchor_open_validation}" "${_replacement_open_validation}")

file(WRITE "${JW_COLLAB_SELECTION_SOURCE}" "${_jw_collab_content}")
message(STATUS "JW collaboration workspace guard: ${JW_COLLAB_SELECTION_SOURCE}")