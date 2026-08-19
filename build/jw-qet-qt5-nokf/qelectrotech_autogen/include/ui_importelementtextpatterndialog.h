/********************************************************************************
** Form generated from reading UI file 'importelementtextpatterndialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.19
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMPORTELEMENTTEXTPATTERNDIALOG_H
#define UI_IMPORTELEMENTTEXTPATTERNDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ImportElementTextPatternDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *m_label;
    QComboBox *m_combo_box;
    QCheckBox *m_erase_existing_text;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ImportElementTextPatternDialog)
    {
        if (ImportElementTextPatternDialog->objectName().isEmpty())
            ImportElementTextPatternDialog->setObjectName(QString::fromUtf8("ImportElementTextPatternDialog"));
        ImportElementTextPatternDialog->resize(187, 116);
        verticalLayout = new QVBoxLayout(ImportElementTextPatternDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_label = new QLabel(ImportElementTextPatternDialog);
        m_label->setObjectName(QString::fromUtf8("m_label"));

        verticalLayout->addWidget(m_label);

        m_combo_box = new QComboBox(ImportElementTextPatternDialog);
        m_combo_box->setObjectName(QString::fromUtf8("m_combo_box"));

        verticalLayout->addWidget(m_combo_box);

        m_erase_existing_text = new QCheckBox(ImportElementTextPatternDialog);
        m_erase_existing_text->setObjectName(QString::fromUtf8("m_erase_existing_text"));

        verticalLayout->addWidget(m_erase_existing_text);

        buttonBox = new QDialogButtonBox(ImportElementTextPatternDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ImportElementTextPatternDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ImportElementTextPatternDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ImportElementTextPatternDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ImportElementTextPatternDialog);
    } // setupUi

    void retranslateUi(QDialog *ImportElementTextPatternDialog)
    {
        ImportElementTextPatternDialog->setWindowTitle(QCoreApplication::translate("ImportElementTextPatternDialog", "Dialog", nullptr));
        m_label->setText(QCoreApplication::translate("ImportElementTextPatternDialog", "TextLabel", nullptr));
        m_erase_existing_text->setText(QCoreApplication::translate("ImportElementTextPatternDialog", "\303\211craser les textes existants", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImportElementTextPatternDialog: public Ui_ImportElementTextPatternDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPORTELEMENTTEXTPATTERNDIALOG_H
