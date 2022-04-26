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
    qDebug() << "HERE" << list;
    m_listVar = list;
    splitList();
}

void Dialog::splitList(){
    while (m_listVar.contains(':')){
        //        qDebug() << "while" << m_listVar;
        QString *data = new QString (m_listVar.left(m_listVar.indexOf(':')));
        ui->listWidget->addItem(*data);

        delete data;
        data = nullptr;
        if (m_listVar.contains(','))
            m_listVar = m_listVar.remove(0,m_listVar.indexOf(',')+1);
        else
            break;
    }
}

void Dialog::on_buttonBox_accepted()
{
    if  (!m_listVar.isEmpty())
        m_listVar.clear();

    if  (!m_realListVar.isEmpty())
        m_realListVar.clear();

    for (int i = 0; i < ui->listWidget->count(); i++){
        if (ui->listWidget->item(i)->isSelected()){
            m_listVar += ui->listWidget->item(i)->text();
            m_realListVar += ui->listWidget->item(i)->text();
        }
    }
    qDebug() << "m_listVar" << m_listVar;
    qDebug() << "m_listVar size" << m_listVar.size();

//    emit si_sendSelectedVar(m_listVar);
    emit si_sendSelectedVar(m_realListVar);

}


void Dialog::on_pushButton_clicked()
{
    if  (!m_listVar.isEmpty())
        m_listVar.clear();
    for (int i = 0; i < ui->listWidget->count(); i++){
    m_listVar += ui->listWidget->item(i)->text();
    m_realListVar += ui->listWidget->item(i)->text();

    }
    emit si_sendSelectedVar(m_realListVar);
}


void Dialog::on_buttonBox_rejected()
{
    emit si_quitApp();
}

