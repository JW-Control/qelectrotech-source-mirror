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

#include <QAbstractButton>
#include <QAbstractItemView>
#include <QApplication>
#include <QCryptographicHash>
#include <QDateTime>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDir>
#include <QDomDocument>
#include <QEvent>
#include <QFile>
#include <QFileInfo>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QRegularExpression>
#include <QSaveFile>
#include <QTimer>
#include <QVBoxLayout>

namespace
{
	const QString kManifestSuffix = QStringLiteral(".jwqet.json");

	struct JwFolio
	{
		QString key;
		QString label;
	};

	QString nowIso()
	{
		return QDateTime::currentDateTime().toString(Qt::ISODate);
	}

	QString timestamp()
	{
		return QDateTime::currentDateTime().toString(QStringLiteral("yyyyMMdd_HHmmss"));
	}

	QString userSlug(const QString &user)
	{
		QString slug = user.trimmed();
		slug.replace(QRegularExpression(QStringLiteral("[^A-Za-z0-9_.-]+")), QStringLiteral("_"));
		slug.remove(QRegularExpression(QStringLiteral("^[._-]+|[._-]+$")));
		return slug.isEmpty() ? QStringLiteral("usuario") : slug;
	}

	QString manifestForQet(const QString &qet_path)
	{
		return qet_path + kManifestSuffix;
	}

	QJsonObject readJson(const QString &path)
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

	bool writeJson(const QString &path, const QJsonObject &payload, QString *error_message = nullptr)
	{
		if (!QDir().mkpath(QFileInfo(path).absolutePath()))
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo crear la carpeta interna de colaboración.");
			return false;
		}

		QSaveFile file(path);
		if (!file.open(QIODevice::WriteOnly))
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo escribir %1\n%2")
					.arg(QDir::toNativeSeparators(path), file.errorString());
			return false;
		}
		file.write(QJsonDocument(payload).toJson(QJsonDocument::Indented));
		if (!file.commit())
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo finalizar %1\n%2")
					.arg(QDir::toNativeSeparators(path), file.errorString());
			return false;
		}
		return true;
	}

	QString sha256File(const QString &path)
	{
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly))
			return {};
		QCryptographicHash hash(QCryptographicHash::Sha256);
		while (!file.atEnd())
			hash.addData(file.read(1024 * 1024));
		return QString::fromLatin1(hash.result().toHex());
	}

	bool copyAtomically(const QString &source, const QString &destination, QString *error_message = nullptr)
	{
		QFile input(source);
		if (!input.open(QIODevice::ReadOnly))
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo leer el maestro:\n%1").arg(input.errorString());
			return false;
		}
		if (!QDir().mkpath(QFileInfo(destination).absolutePath()))
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo crear la carpeta de trabajo.");
			return false;
		}
		QSaveFile output(destination);
		if (!output.open(QIODevice::WriteOnly))
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo preparar la copia de trabajo:\n%1").arg(output.errorString());
			return false;
		}
		while (!input.atEnd())
		{
			const QByteArray chunk = input.read(1024 * 1024);
			if (output.write(chunk) != chunk.size())
			{
				output.cancelWriting();
				if (error_message)
					*error_message = QObject::tr("No se pudo copiar completamente el maestro.");
				return false;
			}
		}
		if (!output.commit())
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo reemplazar la copia de trabajo:\n%1").arg(output.errorString());
			return false;
		}
		return true;
	}

	QString workspaceFromPath(const QString &path)
	{
		if (path.isEmpty())
			return {};
		QDir directory = QFileInfo(path).absoluteDir();
		for (int level = 0; level < 18; ++level)
		{
			if (directory.exists(QStringLiteral("00_MASTER")) && directory.exists(QStringLiteral("02_WORKING")))
				return directory.absolutePath();
			if (!directory.cdUp())
				break;
		}
		return {};
	}

	QString masterPath(const QString &workspace)
	{
		QDir directory(QDir(workspace).absoluteFilePath(QStringLiteral("00_MASTER")));
		const QFileInfoList files = directory.entryInfoList(QStringList() << QStringLiteral("*.qet"), QDir::Files, QDir::Name);
		return files.isEmpty() ? QString() : files.first().absoluteFilePath();
	}

	QString hiddenRoot(const QString &workspace)
	{
		return QDir(workspace).absoluteFilePath(QStringLiteral(".jwqet"));
	}

	QString profilesPath(const QString &workspace)
	{
		return QDir(hiddenRoot(workspace)).absoluteFilePath(QStringLiteral("profiles.json"));
	}

	QString reservationsPath(const QString &workspace)
	{
		return QDir(hiddenRoot(workspace)).absoluteFilePath(QStringLiteral("reservations.json"));
	}

	QString relativeToWorkspace(const QString &path, const QString &workspace)
	{
		return QDir::fromNativeSeparators(QDir(workspace).relativeFilePath(path));
	}

	QStringList profileNames(const QString &workspace)
	{
		QStringList names;
		const QJsonObject registry = readJson(profilesPath(workspace));
		for (const QJsonValue &value : registry.value(QStringLiteral("profiles")).toArray())
		{
			const QString name = value.toObject().value(QStringLiteral("name")).toString().trimmed();
			if (!name.isEmpty() && !names.contains(name, Qt::CaseInsensitive))
				names << name;
		}
		QDir working(QDir(workspace).absoluteFilePath(QStringLiteral("02_WORKING")));
		for (const QFileInfo &info : working.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name))
		{
			const QString name = info.fileName();
			if (!name.isEmpty() && !names.contains(name, Qt::CaseInsensitive))
				names << name;
		}
		names.sort(Qt::CaseInsensitive);
		return names;
	}

	QString selectProfile(QWidget *parent, const QString &workspace, const QString &current, bool *accepted)
	{
		if (accepted)
			*accepted = false;
		QStringList profiles = profileNames(workspace);
		if (!current.isEmpty() && !profiles.contains(current, Qt::CaseInsensitive))
			profiles.prepend(current);
		if (profiles.isEmpty())
			return {};
		int index = profiles.indexOf(current);
		if (index < 0)
			index = 0;
		bool ok = false;
		const QString selected = QInputDialog::getItem(
				parent,
				QObject::tr("Continuar colaboración"),
				QObject::tr("Perfil para la nueva ronda:"),
				profiles,
				index,
				false,
				&ok).trimmed();
		if (!ok || selected.isEmpty())
			return {};
		if (accepted)
			*accepted = true;
		return selected;
	}

	bool rememberProfile(const QString &workspace, const QString &user, QString *error_message = nullptr)
	{
		QJsonObject registry = readJson(profilesPath(workspace));
		QJsonArray profiles = registry.value(QStringLiteral("profiles")).toArray();
		const QString slug = userSlug(user);
		bool found = false;
		for (int i = 0; i < profiles.size(); ++i)
		{
			QJsonObject item = profiles.at(i).toObject();
			if (item.value(QStringLiteral("slug")).toString() == slug)
			{
				item.insert(QStringLiteral("name"), user);
				item.insert(QStringLiteral("last_used_at"), nowIso());
				profiles.replace(i, item);
				found = true;
				break;
			}
		}
		if (!found)
		{
			QJsonObject item;
			item.insert(QStringLiteral("name"), user);
			item.insert(QStringLiteral("slug"), slug);
			item.insert(QStringLiteral("created_at"), nowIso());
			item.insert(QStringLiteral("last_used_at"), nowIso());
			profiles.append(item);
		}
		registry.insert(QStringLiteral("schema"), QStringLiteral("jw-qet-profiles.v1"));
		registry.insert(QStringLiteral("profiles"), profiles);
		return writeJson(profilesPath(workspace), registry, error_message);
	}

	QJsonObject reservationsObject(const QString &workspace)
	{
		QJsonObject root = readJson(reservationsPath(workspace));
		if (root.isEmpty())
			root.insert(QStringLiteral("schema"), QStringLiteral("jw-qet-reservations.v1"));
		return root;
	}

	QString reservedOwner(const QString &workspace, const QString &folio_key, const QString &except_user = QString())
	{
		const QJsonObject profiles = reservationsObject(workspace).value(QStringLiteral("profiles")).toObject();
		for (auto it = profiles.begin(); it != profiles.end(); ++it)
		{
			const QJsonObject entry = it.value().toObject();
			const QString user = entry.value(QStringLiteral("user")).toString();
			if (!except_user.isEmpty() && user.compare(except_user, Qt::CaseInsensitive) == 0)
				continue;
			for (const QJsonValue &value : entry.value(QStringLiteral("folios")).toArray())
				if (value.toString() == folio_key)
					return user.isEmpty() ? it.key() : user;
		}
		return {};
	}

	bool setReservation(const QString &workspace, const QString &user, const QStringList &folios, QString *error_message = nullptr)
	{
		QJsonObject root = reservationsObject(workspace);
		QJsonObject profiles = root.value(QStringLiteral("profiles")).toObject();
		QJsonObject entry;
		entry.insert(QStringLiteral("user"), user);
		entry.insert(QStringLiteral("user_slug"), userSlug(user));
		entry.insert(QStringLiteral("updated_at"), nowIso());
		QJsonArray array;
		for (const QString &folio : folios)
			array.append(folio);
		entry.insert(QStringLiteral("folios"), array);
		profiles.insert(userSlug(user), entry);
		root.insert(QStringLiteral("profiles"), profiles);
		root.insert(QStringLiteral("updated_at"), nowIso());
		return writeJson(reservationsPath(workspace), root, error_message);
	}

	QList<JwFolio> foliosFromQet(const QString &path, QString *error_message = nullptr)
	{
		QList<JwFolio> folios;
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly))
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo leer el maestro para listar sus folios.");
			return folios;
		}
		QDomDocument document;
		QString xml_error;
		int line = 0;
		int column = 0;
		if (!document.setContent(&file, &xml_error, &line, &column))
		{
			if (error_message)
				*error_message = QObject::tr("XML inválido al listar folios: %1").arg(xml_error);
			return folios;
		}
		int position = 0;
		for (QDomNode node = document.documentElement().firstChild(); !node.isNull(); node = node.nextSibling())
		{
			if (!node.isElement() || node.toElement().tagName() != QStringLiteral("diagram"))
				continue;
			++position;
			const QDomElement diagram = node.toElement();
			const QString order = diagram.attribute(QStringLiteral("order"), QString::number(position));
			const QString title = diagram.attribute(QStringLiteral("title")).trimmed();
			JwFolio folio;
			folio.key = QStringLiteral("order:%1").arg(order);
			folio.label = title.isEmpty()
				? QObject::tr("Folio %1").arg(order)
				: QObject::tr("Folio %1 — %2").arg(order, title);
			folios << folio;
		}
		return folios;
	}

	QStringList selectFolios(QWidget *parent, const QString &workspace, const QString &user,
			const QList<JwFolio> &folios, bool *accepted)
	{
		if (accepted)
			*accepted = false;
		QDialog dialog(parent);
		dialog.setWindowTitle(QObject::tr("Reservar folios colaborativos"));
		dialog.resize(610, 390);
		auto *layout = new QVBoxLayout(&dialog);
		auto *label = new QLabel(
			QObject::tr("Selecciona los folios que editará el perfil %1 en la nueva ronda.\n"
			            "Los folios reservados por otro perfil quedan bloqueados.").arg(user), &dialog);
		label->setWordWrap(true);
		layout->addWidget(label);
		auto *list = new QListWidget(&dialog);
		list->setSelectionMode(QAbstractItemView::NoSelection);
		for (const JwFolio &folio : folios)
		{
			const QString owner = reservedOwner(workspace, folio.key, user);
			QString text = folio.label;
			if (!owner.isEmpty())
				text += QObject::tr("    —    EN USO POR %1").arg(owner);
			auto *item = new QListWidgetItem(text, list);
			item->setData(Qt::UserRole, folio.key);
			item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
			item->setCheckState(Qt::Unchecked);
			if (!owner.isEmpty())
				item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
		}
		layout->addWidget(list, 1);
		auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
		buttons->button(QDialogButtonBox::Ok)->setText(QObject::tr("Continuar con estos folios"));
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
				if ((item->flags() & Qt::ItemIsEnabled) && item->checkState() == Qt::Checked)
					selected << item->data(Qt::UserRole).toString();
			}
			if (!selected.isEmpty())
			{
				if (accepted)
					*accepted = true;
				return selected;
			}
			QMessageBox::information(&dialog, QObject::tr("Sin folios reservados"),
				QObject::tr("Selecciona al menos un folio para continuar."));
		}
		return {};
	}

	bool refreshSession(QETDiagramEditor *editor, const QString &source_working_path)
	{
		const QString source_manifest_path = manifestForQet(source_working_path);
		const QJsonObject source_manifest = readJson(source_manifest_path);
		const QString workspace = workspaceFromPath(source_working_path);
		if (workspace.isEmpty())
		{
			QMessageBox::warning(editor, QObject::tr("No se pudo continuar"),
				QObject::tr("No se pudo localizar el workspace colaborativo."));
			return false;
		}
		const QString master = masterPath(workspace);
		if (master.isEmpty())
		{
			QMessageBox::warning(editor, QObject::tr("No se pudo continuar"),
				QObject::tr("No se encontró el proyecto oficial en 00_MASTER."));
			return false;
		}
		const QString master_hash = sha256File(master);
		const QString expected_hash = source_manifest.value(QStringLiteral("published_master_sha256")).toString();
		if (!expected_hash.isEmpty() && expected_hash != master_hash)
		{
			QMessageBox::information(editor, QObject::tr("Sincronizando maestro"),
				QObject::tr("La nueva versión del maestro todavía no llegó a esta PC.\n"
				            "Espera a que Google Drive termine de sincronizar y vuelve a intentar."));
			return false;
		}

		const QString current_user = source_manifest.value(QStringLiteral("user")).toString();
		bool profile_ok = false;
		const QString user = selectProfile(editor, workspace, current_user, &profile_ok);
		if (!profile_ok || user.isEmpty())
			return false;

		QString folio_error;
		const QList<JwFolio> folios = foliosFromQet(master, &folio_error);
		if (folios.isEmpty())
		{
			QMessageBox::warning(editor, QObject::tr("No se pudieron listar los folios"), folio_error);
			return false;
		}
		bool folios_ok = false;
		const QStringList reserved = selectFolios(editor, workspace, user, folios, &folios_ok);
		if (!folios_ok)
			return false;

		const QString slug = userSlug(user);
		const QFileInfo master_info(master);
		const QString working_path = QDir(QDir(QDir(workspace).absoluteFilePath(QStringLiteral("02_WORKING"))).absoluteFilePath(slug))
			.absoluteFilePath(master_info.fileName());
		const QString working_manifest_path = manifestForQet(working_path);
		const QJsonObject existing_target = readJson(working_manifest_path);
		if (existing_target.value(QStringLiteral("status")).toString() == QStringLiteral("submitted"))
		{
			QMessageBox::information(editor, QObject::tr("Entrega pendiente"),
				QObject::tr("El perfil %1 todavía tiene una entrega pendiente de publicación.").arg(user));
			return false;
		}

		if (editor->currentProject())
		{
			const QString current_path = editor->currentProject()->filePath();
			if (workspaceFromPath(current_path) == workspace)
			{
				if (!editor->closeProject(editor->currentProject()))
					return false;
			}
		}
		if (auto *view = editor->viewForFile(working_path))
		{
			if (!editor->closeProject(view))
				return false;
		}

		const QString baseline_dir = QDir(hiddenRoot(workspace)).absoluteFilePath(QStringLiteral("baselines"));
		const QString baseline_path = QDir(baseline_dir).absoluteFilePath(
			QStringLiteral("%1_%2").arg(master_hash.left(16), master_info.fileName()));
		QString error_message;
		if (!QFileInfo::exists(baseline_path) && !copyAtomically(master, baseline_path, &error_message))
		{
			QMessageBox::warning(editor, QObject::tr("No se pudo preparar la baseline"), error_message);
			return false;
		}
		if (!copyAtomically(master, working_path, &error_message))
		{
			QMessageBox::warning(editor, QObject::tr("No se pudo actualizar la copia"), error_message);
			return false;
		}

		const QString incoming = QDir(QDir(hiddenRoot(workspace)).absoluteFilePath(QStringLiteral("incoming/%1").arg(slug)))
			.absoluteFilePath(master_info.fileName());
		const QString logs_dir = QDir(hiddenRoot(workspace)).absoluteFilePath(QStringLiteral("logs"));
		QJsonArray reserved_array;
		for (const QString &folio : reserved)
			reserved_array.append(folio);

		QJsonObject manifest = existing_target;
		manifest.insert(QStringLiteral("schema"), QStringLiteral("jw-qet-collab-session.v1"));
		manifest.insert(QStringLiteral("workflow_version"), 2);
		manifest.insert(QStringLiteral("session_id"), timestamp());
		manifest.insert(QStringLiteral("created_at"), nowIso());
		manifest.insert(QStringLiteral("status"), QStringLiteral("checked_out"));
		manifest.insert(QStringLiteral("user"), user);
		manifest.insert(QStringLiteral("user_slug"), slug);
		manifest.insert(QStringLiteral("reserved_folios"), reserved_array);
		manifest.insert(QStringLiteral("master_path"), QFileInfo(master).absoluteFilePath());
		manifest.insert(QStringLiteral("workspace_path"), QFileInfo(workspace).absoluteFilePath());
		manifest.insert(QStringLiteral("baseline_path"), QFileInfo(baseline_path).absoluteFilePath());
		manifest.insert(QStringLiteral("working_path"), QFileInfo(working_path).absoluteFilePath());
		manifest.insert(QStringLiteral("incoming_path"), QFileInfo(incoming).absoluteFilePath());
		manifest.insert(QStringLiteral("logs_dir"), QFileInfo(logs_dir).absoluteFilePath());
		manifest.insert(QStringLiteral("master_relpath"), relativeToWorkspace(master, workspace));
		manifest.insert(QStringLiteral("baseline_relpath"), relativeToWorkspace(baseline_path, workspace));
		manifest.insert(QStringLiteral("working_relpath"), relativeToWorkspace(working_path, workspace));
		manifest.insert(QStringLiteral("incoming_relpath"), relativeToWorkspace(incoming, workspace));
		manifest.insert(QStringLiteral("logs_relpath"), relativeToWorkspace(logs_dir, workspace));
		manifest.insert(QStringLiteral("master_sha256"), master_hash);
		manifest.insert(QStringLiteral("baseline_sha256"), sha256File(baseline_path));
		manifest.insert(QStringLiteral("working_sha256"), sha256File(working_path));
		for (const QString &field : {
			QStringLiteral("submitted_at"), QStringLiteral("published_at"), QStringLiteral("published_master_sha256"),
			QStringLiteral("incoming_sha256"), QStringLiteral("changed_folios")})
			manifest.remove(field);

		if (!writeJson(working_manifest_path, manifest, &error_message)
				|| !setReservation(workspace, user, reserved, &error_message)
				|| !rememberProfile(workspace, user, &error_message))
		{
			QMessageBox::warning(editor, QObject::tr("No se pudo iniciar la nueva ronda"), error_message);
			return false;
		}

		QDir().mkpath(logs_dir);
		QJsonObject log = manifest;
		log.insert(QStringLiteral("event"), QStringLiteral("continue_after_publish"));
		writeJson(QDir(logs_dir).absoluteFilePath(
			QStringLiteral("%1_continue_%2.json").arg(timestamp(), slug)), log);

		if (!editor->openAndAddProject(working_path))
		{
			QMessageBox::warning(editor, QObject::tr("No se pudo abrir la copia"),
				QObject::tr("La copia se actualizó correctamente, pero QET no pudo abrirla automáticamente."));
			return false;
		}
		QMessageBox::information(editor, QObject::tr("Nueva ronda lista"),
			QObject::tr("Perfil: %1\nFolios reservados: %2\n\nLa copia local ya está basada en el maestro actualizado.")
				.arg(user, [&reserved]() {
					QStringList labels;
					for (const QString &key : reserved)
						labels << (key.startsWith(QStringLiteral("order:")) ? QObject::tr("Folio %1").arg(key.mid(6)) : key);
					return labels.join(QStringLiteral(", "));
				}()));
		return true;
	}

	QETDiagramEditor *editorFor(QWidget *widget)
	{
		for (QWidget *cursor = widget; cursor; cursor = cursor->parentWidget())
			if (auto *editor = qobject_cast<QETDiagramEditor *>(cursor))
				return editor;
		return nullptr;
	}

	QString refreshKey(QETDiagramEditor *editor)
	{
		if (!editor || !editor->currentProject())
			return {};
		const QString path = editor->currentProject()->filePath();
		const QJsonObject manifest = readJson(manifestForQet(path));
		if (manifest.value(QStringLiteral("status")).toString() != QStringLiteral("refresh_required"))
			return {};
		const QString published = manifest.value(QStringLiteral("published_master_sha256")).toString();
		return path + QStringLiteral("|") + published;
	}

	void maybePromptRemoteRefresh(QETDiagramEditor *editor)
	{
		if (!editor || !editor->currentProject() || editor->property("jw_collab_publish_dialog_active").toBool())
			return;
		const QString working_path = editor->currentProject()->filePath();
		const QJsonObject manifest = readJson(manifestForQet(working_path));
		if (manifest.value(QStringLiteral("status")).toString() != QStringLiteral("refresh_required"))
			return;
		const QString workspace = workspaceFromPath(working_path);
		const QString master = masterPath(workspace);
		if (workspace.isEmpty() || master.isEmpty())
			return;
		const QString published_hash = manifest.value(QStringLiteral("published_master_sha256")).toString();
		if (!published_hash.isEmpty() && sha256File(master) != published_hash)
			return; // Drive has not finished syncing this PC yet.
		const QString key = refreshKey(editor);
		if (key.isEmpty() || editor->property("jw_collab_refresh_prompt_key").toString() == key)
			return;
		editor->setProperty("jw_collab_refresh_prompt_key", key);

		QMessageBox message(QMessageBox::Information,
			QObject::tr("Maestro colaborativo actualizado"),
			QObject::tr("Ya está disponible la nueva versión oficial del proyecto."),
			QMessageBox::NoButton,
			editor);
		message.setInformativeText(QObject::tr("Perfil actual: %1\n\nPuedes actualizar tu copia local y elegir los folios de la siguiente ronda sin cerrar QElectroTech.")
			.arg(manifest.value(QStringLiteral("user")).toString()));
		QPushButton *continue_button = message.addButton(QObject::tr("Continuar"), QMessageBox::AcceptRole);
		message.addButton(QObject::tr("Más tarde"), QMessageBox::RejectRole);
		message.exec();
		if (message.clickedButton() == continue_button)
			refreshSession(editor, working_path);
	}

	void augmentPublishSuccess(QMessageBox *box)
	{
		if (!box || box->property("jw_collab_continue_augmented").toBool())
			return;
		if (box->windowTitle() != QObject::tr("Proyecto maestro actualizado"))
			return;
		QETDiagramEditor *editor = editorFor(box);
		if (!editor || !editor->currentProject())
			return;
		const QString working_path = editor->currentProject()->filePath();
		const QJsonObject manifest = readJson(manifestForQet(working_path));
		if (manifest.value(QStringLiteral("status")).toString() != QStringLiteral("refresh_required"))
			return;

		box->setProperty("jw_collab_continue_augmented", true);
		editor->setProperty("jw_collab_publish_dialog_active", true);
		QPushButton *continue_button = box->addButton(QObject::tr("Continuar"), QMessageBox::ActionRole);
		QObject::connect(continue_button, &QPushButton::clicked, box, [box, editor, working_path]() {
			box->setProperty("jw_collab_continue_clicked", true);
			QTimer::singleShot(50, editor, [editor, working_path]() {
				refreshSession(editor, working_path);
			});
		});
		QObject::connect(box, &QMessageBox::finished, editor, [box, editor](int) {
			editor->setProperty("jw_collab_publish_dialog_active", false);
			if (!box->property("jw_collab_continue_clicked").toBool())
				editor->setProperty("jw_collab_refresh_prompt_key", refreshKey(editor));
		});
	}

	void installEditorWatch(QETDiagramEditor *editor)
	{
		if (!editor || editor->property("jw_collab_continuation_installed").toBool())
			return;
		editor->setProperty("jw_collab_continuation_installed", true);
		auto *timer = new QTimer(editor);
		timer->setInterval(1500);
		QObject::connect(timer, &QTimer::timeout, editor, [editor]() { maybePromptRemoteRefresh(editor); });
		timer->start();
	}

	class JwContinuationInstaller : public QObject
	{
		public:
			explicit JwContinuationInstaller(QObject *parent = nullptr) : QObject(parent) {}

		protected:
			bool eventFilter(QObject *watched, QEvent *event) override
			{
				if (event->type() == QEvent::Show)
				{
					if (auto *editor = qobject_cast<QETDiagramEditor *>(watched))
						QTimer::singleShot(0, editor, [editor]() { installEditorWatch(editor); });
					else if (auto *box = qobject_cast<QMessageBox *>(watched))
						QTimer::singleShot(0, box, [box]() { augmentPublishSuccess(box); });
				}
				return QObject::eventFilter(watched, event);
			}
	};

	void installContinuationWorkflow()
	{
		if (!qApp)
			return;
		auto *installer = new JwContinuationInstaller(qApp);
		qApp->installEventFilter(installer);
		for (QWidget *widget : QApplication::topLevelWidgets())
			if (auto *editor = qobject_cast<QETDiagramEditor *>(widget))
				installEditorWatch(editor);
	}
}

Q_COREAPP_STARTUP_FUNCTION(installContinuationWorkflow)
