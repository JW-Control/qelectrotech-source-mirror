/********************************************************************************
** Form generated from reading UI file 'imagepropertieswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.19
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEPROPERTIESWIDGET_H
#define UI_IMAGEPROPERTIESWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImagePropertiesWidget
{
public:
    QGridLayout *gridLayout;
    QCheckBox *m_lock_pos_cb;
    QLabel *label;
    QSlider *m_scale_slider;
    QSpinBox *m_scale_sb;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *ImagePropertiesWidget)
    {
        if (ImagePropertiesWidget->objectName().isEmpty())
            ImagePropertiesWidget->setObjectName(QString::fromUtf8("ImagePropertiesWidget"));
        ImagePropertiesWidget->resize(244, 105);
        gridLayout = new QGridLayout(ImagePropertiesWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
        m_lock_pos_cb = new QCheckBox(ImagePropertiesWidget);
        m_lock_pos_cb->setObjectName(QString::fromUtf8("m_lock_pos_cb"));

        gridLayout->addWidget(m_lock_pos_cb, 2, 0, 1, 1);

        label = new QLabel(ImagePropertiesWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        m_scale_slider = new QSlider(ImagePropertiesWidget);
        m_scale_slider->setObjectName(QString::fromUtf8("m_scale_slider"));
        m_scale_slider->setMinimum(1);
        m_scale_slider->setMaximum(400);
        m_scale_slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(m_scale_slider, 1, 0, 1, 1);

        m_scale_sb = new QSpinBox(ImagePropertiesWidget);
        m_scale_sb->setObjectName(QString::fromUtf8("m_scale_sb"));
        m_scale_sb->setMinimum(1);
        m_scale_sb->setMaximum(400);

        gridLayout->addWidget(m_scale_sb, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 1);


        retranslateUi(ImagePropertiesWidget);
        QObject::connect(m_scale_slider, SIGNAL(valueChanged(int)), m_scale_sb, SLOT(setValue(int)));
        QObject::connect(m_scale_sb, SIGNAL(valueChanged(int)), m_scale_slider, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(ImagePropertiesWidget);
    } // setupUi

    void retranslateUi(QWidget *ImagePropertiesWidget)
    {
        ImagePropertiesWidget->setWindowTitle(QCoreApplication::translate("ImagePropertiesWidget", "Form", nullptr));
        m_lock_pos_cb->setText(QCoreApplication::translate("ImagePropertiesWidget", "Verrouiller la position", nullptr));
        label->setText(QCoreApplication::translate("ImagePropertiesWidget", "Dimension de l'image", nullptr));
        m_scale_sb->setSuffix(QCoreApplication::translate("ImagePropertiesWidget", "%", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImagePropertiesWidget: public Ui_ImagePropertiesWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEPROPERTIESWIDGET_H
