/********************************************************************************
** Form generated from reading UI file 'ruleorganizer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RULEORGANIZER_H
#define UI_RULEORGANIZER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RuleOrganizer
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *RuleOrganizer)
    {
        if (RuleOrganizer->objectName().isEmpty())
            RuleOrganizer->setObjectName(QString::fromUtf8("RuleOrganizer"));
        RuleOrganizer->resize(400, 300);
        widget = new QWidget(RuleOrganizer);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(140, 250, 249, 30));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        comboBox = new QComboBox(widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        buttonBox = new QDialogButtonBox(widget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        retranslateUi(RuleOrganizer);
        QObject::connect(buttonBox, SIGNAL(accepted()), RuleOrganizer, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RuleOrganizer, SLOT(reject()));

        QMetaObject::connectSlotsByName(RuleOrganizer);
    } // setupUi

    void retranslateUi(QDialog *RuleOrganizer)
    {
        RuleOrganizer->setWindowTitle(QCoreApplication::translate("RuleOrganizer", "Dialog", nullptr));
        comboBox->setItemText(0, QString());
        comboBox->setItemText(1, QCoreApplication::translate("RuleOrganizer", "ET", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("RuleOrganizer", "OU", nullptr));

    } // retranslateUi

};

namespace Ui {
    class RuleOrganizer: public Ui_RuleOrganizer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RULEORGANIZER_H
