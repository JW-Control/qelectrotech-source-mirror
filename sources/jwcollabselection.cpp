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
#include <QAbstractItemView>
#include <QAction>
#include <QApplication>
#include <QCoreApplication>
#include <QCryptographicHash>
#include <QDateTime>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDir>
#include <QDomDocument>
#include <QEvent>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QInputDialog>
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
#include <QSaveFile>
#include <QSettings>
#include <QStandardPaths>
#include <QStatusBar>
#include <QStringList>
#include <QTimer>
#include <QVBoxLayout>

namespace
{
	const QString kManifestSuffix = QStringLiteral(".jwqet.json");
	const QString kSchema = QStringLiteral("jw-qet-collab-session.v1");

	struct JwFolio
	{
		QString key;
		QString label;
	};

	struct JwDelivery
	{
		QString manifest_path;
		QString user;
		QString user_slug;
		QDateTime submitted_at;
		QString baseline_sha256;
		bool stale = false;
	};

	struct JwMergeResult
	{
		bool parsed = false;
		QJsonObject payload;
		QString error_message;
	};

	QString nowIso()
	{
		return(QDateTime::currentDateTime().toString(Qt::ISODate));
	}

	QString timestamp()
	{
		return(QDateTime::currentDateTime().toString(QStringLiteral("yyyyMMdd_HHmmss")));
	}

	QString userSlug(const QString &user)
	{
		QString slug = user.trimmed();
		slug.replace(QRegularExpression(QStringLiteral("[^A-Za-z0-9_.-]+")), QStringLiteral("_"));
		slug = slug.remove(QRegularExpression(QStringLiteral("^[._-]+|[._-]+$")));
		return(slug.isEmpty() ? QStringLiteral("usuario") : slug);
	}

	QString hiddenRoot(const QString &workspace)
	{
		return(QDir(workspace).absoluteFilePath(QStringLiteral(".jwqet")));
	}

	QString profilesPath(const QString &workspace)
	{
		return(QDir(hiddenRoot(workspace)).absoluteFilePath(QStringLiteral("profiles.json")));
	}

	QString reservationsPath(const QString &workspace)
	{
		return(QDir(hiddenRoot(workspace)).absoluteFilePath(QStringLiteral("reservations.json")));
	}

	QString manifestForQet(const QString &qet_path)
	{
		return(qet_path + kManifestSuffix);
	}

	QJsonObject readJson(const QString &path)
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

	bool writeJson(const QString &path, const QJsonObject &payload, QString *error_message = nullptr)
	{
		const QFileInfo info(path);
		if (!QDir().mkpath(info.absolutePath()))
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo crear la carpeta interna:\n%1").arg(
						QDir::toNativeSeparators(info.absolutePath()));
			return(false);
		}

		QSaveFile file(path);
		if (!file.open(QIODevice::WriteOnly))
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo escribir:\n%1\n%2").arg(
						QDir::toNativeSeparators(path), file.errorString());
			return(false);
		}
		file.write(QJsonDocument(payload).toJson(QJsonDocument::Indented));
		if (!file.commit())
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo finalizar la escritura:\n%1\n%2").arg(
						QDir::toNativeSeparators(path), file.errorString());
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

	bool copyOverwrite(const QString &source, const QString &destination, QString *error_message = nullptr)
	{
		if (!QFileInfo::exists(source))
		{
			if (error_message)
				*error_message = QObject::tr("No existe el archivo de origen:\n%1").arg(QDir::toNativeSeparators(source));
			return(false);
		}
		if (!QDir().mkpath(QFileInfo(destination).absolutePath()))
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo crear la carpeta destino:\n%1").arg(
						QDir::toNativeSeparators(QFileInfo(destination).absolutePath()));
			return(false);
		}
		if (QFileInfo::exists(destination) && !QFile::remove(destination))
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo reemplazar:\n%1").arg(QDir::toNativeSeparators(destination));
			return(false);
		}
		if (!QFile::copy(source, destination))
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo copiar:\n%1\nhacia:\n%2").arg(
						QDir::toNativeSeparators(source), QDir::toNativeSeparators(destination));
			return(false);
		}
		return(true);
	}

	bool replaceAtomically(const QString &source, const QString &destination, QString *error_message = nullptr)
	{
		QFile input(source);
		if (!input.open(QIODevice::ReadOnly))
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo leer el resultado de la fusión:\n%1").arg(input.errorString());
			return(false);
		}
		QSaveFile output(destination);
		if (!output.open(QIODevice::WriteOnly))
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo preparar el maestro oficial:\n%1").arg(output.errorString());
			return(false);
		}
		while (!input.atEnd())
		{
			const QByteArray chunk = input.read(1024 * 1024);
			if (output.write(chunk) != chunk.size())
			{
				if (error_message)
					*error_message = QObject::tr("No se pudo escribir completamente el maestro oficial.");
				output.cancelWriting();
				return(false);
			}
		}
		if (!output.commit())
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo reemplazar atómicamente el maestro:\n%1").arg(output.errorString());
			return(false);
		}
		return(true);
	}

	QString relativeToWorkspace(const QString &path, const QString &workspace)
	{
		return(QDir::fromNativeSeparators(QDir(workspace).relativeFilePath(path)));
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
				QStringLiteral("00_MASTER"), QStringLiteral("01_BASELINES"),
				QStringLiteral("02_WORKING"), QStringLiteral("03_INCOMING"),
				QStringLiteral("04_PUBLISHED"), QStringLiteral("05_ARCHIVE"),
				QStringLiteral("06_LOGS"), QStringLiteral(".jwqet")
			};
			const QStringList parts = normalized.split('/', Qt::SkipEmptyParts);
			for (int index = 0; index < parts.size(); ++index)
			{
				if (markers.contains(parts.at(index)))
				{
					const QString suffix = parts.mid(index).join('/');
					const QString candidate = QDir(workspace).absoluteFilePath(suffix);
					if (QFileInfo::exists(candidate))
						return(QDir::cleanPath(candidate));
				}
			}
			if (QFileInfo::exists(stored))
				return(QFileInfo(stored).absoluteFilePath());
		}
		return(QString());
	}

	QString masterPath(const QString &workspace)
	{
		QDir master_dir(QDir(workspace).absoluteFilePath(QStringLiteral("00_MASTER")));
		const QFileInfoList masters = master_dir.entryInfoList(
				QStringList() << QStringLiteral("*.qet"), QDir::Files, QDir::Name);
		return(masters.isEmpty() ? QString() : masters.first().absoluteFilePath());
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
		const QFileInfoList directories = working.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
		for (const QFileInfo &info : directories)
		{
			const QString name = info.fileName();
			if (!name.isEmpty() && !names.contains(name, Qt::CaseInsensitive))
				names << name;
		}
		names.sort(Qt::CaseInsensitive);
		return(names);
	}

	bool rememberProfile(const QString &workspace, const QString &user, QString *error_message = nullptr)
	{
		QJsonObject registry = readJson(profilesPath(workspace));
		QJsonArray profiles = registry.value(QStringLiteral("profiles")).toArray();
		const QString slug = userSlug(user);
		bool found = false;
		for (int index = 0; index < profiles.size(); ++index)
		{
			QJsonObject item = profiles.at(index).toObject();
			if (item.value(QStringLiteral("slug")).toString() == slug)
			{
				item.insert(QStringLiteral("name"), user);
				item.insert(QStringLiteral("last_used_at"), nowIso());
				profiles.replace(index, item);
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
		return(writeJson(profilesPath(workspace), registry, error_message));
	}

	QString selectProfile(QWidget *parent, const QString &workspace, bool *accepted)
	{
		if (accepted)
			*accepted = false;
		QStringList profiles = profileNames(workspace);
		const QString create_label = QObject::tr("Crear nuevo perfil...");
		profiles << create_label;

		QSettings settings;
		const QString last = settings.value(QStringLiteral("jwcollab/last_profile")).toString();
		int current = profiles.indexOf(last);
		if (current < 0)
			current = 0;

		bool ok = false;
		QString selected = QInputDialog::getItem(
				parent,
				QObject::tr("Perfil colaborativo"),
				QObject::tr("Selecciona el perfil que usarás en esta PC:"),
				profiles,
				current,
				false,
				&ok).trimmed();
		if (!ok || selected.isEmpty())
			return(QString());

		if (selected == create_label)
		{
			QString suggested = qEnvironmentVariable("USERNAME").trimmed();
			selected = QInputDialog::getText(
					parent,
					QObject::tr("Nuevo perfil colaborativo"),
					QObject::tr("Nombre del perfil:"),
					QLineEdit::Normal,
					suggested,
					&ok).trimmed();
			if (!ok || selected.isEmpty())
				return(QString());
		}

		settings.setValue(QStringLiteral("jwcollab/last_profile"), selected);
		if (accepted)
			*accepted = true;
		return(selected);
	}

	QList<JwFolio> foliosFromQet(const QString &path, QString *error_message = nullptr)
	{
		QList<JwFolio> folios;
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly))
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo leer el proyecto para listar sus folios.");
			return(folios);
		}
		QDomDocument document;
		QString xml_error;
		int error_line = 0;
		int error_column = 0;
		if (!document.setContent(&file, &xml_error, &error_line, &error_column))
		{
			if (error_message)
				*error_message = QObject::tr("XML inválido al listar folios: %1 (línea %2, columna %3)")
						.arg(xml_error).arg(error_line).arg(error_column);
			return(folios);
		}

		const QDomElement root = document.documentElement();
		int position = 0;
		for (QDomNode node = root.firstChild(); !node.isNull(); node = node.nextSibling())
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
		return(folios);
	}

	QJsonObject reservationsObject(const QString &workspace)
	{
		QJsonObject root = readJson(reservationsPath(workspace));
		if (root.isEmpty())
			root.insert(QStringLiteral("schema"), QStringLiteral("jw-qet-reservations.v1"));
		return(root);
	}

	QStringList reservedFoliosFor(const QString &workspace, const QString &user)
	{
		const QJsonObject profiles = reservationsObject(workspace).value(QStringLiteral("profiles")).toObject();
		const QJsonObject entry = profiles.value(userSlug(user)).toObject();
		QStringList result;
		for (const QJsonValue &value : entry.value(QStringLiteral("folios")).toArray())
			if (value.isString())
				result << value.toString();
		return(result);
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
					return(user.isEmpty() ? it.key() : user);
		}
		return(QString());
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
		return(writeJson(reservationsPath(workspace), root, error_message));
	}

	void clearReservation(const QString &workspace, const QString &user)
	{
		QJsonObject root = reservationsObject(workspace);
		QJsonObject profiles = root.value(QStringLiteral("profiles")).toObject();
		profiles.remove(userSlug(user));
		root.insert(QStringLiteral("profiles"), profiles);
		root.insert(QStringLiteral("updated_at"), nowIso());
		writeJson(reservationsPath(workspace), root);
	}

	QStringList selectFolios(QWidget *parent, const QString &workspace, const QString &user,
			const QList<JwFolio> &folios, bool *accepted)
	{
		if (accepted)
			*accepted = false;
		if (folios.isEmpty())
			return(QStringList());

		QDialog dialog(parent);
		dialog.setWindowTitle(QObject::tr("Reservar folios colaborativos"));
		dialog.resize(610, 390);
		auto *layout = new QVBoxLayout(&dialog);
		auto *label = new QLabel(
				QObject::tr("Selecciona los folios que editará el perfil %1.\n"
				            "Un folio reservado por otro perfil queda bloqueado para evitar conflictos.").arg(user),
				&dialog);
		label->setWordWrap(true);
		layout->addWidget(label);

		auto *list = new QListWidget(&dialog);
		list->setSelectionMode(QAbstractItemView::NoSelection);
		const QStringList previous = reservedFoliosFor(workspace, user);
		for (const JwFolio &folio : folios)
		{
			const QString owner = reservedOwner(workspace, folio.key, user);
			QString text = folio.label;
			if (!owner.isEmpty())
				text += QObject::tr("    —    EN USO POR %1").arg(owner);
			auto *item = new QListWidgetItem(text, list);
			item->setData(Qt::UserRole, folio.key);
			item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
			if (!owner.isEmpty())
			{
				item->setCheckState(Qt::Unchecked);
				item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
			}
			else
				item->setCheckState(previous.contains(folio.key) ? Qt::Checked : Qt::Unchecked);
		}
		layout->addWidget(list, 1);

		auto *hint = new QLabel(
				QObject::tr("La entrega se bloqueará si modificas un folio que no esté reservado para este perfil."),
				&dialog);
		hint->setWordWrap(true);
		layout->addWidget(hint);

		auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
		buttons->button(QDialogButtonBox::Ok)->setText(QObject::tr("Usar folios seleccionados"));
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
				return(selected);
			}
			QMessageBox::information(&dialog,
					QObject::tr("Sin folios reservados"),
					QObject::tr("Selecciona al menos un folio para este perfil."));
		}
		return(QStringList());
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

	QMap<QString, QByteArray> diagramFingerprints(const QString &path, QString *error_message = nullptr)
	{
		QMap<QString, QByteArray> result;
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly))
		{
			if (error_message)
				*error_message = QObject::tr("No se pudo leer el proyecto para verificar los folios modificados.");
			return(result);
		}
		QDomDocument document;
		QString xml_error;
		int line = 0;
		int column = 0;
		if (!document.setContent(&file, &xml_error, &line, &column))
		{
			if (error_message)
				*error_message = QObject::tr("XML inválido al verificar cambios: %1").arg(xml_error);
			return(result);
		}
		const QDomElement root = document.documentElement();
		int position = 0;
		for (QDomNode node = root.firstChild(); !node.isNull(); node = node.nextSibling())
		{
			if (!node.isElement() || node.toElement().tagName() != QStringLiteral("diagram"))
				continue;
			++position;
			const QDomElement element = node.toElement();
			const QString order = element.attribute(QStringLiteral("order"), QString::number(position));
			QString serialized;
			QTextStream stream(&serialized);
			element.save(stream, 0);
			result.insert(QStringLiteral("order:%1").arg(order),
					QCryptographicHash::hash(serialized.toUtf8(), QCryptographicHash::Sha256));
		}
		return(result);
	}

	QStringList changedFolios(const QString &baseline, const QString &working, QString *error_message = nullptr)
	{
		const QMap<QString, QByteArray> base = diagramFingerprints(baseline, error_message);
		if (base.isEmpty() && error_message && !error_message->isEmpty())
			return(QStringList());
		const QMap<QString, QByteArray> work = diagramFingerprints(working, error_message);
		if (work.isEmpty() && error_message && !error_message->isEmpty())
			return(QStringList());
		QStringList keys = base.keys();
		for (const QString &key : work.keys())
			if (!keys.contains(key))
				keys << key;
		QStringList changed;
		for (const QString &key : keys)
			if (!base.contains(key) || !work.contains(key) || base.value(key) != work.value(key))
				changed << key;
		return(changed);
	}

	bool createOrContinueSession(QETDiagramEditor *editor, const QString &master, const QString &workspace,
			const QString &user, const QStringList &reserved)
	{
		const QString slug = userSlug(user);
		const QString current_master_hash = sha256File(master);
		if (current_master_hash.isEmpty())
		{
			QMessageBox::warning(editor, QObject::tr("No se pudo iniciar la sesión"),
					QObject::tr("No se pudo calcular la firma del proyecto maestro."));
			return(false);
		}

		const QFileInfo master_info(master);
		const QString working_dir = QDir(QDir(workspace).absoluteFilePath(QStringLiteral("02_WORKING"))).absoluteFilePath(slug);
		const QString working_path = QDir(working_dir).absoluteFilePath(master_info.fileName());
		const QString working_manifest_path = manifestForQet(working_path);

		if (QFileInfo::exists(working_path) && QFileInfo::exists(working_manifest_path))
		{
			QJsonObject existing = readJson(working_manifest_path);
			const QString status = existing.value(QStringLiteral("status")).toString();
			const QString existing_master_hash = existing.value(QStringLiteral("master_sha256")).toString();

			if (status == QStringLiteral("submitted"))
			{
				QMessageBox::information(editor,
						QObject::tr("Entrega pendiente"),
						QObject::tr("El perfil %1 ya entregó cambios y está esperando publicación.\n"
						            "Publica o descarta esa entrega antes de continuar editando.").arg(user));
				return(false);
			}

			if (status == QStringLiteral("checked_out") && existing_master_hash == current_master_hash)
			{
				QMessageBox choice(QMessageBox::Question,
						QObject::tr("Sesión colaborativa existente"),
						QObject::tr("El perfil %1 ya tiene una copia de trabajo basada en el maestro actual.").arg(user),
						QMessageBox::NoButton,
						editor);
				choice.setInformativeText(QObject::tr("Puedes continuarla o recrearla desde el maestro. Recrearla descarta cambios locales no entregados."));
				QPushButton *continue_button = choice.addButton(QObject::tr("Continuar copia existente"), QMessageBox::AcceptRole);
				QPushButton *recreate_button = choice.addButton(QObject::tr("Recrear desde maestro"), QMessageBox::DestructiveRole);
				choice.addButton(QObject::tr("Cancelar"), QMessageBox::RejectRole);
				choice.exec();
				if (choice.clickedButton() == continue_button)
				{
					QJsonArray array;
					for (const QString &folio : reserved)
						array.append(folio);
					existing.insert(QStringLiteral("reserved_folios"), array);
					existing.insert(QStringLiteral("last_opened_at"), nowIso());
					writeJson(working_manifest_path, existing);
					setReservation(workspace, user, reserved);
					rememberProfile(workspace, user);
					editor->openAndAddProject(working_path);
					return(true);
				}
				if (choice.clickedButton() != recreate_button)
					return(false);
			}
			else
			{
				const QMessageBox::StandardButton answer = QMessageBox::question(
						editor,
						QObject::tr("Actualizar copia de trabajo"),
						QObject::tr("La copia del perfil %1 pertenece a una versión anterior del maestro.\n"
						            "¿Deseas reemplazarla por el maestro actual?\n\n"
						            "Los cambios locales no entregados de esa copia se perderán.").arg(user),
						QMessageBox::Yes | QMessageBox::Cancel,
						QMessageBox::Cancel);
				if (answer != QMessageBox::Yes)
					return(false);
			}
		}
		else if (QFileInfo::exists(working_path))
		{
			const QMessageBox::StandardButton answer = QMessageBox::warning(
					editor,
					QObject::tr("Copia de trabajo sin manifiesto"),
					QObject::tr("Ya existe una copia para %1 sin manifiesto colaborativo. ¿Reemplazarla desde el maestro?").arg(user),
					QMessageBox::Yes | QMessageBox::Cancel,
					QMessageBox::Cancel);
			if (answer != QMessageBox::Yes)
				return(false);
		}

		const QString internal = hiddenRoot(workspace);
		const QString baseline_dir = QDir(internal).absoluteFilePath(QStringLiteral("baselines"));
		const QString baseline_path = QDir(baseline_dir).absoluteFilePath(
				QStringLiteral("%1_%2").arg(current_master_hash.left(16), master_info.fileName()));
		const QString incoming_dir = QDir(QDir(internal).absoluteFilePath(QStringLiteral("incoming"))).absoluteFilePath(slug);
		const QString incoming_path = QDir(incoming_dir).absoluteFilePath(master_info.fileName());
		const QString logs_dir = QDir(internal).absoluteFilePath(QStringLiteral("logs"));

		QString error_message;
		if (!QFileInfo::exists(baseline_path) && !copyOverwrite(master, baseline_path, &error_message))
		{
			QMessageBox::warning(editor, QObject::tr("No se pudo crear la baseline"), error_message);
			return(false);
		}
		if (!copyOverwrite(master, working_path, &error_message))
		{
			QMessageBox::warning(editor, QObject::tr("No se pudo crear la copia de trabajo"), error_message);
			return(false);
		}

		QJsonArray reserved_array;
		for (const QString &folio : reserved)
			reserved_array.append(folio);

		QJsonObject manifest;
		manifest.insert(QStringLiteral("schema"), kSchema);
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
		manifest.insert(QStringLiteral("incoming_path"), QFileInfo(incoming_path).absoluteFilePath());
		manifest.insert(QStringLiteral("logs_dir"), QFileInfo(logs_dir).absoluteFilePath());
		manifest.insert(QStringLiteral("master_relpath"), relativeToWorkspace(master, workspace));
		manifest.insert(QStringLiteral("baseline_relpath"), relativeToWorkspace(baseline_path, workspace));
		manifest.insert(QStringLiteral("working_relpath"), relativeToWorkspace(working_path, workspace));
		manifest.insert(QStringLiteral("incoming_relpath"), relativeToWorkspace(incoming_path, workspace));
		manifest.insert(QStringLiteral("logs_relpath"), relativeToWorkspace(logs_dir, workspace));
		manifest.insert(QStringLiteral("master_sha256"), current_master_hash);
		manifest.insert(QStringLiteral("baseline_sha256"), sha256File(baseline_path));
		manifest.insert(QStringLiteral("working_sha256"), sha256File(working_path));

		if (!writeJson(working_manifest_path, manifest, &error_message) ||
			!setReservation(workspace, user, reserved, &error_message) ||
			!rememberProfile(workspace, user, &error_message))
		{
			QMessageBox::warning(editor, QObject::tr("No se pudo iniciar la sesión"), error_message);
			return(false);
		}

		QJsonObject log = manifest;
		log.insert(QStringLiteral("manifest_path"), working_manifest_path);
		writeJson(QDir(logs_dir).absoluteFilePath(
				QStringLiteral("%1_checkout_%2.json").arg(timestamp(), slug)), log);

		const bool opened = editor->openAndAddProject(working_path);
		QMessageBox message(QMessageBox::Information,
				QObject::tr("Sesión colaborativa lista"),
				QObject::tr("Perfil: %1\nFolios reservados: %2").arg(user, friendlyFolios(reserved)),
				QMessageBox::Ok,
				editor);
		message.setInformativeText(opened
				? QObject::tr("La copia de trabajo se abrió correctamente.")
				: QObject::tr("La copia fue creada, pero QET no pudo abrirla automáticamente."));
		message.exec();
		return(opened);
	}

	void checkoutWorkflow(QETDiagramEditor *editor)
	{
		const QString master = QFileDialog::getOpenFileName(
				editor,
				QObject::tr("Seleccionar archivo maestro colaborativo"),
				QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
				QObject::tr("Proyectos QElectroTech (*.qet);;Todos los archivos (*)"));
		if (master.isEmpty())
			return;

		QDir default_workspace = QFileInfo(master).absoluteDir();
		if (default_workspace.dirName() == QStringLiteral("00_MASTER"))
			default_workspace.cdUp();
		const QString workspace = QFileDialog::getExistingDirectory(
				editor,
				QObject::tr("Seleccionar carpeta colaborativa"),
				default_workspace.absolutePath());
		if (workspace.isEmpty())
			return;

		bool profile_ok = false;
		const QString user = selectProfile(editor, workspace, &profile_ok);
		if (!profile_ok || user.isEmpty())
			return;

		QString folio_error;
		const QList<JwFolio> folios = foliosFromQet(master, &folio_error);
		if (folios.isEmpty())
		{
			QMessageBox::warning(editor, QObject::tr("No se pudieron listar los folios"), folio_error);
			return;
		}

		bool folios_ok = false;
		const QStringList reserved = selectFolios(editor, workspace, user, folios, &folios_ok);
		if (!folios_ok)
			return;

		createOrContinueSession(editor, master, workspace, user, reserved);
	}

	void submitWorkflow(QETDiagramEditor *editor)
	{
		if (!editor->currentProject())
		{
			QMessageBox::information(editor, QObject::tr("Sin proyecto abierto"),
					QObject::tr("Abre primero una copia de trabajo colaborativa."));
			return;
		}
		const QString working_path = editor->currentProject()->filePath();
		const QString manifest_path = manifestForQet(working_path);
		if (!QFileInfo::exists(manifest_path))
		{
			// Legacy sessions keep using the original submission path.
			editor->submitCollaborativeChanges();
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
		if (status == QStringLiteral("submitted"))
		{
			QMessageBox::information(editor, QObject::tr("Entrega pendiente"),
					QObject::tr("El perfil %1 ya entregó sus cambios. Espera la publicación antes de continuar.").arg(user));
			return;
		}
		if (status == QStringLiteral("refresh_required"))
		{
			QMessageBox::warning(editor, QObject::tr("Copia desactualizada"),
					QObject::tr("El maestro ya fue actualizado. Crea/abre de nuevo la sesión del perfil %1 para trabajar sobre la versión vigente.").arg(user));
			return;
		}

		editor->save();
		QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);

		const QString workspace = workspaceFromPath(working_path);
		const QString baseline = resolveMember(workspace, manifest,
				QStringLiteral("baseline_relpath"), QStringLiteral("baseline_path"));
		if (workspace.isEmpty() || baseline.isEmpty())
		{
			QMessageBox::warning(editor, QObject::tr("No se pudo verificar la entrega"),
					QObject::tr("No se pudo resolver la baseline colaborativa de esta copia."));
			return;
		}

		QString diff_error;
		const QStringList changed = changedFolios(baseline, working_path, &diff_error);
		if (!diff_error.isEmpty())
		{
			QMessageBox::warning(editor, QObject::tr("No se pudo verificar la entrega"), diff_error);
			return;
		}
		if (changed.isEmpty())
		{
			QMessageBox::information(editor, QObject::tr("Sin cambios de folio"),
					QObject::tr("No se detectaron cambios en los folios de esta copia."));
			return;
		}

		QStringList reserved;
		for (const QJsonValue &value : manifest.value(QStringLiteral("reserved_folios")).toArray())
			if (value.isString())
				reserved << value.toString();
		QStringList unauthorized;
		for (const QString &folio : changed)
			if (!reserved.contains(folio))
				unauthorized << folio;
		if (!unauthorized.isEmpty())
		{
			QMessageBox message(QMessageBox::Critical,
					QObject::tr("Edición fuera de los folios reservados"),
					QObject::tr("La entrega fue bloqueada para evitar un conflicto colaborativo."),
					QMessageBox::Ok,
					editor);
			message.setInformativeText(
					QObject::tr("Perfil: %1\nReservados: %2\nModificados sin reserva: %3")
						.arg(user, friendlyFolios(reserved), friendlyFolios(unauthorized)));
			message.exec();
			return;
		}

		QString incoming = resolveMember(workspace, manifest,
				QStringLiteral("incoming_relpath"), QStringLiteral("incoming_path"));
		if (incoming.isEmpty())
			incoming = QDir(QDir(hiddenRoot(workspace)).absoluteFilePath(QStringLiteral("incoming/%1").arg(userSlug(user))))
					.absoluteFilePath(QFileInfo(working_path).fileName());

		QString error_message;
		if (!copyOverwrite(working_path, incoming, &error_message))
		{
			QMessageBox::warning(editor, QObject::tr("No se pudieron entregar los cambios"), error_message);
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
			QMessageBox::warning(editor, QObject::tr("No se pudieron entregar los cambios"), error_message);
			return;
		}

		const QString logs_dir = QDir(hiddenRoot(workspace)).absoluteFilePath(QStringLiteral("logs"));
		QJsonObject log = submitted;
		log.insert(QStringLiteral("manifest_path"), incoming_manifest);
		writeJson(QDir(logs_dir).absoluteFilePath(
				QStringLiteral("%1_submit_%2.json").arg(timestamp(), userSlug(user))), log);

		QMessageBox::information(editor,
				QObject::tr("Cambios entregados"),
				QObject::tr("Perfil: %1\nFolios entregados: %2\n\nLa entrega queda pendiente hasta que se publique el maestro.")
					.arg(user, friendlyFolios(changed)));
	}

	QString findPython()
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
			if (QFileInfo(candidate).isFile())
				return(QFileInfo(candidate).absoluteFilePath());
		return(QStandardPaths::findExecutable(QStringLiteral("python.exe")));
	}

	QString findMergeTool()
	{
		const QString app_dir = QCoreApplication::applicationDirPath();
		const QString current_dir = QDir::currentPath();
		const QStringList names {QStringLiteral("qet_collab_session_v2.py"), QStringLiteral("qet_collab_session.py")};
		for (const QString &name : names)
		{
			const QStringList candidates {
				QDir(current_dir).absoluteFilePath(QStringLiteral("tools/%1").arg(name)),
				QDir(app_dir).absoluteFilePath(QStringLiteral("tools/%1").arg(name)),
				QDir(app_dir).absoluteFilePath(QStringLiteral("../tools/%1").arg(name)),
				QDir(app_dir).absoluteFilePath(QStringLiteral("../../tools/%1").arg(name)),
				QDir(app_dir).absoluteFilePath(QStringLiteral("../../../tools/%1").arg(name))
			};
			for (const QString &candidate : candidates)
				if (QFileInfo(QDir::cleanPath(candidate)).isFile())
					return(QFileInfo(QDir::cleanPath(candidate)).absoluteFilePath());
		}
		return(QString());
	}

	QList<JwDelivery> pendingDeliveries(const QString &workspace)
	{
		QMap<QString, JwDelivery> latest;
		QStringList roots;
		roots << QDir(hiddenRoot(workspace)).absoluteFilePath(QStringLiteral("incoming"));
		roots << QDir(workspace).absoluteFilePath(QStringLiteral("03_INCOMING"));
		const QString current_master_hash = sha256File(masterPath(workspace));

		for (const QString &root_path : roots)
		{
			QDir root(root_path);
			if (!root.exists())
				continue;
			for (const QFileInfo &user_dir_info : root.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name))
			{
				QDir user_dir(user_dir_info.absoluteFilePath());
				const QFileInfoList manifests = user_dir.entryInfoList(
						QStringList() << QStringLiteral("*.jwqet.json"), QDir::Files, QDir::Time);
				for (const QFileInfo &info : manifests)
				{
					const QJsonObject json = readJson(info.absoluteFilePath());
					if (json.value(QStringLiteral("status")).toString() != QStringLiteral("submitted"))
						continue;
					JwDelivery delivery;
					delivery.manifest_path = info.absoluteFilePath();
					delivery.user = json.value(QStringLiteral("user")).toString().trimmed();
					if (delivery.user.isEmpty())
						delivery.user = user_dir_info.fileName();
					delivery.user_slug = json.value(QStringLiteral("user_slug")).toString(userSlug(delivery.user));
					delivery.submitted_at = QDateTime::fromString(json.value(QStringLiteral("submitted_at")).toString(), Qt::ISODate);
					if (!delivery.submitted_at.isValid())
						delivery.submitted_at = info.lastModified();
					delivery.baseline_sha256 = json.value(QStringLiteral("baseline_sha256")).toString();
					delivery.stale = !current_master_hash.isEmpty() && !delivery.baseline_sha256.isEmpty()
							&& delivery.baseline_sha256 != current_master_hash;
					const QString key = delivery.user_slug;
					if (!latest.contains(key) || delivery.submitted_at > latest.value(key).submitted_at)
						latest.insert(key, delivery);
					break;
				}
			}
		}
		QList<JwDelivery> deliveries = latest.values();
		std::sort(deliveries.begin(), deliveries.end(), [](const JwDelivery &a, const JwDelivery &b) {
			return(a.submitted_at > b.submitted_at);
		});
		return(deliveries);
	}

	QStringList selectDeliveries(QWidget *parent, const QList<JwDelivery> &deliveries, bool *accepted)
	{
		if (accepted)
			*accepted = false;
		QDialog dialog(parent);
		dialog.setWindowTitle(QObject::tr("Seleccionar entregas colaborativas"));
		dialog.resize(720, 390);
		auto *layout = new QVBoxLayout(&dialog);
		auto *label = new QLabel(
				QObject::tr("Selecciona las entregas de esta publicación. Las entregas basadas en un maestro anterior aparecen deshabilitadas."),
				&dialog);
		label->setWordWrap(true);
		layout->addWidget(label);
		auto *list = new QListWidget(&dialog);
		list->setSelectionMode(QAbstractItemView::NoSelection);
		layout->addWidget(list, 1);

		QDateTime newest;
		for (const JwDelivery &delivery : deliveries)
			if (!delivery.stale && (!newest.isValid() || delivery.submitted_at > newest))
				newest = delivery.submitted_at;

		for (const JwDelivery &delivery : deliveries)
		{
			QString text = QStringLiteral("%1    —    %2")
					.arg(delivery.user, delivery.submitted_at.toString(QStringLiteral("dd/MM/yyyy HH:mm")));
			if (delivery.stale)
				text += QObject::tr("    —    DESACTUALIZADA");
			auto *item = new QListWidgetItem(text, list);
			item->setData(Qt::UserRole, delivery.manifest_path);
			item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
			if (delivery.stale)
			{
				item->setCheckState(Qt::Unchecked);
				item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
			}
			else
			{
				const bool recent = newest.isValid() && delivery.submitted_at.secsTo(newest) <= 2 * 60 * 60;
				item->setCheckState(recent ? Qt::Checked : Qt::Unchecked);
			}
			item->setToolTip(QDir::toNativeSeparators(delivery.manifest_path));
		}

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
				if ((item->flags() & Qt::ItemIsEnabled) && item->checkState() == Qt::Checked)
					selected << item->data(Qt::UserRole).toString();
			}
			if (!selected.isEmpty())
			{
				if (accepted)
					*accepted = true;
				return(selected);
			}
			QMessageBox::information(&dialog, QObject::tr("Sin entregas seleccionadas"),
					QObject::tr("Selecciona al menos una entrega vigente."));
		}
		return(QStringList());
	}

	JwMergeResult runMerge(const QString &python, const QString &tool, const QStringList &manifests,
			const QString &output, bool dry_run)
	{
		JwMergeResult result;
		QStringList arguments;
		arguments << tool << QStringLiteral("merge") << QStringLiteral("--json");
		if (dry_run)
			arguments << QStringLiteral("--dry-run");
		else
			arguments << QStringLiteral("--force");
		arguments << QStringLiteral("--output") << output;
		arguments << manifests;

		QProcess process;
		process.setProcessChannelMode(QProcess::SeparateChannels);
		process.start(python, arguments);
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

		const QByteArray output_data = process.readAllStandardOutput().trimmed();
		const QString stderr_text = QString::fromLocal8Bit(process.readAllStandardError()).trimmed();
		QJsonParseError parse_error;
		const QJsonDocument document = QJsonDocument::fromJson(output_data, &parse_error);
		if (parse_error.error == QJsonParseError::NoError && document.isObject())
		{
			result.parsed = true;
			result.payload = document.object();
			return(result);
		}
		result.error_message = QString::fromUtf8(output_data).trimmed();
		if (!stderr_text.isEmpty())
		{
			if (!result.error_message.isEmpty())
				result.error_message += QStringLiteral("\n");
			result.error_message += stderr_text;
		}
		return(result);
	}

	QStringList jsonStrings(const QJsonValue &value)
	{
		QStringList result;
		for (const QJsonValue &item : value.toArray())
			if (item.isString())
				result << item.toString();
		return(result);
	}

	QString mergeDetails(const QJsonObject &payload)
	{
		QStringList sections;
		QStringList warnings;
		for (const QString &warning : jsonStrings(payload.value(QStringLiteral("warnings"))))
		{
			const bool routine = warning.contains(QStringLiteral("diferencias globales: modificado global <newdiagrams>"))
					|| warning.contains(QStringLiteral("diferencias globales: modificado global <properties>"))
					|| warning.contains(QStringLiteral("diferencias globales: modificado global <usage>"))
					|| warning.contains(QStringLiteral("folios modificados:"));
			if (!routine)
				warnings << warning;
		}
		const QStringList conflicts = jsonStrings(payload.value(QStringLiteral("conflicts")));
		if (!warnings.isEmpty())
			sections << QObject::tr("Advertencias relevantes:\n%1").arg(warnings.join(QStringLiteral("\n")));
		if (!conflicts.isEmpty())
			sections << QObject::tr("Conflictos:\n%1").arg(conflicts.join(QStringLiteral("\n")));
		return(sections.join(QStringLiteral("\n\n")));
	}

	void markDeliveryPublished(const QString &workspace, const QString &manifest_path, const QString &new_master_hash)
	{
		QJsonObject manifest = readJson(manifest_path);
		if (manifest.isEmpty())
			return;
		const QString user = manifest.value(QStringLiteral("user")).toString();
		manifest.insert(QStringLiteral("status"), QStringLiteral("published"));
		manifest.insert(QStringLiteral("published_at"), nowIso());
		manifest.insert(QStringLiteral("published_master_sha256"), new_master_hash);
		writeJson(manifest_path, manifest);

		const QString working = resolveMember(workspace, manifest,
				QStringLiteral("working_relpath"), QStringLiteral("working_path"));
		if (!working.isEmpty())
		{
			const QString working_manifest_path = manifestForQet(working);
			QJsonObject working_manifest = readJson(working_manifest_path);
			if (!working_manifest.isEmpty())
			{
				working_manifest.insert(QStringLiteral("status"), QStringLiteral("refresh_required"));
				working_manifest.insert(QStringLiteral("published_at"), nowIso());
				working_manifest.insert(QStringLiteral("published_master_sha256"), new_master_hash);
				writeJson(working_manifest_path, working_manifest);
			}
		}
		clearReservation(workspace, user);
	}

	void publishWorkflow(QETDiagramEditor *editor)
	{
		QString workspace;
		if (editor->currentProject())
			workspace = workspaceFromPath(editor->currentProject()->filePath());
		if (workspace.isEmpty())
			workspace = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
		workspace = QFileDialog::getExistingDirectory(editor,
				QObject::tr("Seleccionar carpeta colaborativa para publicar"), workspace);
		if (workspace.isEmpty())
			return;

		const QString master = masterPath(workspace);
		if (master.isEmpty())
		{
			QMessageBox::warning(editor, QObject::tr("Carpeta colaborativa no válida"),
					QObject::tr("No se encontró un proyecto .qet en 00_MASTER."));
			return;
		}

		const QList<JwDelivery> deliveries = pendingDeliveries(workspace);
		if (deliveries.isEmpty())
		{
			QMessageBox::information(editor, QObject::tr("Sin entregas pendientes"),
					QObject::tr("No hay entregas colaborativas pendientes de publicación."));
			return;
		}

		const QString python = findPython();
		const QString tool = findMergeTool();
		if (python.isEmpty() || tool.isEmpty())
		{
			QMessageBox::warning(editor, QObject::tr("Publicación no disponible"),
					QObject::tr("No se encontró el motor colaborativo interno o Python."));
			return;
		}

		for (;;)
		{
			bool accepted = false;
			const QStringList manifests = selectDeliveries(editor, deliveries, &accepted);
			if (!accepted)
				return;

			QStringList users;
			for (const QString &path : manifests)
				users << readJson(path).value(QStringLiteral("user")).toString(QFileInfo(path).dir().dirName());

			const QString temp_dir = QDir(hiddenRoot(workspace)).absoluteFilePath(QStringLiteral("tmp"));
			QDir().mkpath(temp_dir);
			const QString temp_output = QDir(temp_dir).absoluteFilePath(QStringLiteral("merge_%1.qet").arg(timestamp()));

			QApplication::setOverrideCursor(Qt::WaitCursor);
			const JwMergeResult dry = runMerge(python, tool, manifests, temp_output, true);
			QApplication::restoreOverrideCursor();
			if (!dry.parsed)
			{
				QMessageBox::warning(editor, QObject::tr("No se pudo analizar la publicación"), dry.error_message);
				return;
			}

			const QString details = mergeDetails(dry.payload);
			if (!dry.payload.value(QStringLiteral("ok")).toBool(false))
			{
				QMessageBox conflict(QMessageBox::Warning,
						QObject::tr("Conflicto colaborativo detectado"),
						QObject::tr("Las entregas seleccionadas presentan un conflicto."),
						QMessageBox::NoButton,
						editor);
				conflict.setInformativeText(QObject::tr("Usuarios: %1\n\nPuedes cambiar la selección.").arg(users.join(QStringLiteral(", "))));
				if (!details.isEmpty())
					conflict.setDetailedText(details);
				QPushButton *retry = conflict.addButton(QObject::tr("Cambiar selección"), QMessageBox::AcceptRole);
				conflict.addButton(QObject::tr("Cancelar"), QMessageBox::RejectRole);
				conflict.exec();
				if (conflict.clickedButton() == retry)
					continue;
				return;
			}

			const QStringList changed = jsonStrings(dry.payload.value(QStringLiteral("changed_diagrams")));
			QMessageBox confirm(QMessageBox::Question,
					QObject::tr("Actualizar proyecto maestro"),
					QObject::tr("El análisis colaborativo terminó correctamente."),
					QMessageBox::NoButton,
					editor);
			confirm.setInformativeText(
					QObject::tr("Entregas: %1\nFolios a integrar: %2\n\n"
					            "Se actualizará el único proyecto oficial en 00_MASTER.\n"
					            "El maestro anterior se guardará en el historial interno.")
						.arg(users.join(QStringLiteral(", ")),
							 changed.isEmpty() ? QObject::tr("ninguno") : friendlyFolios(changed)));
			if (!details.isEmpty())
				confirm.setDetailedText(details);
			QPushButton *publish_button = confirm.addButton(QObject::tr("Actualizar maestro"), QMessageBox::AcceptRole);
			confirm.addButton(QObject::tr("Cancelar"), QMessageBox::RejectRole);
			confirm.exec();
			if (confirm.clickedButton() != publish_button)
				return;

			QApplication::setOverrideCursor(Qt::WaitCursor);
			const JwMergeResult published = runMerge(python, tool, manifests, temp_output, false);
			QApplication::restoreOverrideCursor();
			if (!published.parsed || !published.payload.value(QStringLiteral("ok")).toBool(false))
			{
				QMessageBox::warning(editor, QObject::tr("No se pudo publicar"),
						published.parsed ? mergeDetails(published.payload) : published.error_message);
				QFile::remove(temp_output);
				return;
			}

			const QString history_dir = QDir(hiddenRoot(workspace)).absoluteFilePath(QStringLiteral("history/master"));
			const QString archive_path = QDir(history_dir).absoluteFilePath(
					QStringLiteral("%1_%2").arg(timestamp(), QFileInfo(master).fileName()));
			QString error_message;
			if (!copyOverwrite(master, archive_path, &error_message) ||
				!replaceAtomically(temp_output, master, &error_message))
			{
				QMessageBox::critical(editor, QObject::tr("No se pudo actualizar el maestro"), error_message);
				QFile::remove(temp_output);
				return;
			}
			QFile::remove(temp_output);

			const QString new_master_hash = sha256File(master);
			for (const QString &manifest : manifests)
				markDeliveryPublished(workspace, manifest, new_master_hash);

			QJsonObject publish_log;
			publish_log.insert(QStringLiteral("published_at"), nowIso());
			publish_log.insert(QStringLiteral("master_path"), master);
			publish_log.insert(QStringLiteral("master_sha256"), new_master_hash);
			QJsonArray users_array;
			for (const QString &user : users)
				users_array.append(user);
			publish_log.insert(QStringLiteral("users"), users_array);
			QJsonArray folios_array;
			for (const QString &folio : changed)
				folios_array.append(folio);
			publish_log.insert(QStringLiteral("folios"), folios_array);
			writeJson(QDir(QDir(hiddenRoot(workspace)).absoluteFilePath(QStringLiteral("logs")))
					.absoluteFilePath(QStringLiteral("%1_publish.json").arg(timestamp())), publish_log);

			QMessageBox success(QMessageBox::Information,
					QObject::tr("Proyecto maestro actualizado"),
					QObject::tr("Se integraron correctamente las entregas seleccionadas en el proyecto oficial."),
					QMessageBox::NoButton,
					editor);
			success.setInformativeText(QDir::toNativeSeparators(master));
			QPushButton *open_button = success.addButton(QObject::tr("Abrir proyecto oficial"), QMessageBox::AcceptRole);
			success.addButton(QObject::tr("Cerrar"), QMessageBox::RejectRole);
			success.exec();
			if (success.clickedButton() == open_button)
				editor->openAndAddProject(master);
			return;
		}
	}

	QString latestWorkingManifest(const QString &workspace, const QString &user)
	{
		QDir directory(QDir(QDir(workspace).absoluteFilePath(QStringLiteral("02_WORKING"))).absoluteFilePath(userSlug(user)));
		const QFileInfoList manifests = directory.entryInfoList(
				QStringList() << QStringLiteral("*.jwqet.json"), QDir::Files, QDir::Time);
		return(manifests.isEmpty() ? QString() : manifests.first().absoluteFilePath());
	}

	QString friendlyStatus(const QString &status)
	{
		if (status == QStringLiteral("checked_out")) return(QObject::tr("trabajando"));
		if (status == QStringLiteral("submitted")) return(QObject::tr("entregado / esperando publicación"));
		if (status == QStringLiteral("refresh_required")) return(QObject::tr("requiere actualizar desde maestro"));
		if (status == QStringLiteral("published")) return(QObject::tr("publicado"));
		return(status.isEmpty() ? QObject::tr("sin sesión activa") : status);
	}

	void showCollabStatus(QETDiagramEditor *editor)
	{
		QString workspace;
		if (editor->currentProject())
			workspace = workspaceFromPath(editor->currentProject()->filePath());
		if (workspace.isEmpty())
			workspace = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
		workspace = QFileDialog::getExistingDirectory(editor, QObject::tr("Seleccionar carpeta colaborativa"), workspace);
		if (workspace.isEmpty())
			return;

		QDialog dialog(editor);
		dialog.setWindowTitle(QObject::tr("Estado colaborativo"));
		dialog.resize(650, 380);
		auto *layout = new QVBoxLayout(&dialog);
		auto *label = new QLabel(QObject::tr("Perfiles, folios reservados y estado de cada copia de trabajo:"), &dialog);
		layout->addWidget(label);
		auto *list = new QListWidget(&dialog);
		layout->addWidget(list, 1);

		const QStringList profiles = profileNames(workspace);
		for (const QString &user : profiles)
		{
			const QStringList folios = reservedFoliosFor(workspace, user);
			const QString manifest_path = latestWorkingManifest(workspace, user);
			const QString status = manifest_path.isEmpty()
					? QString()
					: readJson(manifest_path).value(QStringLiteral("status")).toString();
			new QListWidgetItem(
					QObject::tr("%1    —    %2    —    %3")
						.arg(user,
							 folios.isEmpty() ? QObject::tr("sin folio reservado") : friendlyFolios(folios),
							 friendlyStatus(status)),
					list);
		}
		if (profiles.isEmpty())
			new QListWidgetItem(QObject::tr("Todavía no hay perfiles colaborativos."), list);

		auto *buttons = new QDialogButtonBox(QDialogButtonBox::Close, &dialog);
		buttons->button(QDialogButtonBox::Close)->setText(QObject::tr("Cerrar"));
		QObject::connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
		QObject::connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
		layout->addWidget(buttons);
		dialog.exec();
	}

	void updatePermanentStatus(QETDiagramEditor *editor, QLabel *label)
	{
		if (!editor || !label || !editor->currentProject())
		{
			if (label) label->hide();
			return;
		}
		const QString path = editor->currentProject()->filePath();
		const QString manifest_path = manifestForQet(path);
		if (!QFileInfo::exists(manifest_path))
		{
			label->hide();
			return;
		}
		const QJsonObject manifest = readJson(manifest_path);
		const QString user = manifest.value(QStringLiteral("user")).toString();
		QStringList folios;
		for (const QJsonValue &value : manifest.value(QStringLiteral("reserved_folios")).toArray())
			if (value.isString()) folios << value.toString();
		const QString status = friendlyStatus(manifest.value(QStringLiteral("status")).toString());
		label->setText(QObject::tr("COLAB: %1 · %2 · %3")
				.arg(user,
					 folios.isEmpty() ? QObject::tr("sin reserva") : friendlyFolios(folios),
					 status));
		label->show();
	}

	void installWorkflow(QETDiagramEditor *editor)
	{
		if (!editor || editor->property("jw_collab_workflow_v2_installed").toBool())
			return;

		QAction *checkout_action = nullptr;
		QAction *submit_action = nullptr;
		QAction *publish_action = nullptr;
		for (QAction *action : editor->findChildren<QAction *>())
		{
			if (action->text().contains(QStringLiteral("Crear copia de trabajo colaborativa"), Qt::CaseInsensitive))
				checkout_action = action;
			else if (action->text().contains(QStringLiteral("Entregar cambios colaborativos"), Qt::CaseInsensitive))
				submit_action = action;
			else if (action->text().contains(QStringLiteral("Publicar / fusionar cambios colaborativos"), Qt::CaseInsensitive))
				publish_action = action;
		}
		if (!checkout_action || !submit_action)
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

		QObject::disconnect(checkout_action, nullptr, nullptr, nullptr);
		QObject::disconnect(submit_action, nullptr, nullptr, nullptr);
		QObject::connect(checkout_action, &QAction::triggered, editor, [editor]() { checkoutWorkflow(editor); });
		QObject::connect(submit_action, &QAction::triggered, editor, [editor]() { submitWorkflow(editor); });
		checkout_action->setStatusTip(QObject::tr("Selecciona perfil y reserva folios antes de crear o abrir su copia colaborativa"));
		submit_action->setStatusTip(QObject::tr("Verifica los folios reservados y prepara la entrega colaborativa"));

		if (!publish_action)
		{
			publish_action = new QAction(submit_action->icon(),
					QObject::tr("Publicar / fusionar cambios colaborativos..."), editor);
			const QList<QAction *> actions = file_menu->actions();
			const int submit_index = actions.indexOf(submit_action);
			if (submit_index >= 0 && submit_index + 1 < actions.size())
				file_menu->insertAction(actions.at(submit_index + 1), publish_action);
			else
				file_menu->addAction(publish_action);
		}
		QObject::disconnect(publish_action, nullptr, nullptr, nullptr);
		QObject::connect(publish_action, &QAction::triggered, editor, [editor]() { publishWorkflow(editor); });
		publish_action->setStatusTip(QObject::tr("Fusiona entregas vigentes y actualiza el único proyecto oficial en 00_MASTER"));

		auto *status_action = new QAction(QObject::tr("Ver estado colaborativo..."), editor);
		status_action->setStatusTip(QObject::tr("Muestra perfiles, folios reservados y estado de las sesiones colaborativas"));
		QObject::connect(status_action, &QAction::triggered, editor, [editor]() { showCollabStatus(editor); });
		const QList<QAction *> actions = file_menu->actions();
		const int publish_index = actions.indexOf(publish_action);
		if (publish_index >= 0 && publish_index + 1 < actions.size())
			file_menu->insertAction(actions.at(publish_index + 1), status_action);
		else
			file_menu->addAction(status_action);

		auto *status_label = new QLabel(editor);
		status_label->setObjectName(QStringLiteral("jwCollabStatusLabel"));
		status_label->setMargin(4);
		status_label->hide();
		editor->statusBar()->addPermanentWidget(status_label);
		auto *timer = new QTimer(editor);
		timer->setInterval(1500);
		QObject::connect(timer, &QTimer::timeout, editor, [editor, status_label]() {
			updatePermanentStatus(editor, status_label);
		});
		timer->start();
		updatePermanentStatus(editor, status_label);

		editor->setProperty("jw_collab_workflow_v2_installed", true);
	}

	class JwWorkflowInstaller : public QObject
	{
		public:
			explicit JwWorkflowInstaller(QObject *parent = nullptr) : QObject(parent) {}

		protected:
			bool eventFilter(QObject *watched, QEvent *event) override
			{
				if (event->type() == QEvent::Show)
				{
					if (auto *editor = qobject_cast<QETDiagramEditor *>(watched))
					{
						for (int delay : {0, 150, 500})
							QTimer::singleShot(delay, editor, [editor]() { installWorkflow(editor); });
					}
				}
				return(QObject::eventFilter(watched, event));
			}
	};

	void installJwWorkflow()
	{
		auto *installer = new JwWorkflowInstaller(qApp);
		qApp->installEventFilter(installer);
	}
}

Q_COREAPP_STARTUP_FUNCTION(installJwWorkflow)
