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
    void setList(QList<Rule *> *list);

    QLineEdit* setupRuleLabel(Rule *rule, int index);

    ~RuleOrganizer();

private:
    Ui::RuleOrganizer *ui;
    QList<Rule*> *listRule = nullptr;
    QLineEdit *newRuleLabel = nullptr;

    QList<QLineEdit*> listRuleLabel;
};

#endif // RULEORGANIZER_H
