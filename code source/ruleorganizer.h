#ifndef RULEORGANIZER_H
#define RULEORGANIZER_H

#include <QDialog>
#include <QtWidgets>
#include "dialog.h"
namespace Ui {
class RuleOrganizer;
}

class RuleOrganizer : public QDialog
{
    Q_OBJECT

public:
    explicit RuleOrganizer(QWidget *parent = nullptr);
    void setList(QList<Rule *> *list, int ruleOrgaOption);

    QLineEdit* setupRuleLabel(Rule *rule, int index);

    ~RuleOrganizer();

signals:
    void si_setRuleOrga(int);

private slots:
    void on_RuleOrganizer_accepted();

private:
    Ui::RuleOrganizer *ui;    
};

#endif // RULEORGANIZER_H
