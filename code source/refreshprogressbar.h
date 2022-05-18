#ifndef REFRESHPROGRESSBAR_H
#define REFRESHPROGRESSBAR_H

#define SIMPLE_THREAD   0
#define MULTIPLE_THREAD 1

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QFile>
class RefreshProgressBar : public QObject
{

    Q_OBJECT
public:
    explicit RefreshProgressBar(QString pathJson, int numeroThread) : m_fileJson(pathJson), m_numeroThread(numeroThread){}
//    explicit RefreshProgressBar(QString pathJson, int numeroThread) : m_fileJson(pathJson), m_numeroThread(numeroThread){};

//    void run() override;
    void getIndex();

signals:

    void si_getThreadIndex(int index, int numeroThread);

private:
    QFile m_fileJson;
    float m_numeroThread = 0;
};

#endif // REFRESHPROGRESSBAR_H
