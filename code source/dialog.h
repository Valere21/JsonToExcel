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
    void si_sendSelectedVar(QStringList);
    void si_quitApp();
    void si_isAllSelected(bool);
private slots:

    void sl_getListVar(QString list);
    void sl_getNewRuleOrga(int);
    void sl_getRuleFilled(QString, ruleSelected, t_option);

    void on_buttonBox_accepted();
    void on_pushButton_clicked();
    void on_buttonBox_rejected();
    void on_addRule_clicked();
    void on_toolButton_clicked();


private:
    Ui::Dialog *ui;
    RuleOrganizer *ui_ruleOrganizer = nullptr;
    Rule *ui_rule = nullptr;

    QList<Rule*> *m_listRule = nullptr;
    int m_ruleOrgaOption = 0;

    QStringList m_listVarData;
    QStringList m_listVar;

};

#endif // DIALOG_H
