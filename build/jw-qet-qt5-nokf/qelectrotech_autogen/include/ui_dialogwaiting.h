/********************************************************************************
** Form generated from reading UI file 'dialogwaiting.ui'
**
** Created by: Qt User Interface Compiler version 5.15.19
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGWAITING_H
#define UI_DIALOGWAITING_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogWaiting
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *labelTitle;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QProgressBar *progressBar;
    QLabel *label_detail;

    void setupUi(QDialog *DialogWaiting)
    {
        if (DialogWaiting->objectName().isEmpty())
            DialogWaiting->setObjectName(QString::fromUtf8("DialogWaiting"));
        DialogWaiting->resize(400, 110);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app/process"), QSize(), QIcon::Normal, QIcon::Off);
        DialogWaiting->setWindowIcon(icon);
        verticalLayout_2 = new QVBoxLayout(DialogWaiting);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelTitle = new QLabel(DialogWaiting);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        labelTitle->setTextFormat(Qt::AutoText);
        labelTitle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelTitle);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(DialogWaiting);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(24, 24));
        label->setAutoFillBackground(false);
        label->setPixmap(QPixmap(QString::fromUtf8(":/ico/48x48/user-away-extended.png")));
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        progressBar = new QProgressBar(DialogWaiting);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        horizontalLayout->addWidget(progressBar);


        verticalLayout->addLayout(horizontalLayout);

        label_detail = new QLabel(DialogWaiting);
        label_detail->setObjectName(QString::fromUtf8("label_detail"));

        verticalLayout->addWidget(label_detail);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(DialogWaiting);

        QMetaObject::connectSlotsByName(DialogWaiting);
    } // setupUi

    void retranslateUi(QDialog *DialogWaiting)
    {
        DialogWaiting->setWindowTitle(QCoreApplication::translate("DialogWaiting", "Merci de patienter", nullptr));
        labelTitle->setText(QCoreApplication::translate("DialogWaiting", "Titre", nullptr));
        label->setText(QString());
        label_detail->setText(QCoreApplication::translate("DialogWaiting", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogWaiting: public Ui_DialogWaiting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGWAITING_H
