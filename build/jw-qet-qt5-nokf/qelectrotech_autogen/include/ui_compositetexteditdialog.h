/********************************************************************************
** Form generated from reading UI file 'compositetexteditdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.19
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPOSITETEXTEDITDIALOG_H
#define UI_COMPOSITETEXTEDITDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_CompositeTextEditDialog
{
public:
    QGridLayout *gridLayout;
    QComboBox *m_info_cb;
    QLabel *label;
    QDialogButtonBox *m_button_box;
    QPlainTextEdit *m_plain_text_edit;

    void setupUi(QDialog *CompositeTextEditDialog)
    {
        if (CompositeTextEditDialog->objectName().isEmpty())
            CompositeTextEditDialog->setObjectName(QString::fromUtf8("CompositeTextEditDialog"));
        CompositeTextEditDialog->resize(664, 538);
        gridLayout = new QGridLayout(CompositeTextEditDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_info_cb = new QComboBox(CompositeTextEditDialog);
        m_info_cb->setObjectName(QString::fromUtf8("m_info_cb"));

        gridLayout->addWidget(m_info_cb, 0, 1, 1, 1);

        label = new QLabel(CompositeTextEditDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        m_button_box = new QDialogButtonBox(CompositeTextEditDialog);
        m_button_box->setObjectName(QString::fromUtf8("m_button_box"));
        m_button_box->setOrientation(Qt::Horizontal);
        m_button_box->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(m_button_box, 2, 0, 1, 2);

        m_plain_text_edit = new QPlainTextEdit(CompositeTextEditDialog);
        m_plain_text_edit->setObjectName(QString::fromUtf8("m_plain_text_edit"));

        gridLayout->addWidget(m_plain_text_edit, 1, 0, 1, 2);


        retranslateUi(CompositeTextEditDialog);
        QObject::connect(m_button_box, SIGNAL(accepted()), CompositeTextEditDialog, SLOT(accept()));
        QObject::connect(m_button_box, SIGNAL(rejected()), CompositeTextEditDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CompositeTextEditDialog);
    } // setupUi

    void retranslateUi(QDialog *CompositeTextEditDialog)
    {
        CompositeTextEditDialog->setWindowTitle(QCoreApplication::translate("CompositeTextEditDialog", "Texte compos\303\251", nullptr));
        label->setText(QCoreApplication::translate("CompositeTextEditDialog", "Ajouter une variable :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CompositeTextEditDialog: public Ui_CompositeTextEditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPOSITETEXTEDITDIALOG_H
