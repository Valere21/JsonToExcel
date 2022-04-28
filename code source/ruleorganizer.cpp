#include "ruleorganizer.h"
#include "ui_ruleorganizer.h"

RuleOrganizer::RuleOrganizer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RuleOrganizer)
{
    ui->setupUi(this);
//    ui->verticalLayout->setGeometry(parent->geometry());
    qDebug() << Q_FUNC_INFO;
}

QString getRuleSymbol(int symbol){

    QString strSymbol;
    switch (symbol){
    case NaN:
        strSymbol = " is NaN";
        break;
    case Zero:
        strSymbol = " = 0";
        break;
    case One:
        strSymbol = " = 1";
        break;
    case Egal:
        strSymbol = " = ";
        break;
    case Sup:
        strSymbol = " > ";
        break;
    case Inf:
        strSymbol = " < ";
        break;
    case SupEgal:
        strSymbol = " >= ";
        break;
    case InfEgal:
        strSymbol = " <= ";
        break;
    }
    return strSymbol;
}

QString concateneRuleInfo(Rule *rule){

    QString info;
    switch (rule->getOption().optionSel) {
    case Name:
        info.append(rule->getOption().name);
        break;

    case Number:
        info.append(QString::number(rule->getOption().val));
        break;
    default:
        break;
    }
    info.prepend(getRuleSymbol(rule->getRule()));
    info.prepend(rule->getVar());
    return info;
}

QLineEdit* RuleOrganizer::setupRuleLabel(Rule *rule, int index){
    newRuleLabel = new QLineEdit(this);
    newRuleLabel->setGeometry(20,index*45,250,25);
    newRuleLabel->setText(concateneRuleInfo(rule));
    newRuleLabel->setReadOnly(true);
    return newRuleLabel;
}

void RuleOrganizer::setList(QList<Rule*> *list){
    listRule = list;
    for (int i = 0; i < listRule->size(); i++){
        listRuleLabel.append(setupRuleLabel(list->at(i), i));
    }
    show();
}

RuleOrganizer::~RuleOrganizer()
{
    for (int i = 0; i < listRuleLabel.size(); i++){
        delete listRuleLabel.value(i);
        listRuleLabel.replace(i, nullptr);
    }
    delete ui;
}
