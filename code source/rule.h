#ifndef RULE_H
#define RULE_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class Rule;
}

enum optionSelect {
    None,
    Number,
    Var
};

enum ruleSelected {
    NaN,
    Zero,
    One,
    Egal,
    Inf,
    Sup,
    InfEgal,
    SupEgal
};

typedef struct OPTION{
    float val;
    QString name;
    optionSelect optionSel;
}t_option;

class Rule : public QDialog
{
    Q_OBJECT

public:


    explicit Rule(QStringList listVar, QWidget *parent = nullptr);
    Rule(QString var, ruleSelected rule, t_option option);
    ~Rule();

    void setListVar(QStringList list);

    void setVar(QString str){m_var = str;}
    void setRule(ruleSelected rule){m_rule = rule;}
    void setOption(t_option option){m_option = option;}

    QString getVar(){return m_var;}
    ruleSelected getRule(){return m_rule;}
    t_option getOption(){return m_option;}

signals:
    void si_sendRuleFilled(QString var, ruleSelected rule, t_option option);
private slots:

    void on_listRule_activated(int index);
    void on_buttonBox_accepted();
    void on_getVar_clicked(bool checked);
    void on_getConst_clicked(bool checked);
    void on_listVar_currentIndexChanged(const QString &arg1);
    void on_listVarRes_currentIndexChanged(const QString &arg1);
    void on_constRes_valueChanged(double arg1);

private:
    Ui::Rule *ui;

    QString m_var;
    ruleSelected m_rule;
    t_option m_option;
};

#endif // RULE_H
