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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RuleOrganizer
{
public:
    QVBoxLayout *verticalLayout;
    QListView *listView;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *RuleOrganizer)
    {
        if (RuleOrganizer->objectName().isEmpty())
            RuleOrganizer->setObjectName(QString::fromUtf8("RuleOrganizer"));
        RuleOrganizer->resize(230, 138);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RuleOrganizer->sizePolicy().hasHeightForWidth());
        RuleOrganizer->setSizePolicy(sizePolicy);
        RuleOrganizer->setMinimumSize(QSize(0, 0));
        verticalLayout = new QVBoxLayout(RuleOrganizer);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout->setContentsMargins(-1, -1, -1, 9);
        listView = new QListView(RuleOrganizer);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        verticalLayout->addWidget(listView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        comboBox = new QComboBox(RuleOrganizer);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        buttonBox = new QDialogButtonBox(RuleOrganizer);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(RuleOrganizer);
        QObject::connect(buttonBox, SIGNAL(accepted()), RuleOrganizer, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RuleOrganizer, SLOT(reject()));

        QMetaObject::connectSlotsByName(RuleOrganizer);
    } // setupUi

    void retranslateUi(QDialog *RuleOrganizer)
    {
        RuleOrganizer->setWindowTitle(QCoreApplication::translate("RuleOrganizer", "Dialog", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("RuleOrganizer", "ET", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("RuleOrganizer", "OU", nullptr));

    } // retranslateUi

};

namespace Ui {
    class RuleOrganizer: public Ui_RuleOrganizer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RULEORGANIZER_H
