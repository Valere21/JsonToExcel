#include "rule.h"
#include "ui_rule.h"

Rule::Rule(QStringList listVar, QWidget *parent) :
    QDialog(parent),ui(new Ui::Rule){
    qDebug() << Q_FUNC_INFO;
    ui->setupUi(this);
    setListVar(listVar);
    ui->constRes->setHidden(true);
    ui->listVarRes->setHidden(true);
    ui->getConst->setHidden(true);
    ui->getVar->setHidden(true);

    show();
}

void Rule::setListVar(QStringList list){
    for (int i = 0; i < list.size(); i++){
        ui->listVar->addItem(list.at(i));
        ui->listVarRes->addItem(list.at(i));
    }
}

void Rule::on_listRule_activated(int index){

    if (index >= Egal){
        qDebug() << Q_FUNC_INFO << index;
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

Rule::~Rule()
{
    delete ui;
}

void Rule::on_buttonBox_accepted()
{
    if (ui->listRule->currentIndex() >= Egal){
        if (ui->getConst->isChecked()){
            m_option.val = ui->constRes->value();
            emit si_sendRuleFilled(m_var,m_rule,m_option);
        }
        else if (ui->getVar->isChecked()){
            m_option.name = ui->listVar->currentText();
            emit si_sendRuleFilled(m_var,m_rule,m_option);
        }
        else {
            QMessageBox msgBox;
            msgBox.setText("Vous devez cochez une case");
            msgBox.exec();
        }
    }
    else {
        m_var = ui->listVar->currentText();
        m_rule = ui->listRule->currentIndex();
        emit si_sendRuleFilled(m_var,m_rule,m_option);
    }
}

void Rule::on_getVar_clicked(bool checked)
{
    if (checked){
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
        if (ui->getVar->isChecked()){
            ui->getVar->setCheckState(Qt::Unchecked);
            on_getVar_clicked(false);
        }
    }
    else
        ui->listVarRes->setDisabled(false);
}









