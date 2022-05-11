#include "rule.h"
#include "ui_rule.h"

Rule::Rule(QStringList listVar, QWidget *parent) : QDialog(parent),ui(new Ui::Rule){
    qDebug() << Q_FUNC_INFO;
    ui->setupUi(this);
    setListVar(listVar);
    ui->constRes->setHidden(true);
    ui->listVarRes->setHidden(true);
    ui->getConst->setHidden(true);
    ui->getVar->setHidden(true);

    show();
}

Rule::Rule(QString var, ruleSelected rule, t_option option) : m_var(var), m_rule(rule), m_option(option){

}

void Rule::setListVar(QStringList list){
    for (int i = 0; i < list.size(); i++){
        ui->listVar->addItem(list.at(i));
        ui->listVarRes->addItem(list.at(i));
    }
    on_getVar_clicked(false);
    ui->getVar->setCheckState(Qt::Unchecked);
}

void Rule::on_listVar_currentIndexChanged(const QString &arg1)
{
    m_var = arg1;
}

void Rule::on_listRule_activated(int index){    
    m_rule = (ruleSelected)index;
    if (index >= Egal){
        ui->constRes->setHidden(false);
        ui->listVarRes->setHidden(false);
        ui->getConst->setHidden(false);
        ui->getVar->setHidden(false);
    }
    else {
        ui->constRes->setHidden(true);
        ui->listVarRes->setHidden(true);
        ui->getConst->setHidden(true);
        ui->getVar->setHidden(true);
    }
}


void Rule::on_getVar_clicked(bool checked)
{
    if (checked){
        ui->listVarRes->setDisabled(false);
        ui->constRes->setDisabled(true);
        if (ui->getConst->isChecked()){
            ui->getConst->setCheckState(Qt::Unchecked);
            on_getConst_clicked(false);
        }
    }
    else
        ui->constRes->setDisabled(false);
}

void Rule::on_getConst_clicked(bool checked)
{
    if (checked){
        ui->listVarRes->setDisabled(true);
        ui->constRes->setDisabled(false);
        if (ui->getVar->isChecked()){
            ui->getVar->setCheckState(Qt::Unchecked);
            on_getVar_clicked(false);
        }
    }
    else
        ui->listVarRes->setDisabled(false);
}

void Rule::on_listVarRes_currentIndexChanged(const QString &arg1)
{
    qDebug() << Q_FUNC_INFO << arg1;
    m_option.name = arg1;
    on_getVar_clicked(true);
    ui->getVar->setCheckState(Qt::Checked);
}


void Rule::on_constRes_valueChanged(double arg1)
{
    m_option.val = arg1;
    on_getConst_clicked(true);
    ui->getConst->setCheckState(Qt::Checked);
}

void Rule::on_buttonBox_accepted()
{
    m_option.val = 0;
    m_option.name = "Non";


    if (ui->listRule->currentIndex() >= Egal){
        if (ui->getConst->isChecked()){
            m_option.optionSel = Number;
            m_option.val = ui->constRes->value();
            emit si_sendRuleFilled(m_var,m_rule,m_option);
        }
        else if (ui->getVar->isChecked()){
            m_option.optionSel = Name;
            m_option.name = ui->listVarRes->currentText();
            emit si_sendRuleFilled(m_var,m_rule,m_option);
        }
        else {
            ui->buttonBox->setDisabled(true);
            QMessageBox msgBox;
            msgBox.setText("Vous devez cochez une case");
            msgBox.exec();
        }
    }
    else {
        m_var = ui->listVar->currentText();
        m_rule = (ruleSelected)ui->listRule->currentIndex();
        m_option.optionSel = None;
        emit si_sendRuleFilled(m_var,m_rule,m_option);
    }
}


Rule::~Rule()
{
    delete ui;
}
