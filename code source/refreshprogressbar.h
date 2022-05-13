#ifndef REFRESHPROGRESSBAR_H
#define REFRESHPROGRESSBAR_H

#include <QObject>
#include <QThread>
#include <QFile>
class RefreshProgressBar : public QThread
{

    Q_OBJECT
public:
    RefreshProgressBar();

    void run() override;
    void getIndexMax();
    int getNrb(QString pathToJson);

private:

};

#endif // REFRESHPROGRESSBAR_H
