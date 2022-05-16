#ifndef REFRESHPROGRESSBAR_H
#define REFRESHPROGRESSBAR_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QFile>
class RefreshProgressBar : public QThread
{

    Q_OBJECT
public:
    RefreshProgressBar(QStringList listJSON);

    void run() override;
    void getIndexMax(QStringList listJSON);
    int getNbr(QString pathToJson);

signals:

    void si_getThreadUpdatePercent(int newPercent);
    void si_getThreadMaxIndex(int maxIndex);

private:

    QStringList m_listJSON;
};

#endif // REFRESHPROGRESSBAR_H
