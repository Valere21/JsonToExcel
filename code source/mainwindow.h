#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define AND 0
#define OR  1

#include <QListWidgetItem>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QThread>
#include <QDebug>
#include <QPair>
#include <QFile>
#include <QDir>

#include "rule.h"
#include "dialog.h"
#include "settings.h"
#include "ui_mainwindow.h"
#include "refreshprogressbar.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void executePythonScript();
    bool askSettings();
    void setPath();
    void getPath();                                                  //  Obtient le chemins des fichiers JSON
    void getVar();                                                  //Obtient le nom des variables contenue dans la balise "content" des fichiers. Elles sont s�l�ctionable par l'utilisateur
    void formatFile(QStringList listSelectedVar);                                      //Formate les fichiers JSON afin de retirer les acolades et guillemets en trop dans les fichiers (formatage n�cessaire pour bonne lecture ensuite dans le script python)
    bool isFileAccepted(QStringList dataWithVar);                               //Rnevoie true si le fichier vérifie les règles (et contient toutes les variables des règles).
    void addModifiedFile(QString dataModified, QString name);      //Ecrit la version modifiee des fichiers JSON  dans une copie + ajoute le nom du fichier en fct de la date
    void emptyJsonFolder();                                        //Vide le dossier JSONModified une fois le traitement effectuer
    QStringList parseVar(QString readAll);

    ~MainWindow();

signals:
    void    si_sendListVar(QString list);

public slots:
    void sl_getSelectedVar(QStringList);
    void sl_quitApp(){this->~MainWindow();}
    void sl_isAllSelected(bool);
    void sl_isAndOr(bool);

//    void sl_getThreadUpdatePercent(int newPercent);
//    void sl_getThreadMaxIndex(int maxIndex);

    void sl_getThreadIndex(int size, int index);

private slots:
    void on_MainWindow_destroyed();
    void sl_onProcessStateChanged();   
private:
    Ui::MainWindow *ui = nullptr;
    Dialog *ui_dialog = nullptr;
    Settings *ui_settings = nullptr;

     QList<Rule*> *m_listRuleSelect = nullptr;

    QFile *m_fileJSON = nullptr;
    QFile *m_fileJSONModified = nullptr;
    QProcess *m_processPythonScript = nullptr;

//    QThread *m_threadGetIndexSize = nullptr;
    RefreshProgressBar *m_thread = nullptr;
    RefreshProgressBar *m_threadGetIndexSize = nullptr;

    QDir m_folderJSON;
    QStringList m_listVar;
    QStringList m_listJSON;
    QString m_folderExcel;
    QDir m_folderModifiedJSON;

    bool m_isAllSelected = false;
    bool m_isAndOr = 0;

    int m_currentIndexThread = 0;
    int m_currentSizeMaxThread = 0;

};

#endif // MAINWINDOW_H


