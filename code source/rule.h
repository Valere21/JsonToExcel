#ifndef RULE_H
#define RULE_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>

class Dialog;

namespace Ui {
class Rule;
}


class Rule : public QDialog
{
    Q_OBJECT

public:

    typedef struct OPTION{
        float val;
        QString name;
    }t_option;

    enum rule {
        NaN,
        Zero,
        One,
        Egal,
        Inf,
        Sup,
        InfEgal,
        SupEgal
    };

    explicit Rule(QStringList listVar, QWidget *parent = nullptr);
    Rule(QString var, int rule, t_option option);
    ~Rule();

    void setListVar(QStringList list);

    void setVar();
    void setRule();
    void setOption();

signals:
    void si_sendRuleFilled(QString var, int rule, t_option option);
private slots:

    void on_listRule_activated(int index);
    void on_buttonBox_accepted();
    void on_getVar_clicked(bool checked);
    void on_getConst_clicked(bool checked);

private:
    Ui::Rule *ui;

    QString m_var;
    int m_rule;
    t_option m_option;

};

#endif // RULE_H
