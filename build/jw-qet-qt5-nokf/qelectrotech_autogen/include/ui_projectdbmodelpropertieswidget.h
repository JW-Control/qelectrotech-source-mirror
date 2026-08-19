/********************************************************************************
** Form generated from reading UI file 'projectdbmodelpropertieswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.19
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTDBMODELPROPERTIESWIDGET_H
#define UI_PROJECTDBMODELPROPERTIESWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectDBModelPropertiesWidget
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *m_edit_query_pb;
    QPushButton *m_refresh_pb;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *ProjectDBModelPropertiesWidget)
    {
        if (ProjectDBModelPropertiesWidget->objectName().isEmpty())
            ProjectDBModelPropertiesWidget->setObjectName(QString::fromUtf8("ProjectDBModelPropertiesWidget"));
        ProjectDBModelPropertiesWidget->resize(106, 92);
        verticalLayout = new QVBoxLayout(ProjectDBModelPropertiesWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_edit_query_pb = new QPushButton(ProjectDBModelPropertiesWidget);
        m_edit_query_pb->setObjectName(QString::fromUtf8("m_edit_query_pb"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ico/16x16/edit-rename.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_edit_query_pb->setIcon(icon);

        verticalLayout->addWidget(m_edit_query_pb);

        m_refresh_pb = new QPushButton(ProjectDBModelPropertiesWidget);
        m_refresh_pb->setObjectName(QString::fromUtf8("m_refresh_pb"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ico/16x16/view-refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_refresh_pb->setIcon(icon1);

        verticalLayout->addWidget(m_refresh_pb);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(ProjectDBModelPropertiesWidget);

        QMetaObject::connectSlotsByName(ProjectDBModelPropertiesWidget);
    } // setupUi

    void retranslateUi(QWidget *ProjectDBModelPropertiesWidget)
    {
        ProjectDBModelPropertiesWidget->setWindowTitle(QCoreApplication::translate("ProjectDBModelPropertiesWidget", "Form", nullptr));
        m_edit_query_pb->setText(QCoreApplication::translate("ProjectDBModelPropertiesWidget", "Requ\303\252te", nullptr));
        m_refresh_pb->setText(QCoreApplication::translate("ProjectDBModelPropertiesWidget", "Recharger", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectDBModelPropertiesWidget: public Ui_ProjectDBModelPropertiesWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTDBMODELPROPERTIESWIDGET_H
