/********************************************************************************
** Form generated from reading UI file 'terminalnumberingdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.19
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TERMINALNUMBERINGDIALOG_H
#define UI_TERMINALNUMBERINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TerminalNumberingDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_description;
    QGroupBox *groupBox_axis;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *rb_priority_x;
    QRadioButton *rb_priority_y;
    QGroupBox *groupBox_type;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *rb_type_num;
    QRadioButton *rb_type_alpha;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *TerminalNumberingDialog)
    {
        if (TerminalNumberingDialog->objectName().isEmpty())
            TerminalNumberingDialog->setObjectName(QString::fromUtf8("TerminalNumberingDialog"));
        TerminalNumberingDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(TerminalNumberingDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_description = new QLabel(TerminalNumberingDialog);
        label_description->setObjectName(QString::fromUtf8("label_description"));
        label_description->setWordWrap(true);

        verticalLayout->addWidget(label_description);

        groupBox_axis = new QGroupBox(TerminalNumberingDialog);
        groupBox_axis->setObjectName(QString::fromUtf8("groupBox_axis"));
        verticalLayout_2 = new QVBoxLayout(groupBox_axis);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        rb_priority_x = new QRadioButton(groupBox_axis);
        rb_priority_x->setObjectName(QString::fromUtf8("rb_priority_x"));
        rb_priority_x->setChecked(true);

        verticalLayout_2->addWidget(rb_priority_x);

        rb_priority_y = new QRadioButton(groupBox_axis);
        rb_priority_y->setObjectName(QString::fromUtf8("rb_priority_y"));

        verticalLayout_2->addWidget(rb_priority_y);


        verticalLayout->addWidget(groupBox_axis);

        groupBox_type = new QGroupBox(TerminalNumberingDialog);
        groupBox_type->setObjectName(QString::fromUtf8("groupBox_type"));
        verticalLayout_3 = new QVBoxLayout(groupBox_type);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        rb_type_num = new QRadioButton(groupBox_type);
        rb_type_num->setObjectName(QString::fromUtf8("rb_type_num"));
        rb_type_num->setChecked(true);

        verticalLayout_3->addWidget(rb_type_num);

        rb_type_alpha = new QRadioButton(groupBox_type);
        rb_type_alpha->setObjectName(QString::fromUtf8("rb_type_alpha"));

        verticalLayout_3->addWidget(rb_type_alpha);


        verticalLayout->addWidget(groupBox_type);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(TerminalNumberingDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(TerminalNumberingDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), TerminalNumberingDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TerminalNumberingDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(TerminalNumberingDialog);
    } // setupUi

    void retranslateUi(QDialog *TerminalNumberingDialog)
    {
        TerminalNumberingDialog->setWindowTitle(QCoreApplication::translate("TerminalNumberingDialog", "Num\303\251rotation automatique des bornes", nullptr));
        label_description->setText(QCoreApplication::translate("TerminalNumberingDialog", "Cette fonction num\303\251rote les bornes du projet selon leur position. Les bornes vides ou verrouill\303\251es sont ignor\303\251es.Le marquage des bornes doit \303\252tre configur\303\251 au pr\303\251alable comme suit : '-X:AB'. La partie avant les deux-points (le bornier) peut \303\252tre nomm\303\251e au choix. 'AB' peut \303\252tre compos\303\251 de chiffres ou de lettres.\"", nullptr));
        groupBox_axis->setTitle(QCoreApplication::translate("TerminalNumberingDialog", "Priorit\303\251 des axes", nullptr));
        rb_priority_x->setText(QCoreApplication::translate("TerminalNumberingDialog", "Priorit\303\251 \303\240 l'axe X (horizontal)", nullptr));
        rb_priority_y->setText(QCoreApplication::translate("TerminalNumberingDialog", "Priorit\303\251 \303\240 l'axe Y (vertical)", nullptr));
        groupBox_type->setTitle(QCoreApplication::translate("TerminalNumberingDialog", "Type de num\303\251rotation", nullptr));
        rb_type_num->setText(QCoreApplication::translate("TerminalNumberingDialog", "Num\303\251rique uniquement (1, 2, 3...)", nullptr));
        rb_type_alpha->setText(QCoreApplication::translate("TerminalNumberingDialog", "Alphanum\303\251rique (A, B, C... 1, 2...)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TerminalNumberingDialog: public Ui_TerminalNumberingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TERMINALNUMBERINGDIALOG_H
