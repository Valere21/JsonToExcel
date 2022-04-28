#include "ruleorganizer.h"
#include "ui_ruleorganizer.h"

RuleOrganizer::RuleOrganizer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RuleOrganizer)
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;
}

void RuleOrganizer::setList(QList<Rule*> *list){
    qDebug() << "POS 2" << list->size() << list;
    listRule = list;
    for (int i = 0; i < listRule->size(); i++){
        qDebug() << "index " << i;
        newRuleLabel = new QLineEdit("aaa");
        qDebug() << newRuleLabel;
    }
    show();
}

RuleOrganizer::~RuleOrganizer()
{
    delete ui;
}
