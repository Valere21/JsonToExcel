/********************************************************************************
** Form generated from reading UI file 'rule.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RULE_H
#define UI_RULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Rule
{
public:
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QComboBox *listVar;
    QComboBox *listRule;
    QGridLayout *gridLayout;
    QDoubleSpinBox *constRes;
    QComboBox *listVarRes;
    QCheckBox *getConst;
    QCheckBox *getVar;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Rule)
    {
        if (Rule->objectName().isEmpty())
            Rule->setObjectName(QString::fromUtf8("Rule"));
        Rule->resize(349, 123);
        gridLayout_3 = new QGridLayout(Rule);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        listVar = new QComboBox(Rule);
        listVar->setObjectName(QString::fromUtf8("listVar"));

        horizontalLayout->addWidget(listVar);

        listRule = new QComboBox(Rule);
        listRule->addItem(QString());
        listRule->addItem(QString());
        listRule->addItem(QString());
        listRule->addItem(QString());
        listRule->addItem(QString());
        listRule->addItem(QString());
        listRule->addItem(QString());
        listRule->addItem(QString());
        listRule->setObjectName(QString::fromUtf8("listRule"));

        horizontalLayout->addWidget(listRule);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        constRes = new QDoubleSpinBox(Rule);
        constRes->setObjectName(QString::fromUtf8("constRes"));
        constRes->setDecimals(6);
        constRes->setMinimum(-99999.000000000000000);
        constRes->setMaximum(9999.000000000000000);

        gridLayout->addWidget(constRes, 0, 0, 1, 1);

        listVarRes = new QComboBox(Rule);
        listVarRes->setObjectName(QString::fromUtf8("listVarRes"));

        gridLayout->addWidget(listVarRes, 1, 0, 1, 1);

        getConst = new QCheckBox(Rule);
        getConst->setObjectName(QString::fromUtf8("getConst"));

        gridLayout->addWidget(getConst, 0, 1, 1, 1);

        getVar = new QCheckBox(Rule);
        getVar->setObjectName(QString::fromUtf8("getVar"));

        gridLayout->addWidget(getVar, 1, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        verticalLayout_3->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(Rule);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_3->addWidget(buttonBox);


        gridLayout_3->addLayout(verticalLayout_3, 0, 0, 1, 1);


        retranslateUi(Rule);
        QObject::connect(buttonBox, SIGNAL(rejected()), Rule, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), Rule, SLOT(accept()));

        QMetaObject::connectSlotsByName(Rule);
    } // setupUi

    void retranslateUi(QDialog *Rule)
    {
        Rule->setWindowTitle(QCoreApplication::translate("Rule", "Dialog", nullptr));
        listRule->setItemText(0, QCoreApplication::translate("Rule", "NaN", nullptr));
        listRule->setItemText(1, QCoreApplication::translate("Rule", "0", nullptr));
        listRule->setItemText(2, QCoreApplication::translate("Rule", "1", nullptr));
        listRule->setItemText(3, QCoreApplication::translate("Rule", "=", nullptr));
        listRule->setItemText(4, QCoreApplication::translate("Rule", "<", nullptr));
        listRule->setItemText(5, QCoreApplication::translate("Rule", ">", nullptr));
        listRule->setItemText(6, QCoreApplication::translate("Rule", "<=", nullptr));
        listRule->setItemText(7, QCoreApplication::translate("Rule", ">=", nullptr));

        getConst->setText(QString());
        getVar->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Rule: public Ui_Rule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RULE_H
