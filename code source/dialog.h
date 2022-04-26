#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>

#include "rule.h"

namespace Ui {
class Dialog;
}

class Rule;

class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = nullptr);

    void splitList();


    ~Dialog();

signals :
    void    si_sendSelectedVar(QStringList);
    void    si_quitApp();

private slots:

    void sl_getListVar(QString list);
    void sl_getRuleFilled(QString var, int, Rule::t_option option);

    void on_buttonBox_accepted();
    void on_pushButton_clicked();
    void on_buttonBox_rejected();
    void on_addRule_clicked();

private:
    Ui::Dialog *ui;
    Rule *ui_rule = nullptr;
    QList<Rule> *m_listRule;
    QStringList m_listVarData;
    QStringList m_listVar;

};

#endif // DIALOG_H
