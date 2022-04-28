#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    show();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::sl_getListVar(QString list){
    m_listVarData = list.split(',');
    splitList();
}

void Dialog::splitList(){
    for (int i = 0; i < m_listVarData.size(); i++){
        m_listVar.append(m_listVarData.at(i).left(m_listVarData.at(i).indexOf(':')));
        ui->listWidget->addItem(m_listVar.at(i));
    }
}

void Dialog::on_buttonBox_accepted()
{
    QStringList listSelected;
    for (int i = 0; i < ui->listWidget->count(); i++){
        if (ui->listWidget->item(i)->isSelected()){
            listSelected += ui->listWidget->item(i)->text();
        }
    }
    emit si_sendSelectedVar(listSelected);
}


void Dialog::on_pushButton_clicked()
{
    QStringList listSelected;
    for (int i = 0; i < ui->listWidget->count(); i++){
        listSelected += ui->listWidget->item(i)->text();
    }
    emit si_sendSelectedVar(listSelected);
}

void Dialog::on_addRule_clicked()
{
    if (ui_rule){
        delete ui_rule;
        ui_rule = nullptr;
    }
    ui_rule = new Rule(m_listVar);
//    connect(ui_rule, SIGNAL(si_sendRuleFilled(QString, ruleSelected, t_option)), this, SLOT(sl_getRuleFilled(QString, ruleSelected, t_option)));
    connect(ui_rule, SIGNAL(si_sendRuleFilled(QString, ruleSelected, t_option)), this->parent(), SLOT(sl_getRuleFilled(QString, ruleSelected, t_option)));
}


void Dialog::on_toolButton_clicked()
{
    if (ui_ruleOrganizer){
        delete ui_ruleOrganizer;
        ui_ruleOrganizer = nullptr;
    }
    ui_ruleOrganizer = new RuleOrganizer;
qDebug() << Q_FUNC_INFO;
    ui_ruleOrganizer->setList(m_listRule);
}

void Dialog::on_buttonBox_rejected()
{
    emit si_quitApp();
}
