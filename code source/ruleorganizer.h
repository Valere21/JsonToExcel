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

    void setList(QList<Rule*> list);

    ~RuleOrganizer();

private:
    Ui::RuleOrganizer *ui;
    QList<Rule*> listRule;
    QLineEdit *newRuleLabel;
};

#endif // RULEORGANIZER_H
