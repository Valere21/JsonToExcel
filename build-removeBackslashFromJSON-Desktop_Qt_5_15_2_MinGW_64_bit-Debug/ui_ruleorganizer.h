/********************************************************************************
** Form generated from reading UI file 'ruleorganizer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RuleOrganizer
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QDialogButtonBox *buttonBox;
    QComboBox *comboBox;

    void setupUi(QDialog *RuleOrganizer)
    {
        if (RuleOrganizer->objectName().isEmpty())
            RuleOrganizer->setObjectName(QString::fromUtf8("RuleOrganizer"));
        RuleOrganizer->resize(492, 74);
        RuleOrganizer->setLayoutDirection(Qt::LeftToRight);
        verticalLayoutWidget = new QWidget(RuleOrganizer);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(300, 0, 195, 80));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        buttonBox = new QDialogButtonBox(verticalLayoutWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);

        comboBox = new QComboBox(verticalLayoutWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout_2->addWidget(comboBox, 0, Qt::AlignLeft|Qt::AlignVCenter);


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
