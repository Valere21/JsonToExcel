#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class Dialog;
}

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
    void on_buttonBox_accepted();

    void on_pushButton_clicked();

    void on_buttonBox_rejected();

private:
    Ui::Dialog *ui;
    QString m_listVar;
    QStringList m_realListVar;

};

#endif // DIALOG_H
