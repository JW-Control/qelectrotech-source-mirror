/********************************************************************************
** Form generated from reading UI file 'shapegraphicsitempropertieswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.19
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHAPEGRAPHICSITEMPROPERTIESWIDGET_H
#define UI_SHAPEGRAPHICSITEMPROPERTIESWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "kcolorbutton.h"

QT_BEGIN_NAMESPACE

class Ui_ShapeGraphicsItemPropertiesWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    KColorButton *m_color_kpb;
    QDoubleSpinBox *m_size_dsb;
    QComboBox *m_style_cb;
    QGroupBox *m_filling_gb;
    QGridLayout *gridLayout;
    QComboBox *m_brush_style_cb;
    QLabel *label_4;
    QLabel *label_5;
    KColorButton *m_brush_color_kpb;
    QCheckBox *m_lock_pos_cb;
    QCheckBox *m_close_polygon;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *ShapeGraphicsItemPropertiesWidget)
    {
        if (ShapeGraphicsItemPropertiesWidget->objectName().isEmpty())
            ShapeGraphicsItemPropertiesWidget->setObjectName(QString::fromUtf8("ShapeGraphicsItemPropertiesWidget"));
        ShapeGraphicsItemPropertiesWidget->resize(245, 311);
        verticalLayout = new QVBoxLayout(ShapeGraphicsItemPropertiesWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(ShapeGraphicsItemPropertiesWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        m_color_kpb = new KColorButton(groupBox);
        m_color_kpb->setObjectName(QString::fromUtf8("m_color_kpb"));

        gridLayout_2->addWidget(m_color_kpb, 2, 1, 1, 1);

        m_size_dsb = new QDoubleSpinBox(groupBox);
        m_size_dsb->setObjectName(QString::fromUtf8("m_size_dsb"));
        m_size_dsb->setMaximumSize(QSize(16777212, 16777215));
        m_size_dsb->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        m_size_dsb->setAccelerated(true);
        m_size_dsb->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        m_size_dsb->setDecimals(1);
        m_size_dsb->setMinimum(0.200000000000000);
        m_size_dsb->setMaximum(50.000000000000000);
        m_size_dsb->setSingleStep(0.200000000000000);
        m_size_dsb->setValue(1.000000000000000);

        gridLayout_2->addWidget(m_size_dsb, 1, 1, 1, 1);

        m_style_cb = new QComboBox(groupBox);
        m_style_cb->addItem(QString());
        m_style_cb->addItem(QString());
        m_style_cb->addItem(QString());
        m_style_cb->addItem(QString());
        m_style_cb->addItem(QString());
        m_style_cb->addItem(QString());
        m_style_cb->setObjectName(QString::fromUtf8("m_style_cb"));

        gridLayout_2->addWidget(m_style_cb, 0, 1, 1, 1);


        verticalLayout->addWidget(groupBox);

        m_filling_gb = new QGroupBox(ShapeGraphicsItemPropertiesWidget);
        m_filling_gb->setObjectName(QString::fromUtf8("m_filling_gb"));
        gridLayout = new QGridLayout(m_filling_gb);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_brush_style_cb = new QComboBox(m_filling_gb);
        m_brush_style_cb->addItem(QString());
        m_brush_style_cb->addItem(QString());
        m_brush_style_cb->addItem(QString());
        m_brush_style_cb->addItem(QString());
        m_brush_style_cb->addItem(QString());
        m_brush_style_cb->addItem(QString());
        m_brush_style_cb->addItem(QString());
        m_brush_style_cb->addItem(QString());
        m_brush_style_cb->addItem(QString());
        m_brush_style_cb->addItem(QString());
        m_brush_style_cb->addItem(QString());
        m_brush_style_cb->addItem(QString());
        m_brush_style_cb->addItem(QString());
        m_brush_style_cb->addItem(QString());
        m_brush_style_cb->addItem(QString());
        m_brush_style_cb->setObjectName(QString::fromUtf8("m_brush_style_cb"));

        gridLayout->addWidget(m_brush_style_cb, 0, 1, 1, 1);

        label_4 = new QLabel(m_filling_gb);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        label_5 = new QLabel(m_filling_gb);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        m_brush_color_kpb = new KColorButton(m_filling_gb);
        m_brush_color_kpb->setObjectName(QString::fromUtf8("m_brush_color_kpb"));

        gridLayout->addWidget(m_brush_color_kpb, 1, 1, 1, 1);


        verticalLayout->addWidget(m_filling_gb);

        m_lock_pos_cb = new QCheckBox(ShapeGraphicsItemPropertiesWidget);
        m_lock_pos_cb->setObjectName(QString::fromUtf8("m_lock_pos_cb"));

        verticalLayout->addWidget(m_lock_pos_cb);

        m_close_polygon = new QCheckBox(ShapeGraphicsItemPropertiesWidget);
        m_close_polygon->setObjectName(QString::fromUtf8("m_close_polygon"));

        verticalLayout->addWidget(m_close_polygon);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        QWidget::setTabOrder(m_style_cb, m_size_dsb);
        QWidget::setTabOrder(m_size_dsb, m_color_kpb);
        QWidget::setTabOrder(m_color_kpb, m_brush_style_cb);
        QWidget::setTabOrder(m_brush_style_cb, m_brush_color_kpb);
        QWidget::setTabOrder(m_brush_color_kpb, m_lock_pos_cb);
        QWidget::setTabOrder(m_lock_pos_cb, m_close_polygon);

        retranslateUi(ShapeGraphicsItemPropertiesWidget);

        QMetaObject::connectSlotsByName(ShapeGraphicsItemPropertiesWidget);
    } // setupUi

    void retranslateUi(QWidget *ShapeGraphicsItemPropertiesWidget)
    {
        ShapeGraphicsItemPropertiesWidget->setWindowTitle(QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Trait", nullptr));
        label->setText(QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Type", nullptr));
        label_2->setText(QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "\303\211paisseur", nullptr));
        label_3->setText(QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Couleur", nullptr));
        m_style_cb->setItemText(0, QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Normal", nullptr));
        m_style_cb->setItemText(1, QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Tiret", nullptr));
        m_style_cb->setItemText(2, QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Pointill\303\251", nullptr));
        m_style_cb->setItemText(3, QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Traits et points", nullptr));
        m_style_cb->setItemText(4, QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Traits points points", nullptr));
        m_style_cb->setItemText(5, QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Tiret custom", nullptr));

        m_filling_gb->setTitle(QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Remplissage", nullptr));
        m_brush_style_cb->setItemText(0, QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Aucun", nullptr));
        m_brush_style_cb->setItemText(1, QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Plein", nullptr));
        m_brush_style_cb->setItemText(2, QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Densit\303\251 1", nullptr));
        m_brush_style_cb->setItemText(3, QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Densit\303\251 2", nullptr));
        m_brush_style_cb->setItemText(4, QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Densit\303\251 3", nullptr));
        m_brush_style_cb->setItemText(5, QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Densit\303\251 4", nullptr));
        m_brush_style_cb->setItemText(6, QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Densit\303\251 5", nullptr));
        m_brush_style_cb->setItemText(7, QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Densit\303\251 6", nullptr));
        m_brush_style_cb->setItemText(8, QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Densit\303\251 7", nullptr));
        m_brush_style_cb->setItemText(9, QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Horizontal", nullptr));
        m_brush_style_cb->setItemText(10, QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Vertical", nullptr));
        m_brush_style_cb->setItemText(11, QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Croix", nullptr));
        m_brush_style_cb->setItemText(12, QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Diagonal arri\303\250re", nullptr));
        m_brush_style_cb->setItemText(13, QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Diagonal avant", nullptr));
        m_brush_style_cb->setItemText(14, QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Diagonal en croix", nullptr));

        label_4->setText(QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Style", nullptr));
        label_5->setText(QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Couleur", nullptr));
        m_lock_pos_cb->setText(QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Verrouiller la position", nullptr));
        m_close_polygon->setText(QCoreApplication::translate("ShapeGraphicsItemPropertiesWidget", "Polygone ferm\303\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShapeGraphicsItemPropertiesWidget: public Ui_ShapeGraphicsItemPropertiesWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHAPEGRAPHICSITEMPROPERTIESWIDGET_H
