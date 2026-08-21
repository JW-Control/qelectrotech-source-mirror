/*
	Copyright 2026 JW Control
	This file is part of the JW Control QElectroTech fork.

	QElectroTech is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.
*/
#ifndef JW_COMPANY_COLLECTION_H
#define JW_COMPANY_COLLECTION_H

#include "ElementsCollection/elementscollectionmodel.h"
#include "ElementsCollection/fileelementcollectionitem.h"
#include "elementspanel.h"
#include "elementspanelwidget.h"
#include "genericpanel.h"
#include "qetapp.h"

#include <QApplication>
#include <QDir>
#include <QDirIterator>
#include <QEvent>
#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QSettings>
#include <QTimer>
#include <QTreeWidgetItem>

namespace JWCompanyCollection
{
	inline QString canonicalRelativePath()
	{
		return QStringLiteral(
			"01_JW_CONTROL/06_INGENIERIA_Y_DESARROLLO/02_LIBRERIAS/JW_QET/COLLECTION_COMPANY");
	}

	inline QString existingDirectory(const QString &path)
	{
		if (path.trimmed().isEmpty() || path == QStringLiteral("default"))
			return {};
		QDir directory(QDir::fromNativeSeparators(path));
		if (!directory.exists())
			return {};
		return QDir::cleanPath(directory.absolutePath());
	}

	inline QString candidateFromDriveRoot(const QString &drive_root, const QString &prefix)
	{
		QDir root(drive_root);
		const QString candidate = root.absoluteFilePath(
			prefix.isEmpty()
				? canonicalRelativePath()
				: prefix + QLatin1Char('/') + canonicalRelativePath());
		return existingDirectory(candidate);
	}

	inline QString detectCanonicalPath(const QString &configured_path = QString())
	{
		// Respect an explicit, currently valid path. This lets a user keep a
		// deliberately different company collection without JW-QET overriding it.
		const QString configured = existingDirectory(configured_path);
		if (!configured.isEmpty())
			return configured;

		// If the configured path came from another PC/drive letter, preserve the
		// portion before 01_JW_CONTROL when possible and try every mounted drive.
		QString configured_prefix;
		const QString normalized = QDir::fromNativeSeparators(configured_path);
		const QString marker = QStringLiteral("/01_JW_CONTROL/");
		const int marker_index = normalized.indexOf(marker, 0, Qt::CaseInsensitive);
		if (marker_index >= 0)
		{
			configured_prefix = normalized.left(marker_index);
			const int slash = configured_prefix.indexOf(QLatin1Char('/'));
			if (slash >= 0)
				configured_prefix = configured_prefix.mid(slash + 1);
		}

		const QStringList common_drive_prefixes {
			configured_prefix,
			QStringLiteral("Mi unidad"),
			QStringLiteral("My Drive"),
			QString()
		};

		for (const QFileInfo &drive : QDir::drives())
		{
			for (const QString &prefix : common_drive_prefixes)
			{
				const QString candidate = candidateFromDriveRoot(drive.absoluteFilePath(), prefix);
				if (!candidate.isEmpty())
					return candidate;
			}
		}
		return {};
	}

	inline void prepareSettings()
	{
		QSettings settings;
		const QString key = QStringLiteral("elements-collections/company-collection-path");
		const QString configured = settings.value(key, QStringLiteral("default")).toString();
		const QString detected = detectCanonicalPath(configured);
		if (detected.isEmpty())
			return;

		if (QDir::cleanPath(QDir::fromNativeSeparators(configured)) != detected)
		{
			settings.setValue(key, QDir::toNativeSeparators(detected));
			settings.setValue(QStringLiteral("jw-control/company-collection-autodetected"), true);
			settings.sync();
		}
	}

	class Manager final : public QObject
	{
		public:
			explicit Manager(QObject *parent = nullptr) : QObject(parent)
		{
			m_reload_timer.setSingleShot(true);
			m_reload_timer.setInterval(1200);
			connect(&m_reload_timer, &QTimer::timeout, this, [this]() {
				rebuildWatchList();
				reloadPanels();
			});

			m_decorate_timer.setInterval(1200);
			connect(&m_decorate_timer, &QTimer::timeout, this, [this]() {
				decorateAll();
			});
			m_decorate_timer.start();

			connect(&m_watcher, &QFileSystemWatcher::directoryChanged,
				this, [this](const QString &) { scheduleReload(); });
			connect(&m_watcher, &QFileSystemWatcher::fileChanged,
				this, [this](const QString &) { scheduleReload(); });

			qApp->installEventFilter(this);
			QTimer::singleShot(0, this, [this]() {
				rebuildWatchList();
				decorateAll();
			});
		}

		protected:
			bool eventFilter(QObject *watched, QEvent *event) override
			{
				Q_UNUSED(watched)
				if (event->type() == QEvent::Show)
					QTimer::singleShot(250, this, [this]() { decorateAll(); });
				return QObject::eventFilter(watched, event);
			}

		private:
			QString companyPath() const
			{
				return QETApp::companyElementsDirN();
			}

			void scheduleReload()
			{
				m_reload_timer.start();
			}

			void rebuildWatchList()
			{
				const QString path = companyPath();
				if (path == m_last_path && QFileInfo(path).isDir() && !m_watcher.directories().isEmpty())
					return;

				const QStringList old_dirs = m_watcher.directories();
				if (!old_dirs.isEmpty())
					m_watcher.removePaths(old_dirs);
				const QStringList old_files = m_watcher.files();
				if (!old_files.isEmpty())
					m_watcher.removePaths(old_files);

				m_last_path = path;
				if (!QFileInfo(path).isDir())
					return;

				QStringList dirs { path };
				QStringList files;
				QDirIterator iterator(path,
					QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot,
					QDirIterator::Subdirectories);
				while (iterator.hasNext())
				{
					iterator.next();
					const QFileInfo info = iterator.fileInfo();
					if (info.isDir())
						dirs << info.absoluteFilePath();
					else if (info.suffix().compare(QStringLiteral("elmt"), Qt::CaseInsensitive) == 0
							 || info.fileName() == QStringLiteral("qet_directory"))
						files << info.absoluteFilePath();
				}
				if (!dirs.isEmpty())
					m_watcher.addPaths(dirs);
				if (!files.isEmpty())
					m_watcher.addPaths(files);
			}

			void reloadPanels()
			{
				for (ElementsPanelWidget *widget : qApp->findChildren<ElementsPanelWidget *>())
					widget->reloadAndFilter();
				QTimer::singleShot(450, this, [this]() { decorateAll(); });
				QTimer::singleShot(1200, this, [this]() { decorateAll(); });
			}

			void decorateTreePanels()
			{
				const QString path = companyPath();
				const bool available = QFileInfo(path).isDir();
				const QString label = available
					? QObject::tr("Colección JW Control · Disponible")
					: QObject::tr("Colección JW Control · No disponible");
				const QString tooltip = available
					? QObject::tr("Biblioteca compartida JW Control disponible en:\n%1")
						.arg(QDir::toNativeSeparators(path))
					: QObject::tr("La biblioteca compartida JW Control no está disponible en esta PC.\n%1")
						.arg(QDir::toNativeSeparators(path));

				for (ElementsPanel *panel : qApp->findChildren<ElementsPanel *>())
				{
					for (int row = 0; row < panel->topLevelItemCount(); ++row)
					{
						QTreeWidgetItem *item = panel->topLevelItem(row);
						if (!item)
							continue;

						bool is_company = false;
						const QVariant value = item->data(0, GenericPanel::Item);
						if (value.canConvert<ElementsLocation>())
							is_company = value.value<ElementsLocation>().isCompanyCollection();

						if (!is_company)
						{
							const QString text = item->text(0);
							is_company = text.contains(QStringLiteral("Company collection"), Qt::CaseInsensitive)
								|| text.contains(QStringLiteral("Collection Company"), Qt::CaseInsensitive)
								|| text.contains(QStringLiteral("colección company"), Qt::CaseInsensitive);
						}

						if (is_company)
						{
							item->setText(0, label);
							item->setToolTip(0, tooltip);
						}
					}
				}
			}

			void decorateModels()
			{
				const QString path = companyPath();
				const bool available = QFileInfo(path).isDir();
				const QString label = available
					? QObject::tr("Colección JW Control · Disponible")
					: QObject::tr("Colección JW Control · No disponible");
				const QString tooltip = available
					? QObject::tr("Biblioteca compartida JW Control disponible en:\n%1")
						.arg(QDir::toNativeSeparators(path))
					: QObject::tr("La biblioteca compartida JW Control no está disponible en esta PC.\n%1")
						.arg(QDir::toNativeSeparators(path));

				for (ElementsCollectionModel *model : qApp->findChildren<ElementsCollectionModel *>())
				{
					for (int row = 0; row < model->rowCount(); ++row)
					{
						QStandardItem *raw = model->item(row);
						if (!raw || raw->type() != FileElementCollectionItem::Type)
							continue;
						auto *item = static_cast<FileElementCollectionItem *>(raw);
						if (!item->isCompanyCollection())
							continue;
						item->setText(label);
						item->setToolTip(tooltip);
					}
				}
			}

			void decorateAll()
			{
				decorateTreePanels();
				decorateModels();
			}

		private:
			QFileSystemWatcher m_watcher;
			QTimer m_reload_timer;
			QTimer m_decorate_timer;
			QString m_last_path;
	};

	inline void install(QETApp *app)
	{
		if (!app || app->property("jw_company_collection_manager_installed").toBool())
			return;
		new Manager(app);
		app->setProperty("jw_company_collection_manager_installed", true);
	}
}

#endif // JW_COMPANY_COLLECTION_H
