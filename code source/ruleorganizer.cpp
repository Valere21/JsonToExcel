#include "ruleorganizer.h"
#include "ui_ruleorganizer.h"

RuleOrganizer::RuleOrganizer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RuleOrganizer)
{
    ui->setupUi(this);
    ui->horizontalLayout->setEnabled(false);
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

void RuleOrganizer::setList(QList<Rule*> *listRule, int ruleOrgaOption){

    ui->comboBox->setCurrentIndex(ruleOrgaOption);

    QStringList strList;
    for (int i  = 0; i < listRule->size(); i++){
        strList.append(concateneRuleInfo(listRule->at(i)));
        qDebug() << concateneRuleInfo(listRule->at(i));
    }

    QStringListModel* model = new QStringListModel(this);
    model->setStringList(strList);
    ui->listView->setModel(model);
    ui->listView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    ui->listView->adjustSize();
    //    ui->listView->setMinimumSize(ui->listView->size());
    ui->verticalLayout->setGeometry(ui->listView->geometry());

    show();
}

RuleOrganizer::~RuleOrganizer()
{
    delete ui;
}

void RuleOrganizer::on_RuleOrganizer_accepted()
{
    emit si_setRuleOrga(ui->comboBox->currentIndex());
}

