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
#include "qetapp.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

/**
	@brief BackupDialog::BackupDialog
	@param parent parent widget
*/
BackupDialog::BackupDialog(QWidget *parent) :
	QDialog(parent)
{
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
