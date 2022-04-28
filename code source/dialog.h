#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>

#include "rule.h"
#include "ruleorganizer.h"

namespace Ui {
class Dialog;
}

class RuleOrganizer;

class Dialog : public QDialog
{

    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);

    void splitList();
     QList<Rule*>* getListRule(){return m_listRule;}

    ~Dialog();

signals :
    void    si_sendSelectedVar(QStringList);
    void    si_quitApp();

private slots:

    void sl_getListVar(QString list);
    void on_buttonBox_accepted();
    void on_pushButton_clicked();
    void on_buttonBox_rejected();
    void on_addRule_clicked();
    void on_toolButton_clicked();

    void sl_getRuleFilled(QString, ruleSelected, t_option);


private:
    Ui::Dialog *ui;
    RuleOrganizer *ui_ruleOrganizer = nullptr;
    Rule *ui_rule = nullptr;
    QList<Rule*> *m_listRule = nullptr;


    QStringList m_listVarData;
    QStringList m_listVar;

};

#endif // DIALOG_H
