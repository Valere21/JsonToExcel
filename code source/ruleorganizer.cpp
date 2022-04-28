#include "ruleorganizer.h"
#include "ui_ruleorganizer.h"

RuleOrganizer::RuleOrganizer(QWidget *parent): QDialog(parent)
{
    ui->setupUi(this);
}

void RuleOrganizer::setList(QList<Rule*> list){
    qDebug() << Q_FUNC_INFO;
    listRule = list;
    for (int i = 0; i < listRule.size(); i++){
        newRuleLabel = new QLineEdit("aaa");
    }
}



RuleOrganizer::~RuleOrganizer()
{
    delete ui;
}
