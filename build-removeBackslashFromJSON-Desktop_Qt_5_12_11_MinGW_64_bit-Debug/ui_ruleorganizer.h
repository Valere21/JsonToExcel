/********************************************************************************
** Form generated from reading UI file 'ruleorganizer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RULEORGANIZER_H
#define UI_RULEORGANIZER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>

QT_BEGIN_NAMESPACE

class Ui_RuleOrganizer
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *RuleOrganizer)
    {
        if (RuleOrganizer->objectName().isEmpty())
            RuleOrganizer->setObjectName(QString::fromUtf8("RuleOrganizer"));
        RuleOrganizer->resize(400, 300);
        buttonBox = new QDialogButtonBox(RuleOrganizer);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(RuleOrganizer);
        QObject::connect(buttonBox, SIGNAL(accepted()), RuleOrganizer, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RuleOrganizer, SLOT(reject()));

        QMetaObject::connectSlotsByName(RuleOrganizer);
    } // setupUi

    void retranslateUi(QDialog *RuleOrganizer)
    {
        RuleOrganizer->setWindowTitle(QApplication::translate("RuleOrganizer", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RuleOrganizer: public Ui_RuleOrganizer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RULEORGANIZER_H
