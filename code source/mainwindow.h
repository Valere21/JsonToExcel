#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidgetItem>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QDebug>
#include <QPair>
#include <QFile>
#include <QDir>

#include "rule.h"
#include "dialog.h"
#include "settings.h"
#include "ui_mainwindow.h"


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
    void addModifiedFile(QString dataModified, QString name);      //Ecrit la version modifi� des fichiers JSON  dans une copie + ajoute le nom du fichier en fct de la date
    void emptyJsonFolder();                                        //Vide le dossier JSONModified une fois le traitement effectuer
    QString removeUnwantedVariable(QString allContentVariable, QStringList listSelected);

    ~MainWindow();

signals:
    void    si_sendListVar(QString list);

public slots:
    void sl_getSelectedVar(QStringList);
    void sl_quitApp(){this->~MainWindow();}

private slots:
    void on_MainWindow_destroyed();
    void sl_onProcessStateChanged();
private:
        Ui::MainWindow *ui = nullptr;
    Dialog *ui_dialog = nullptr;
    Settings *ui_settings = nullptr;

    Rule **m_listRule = nullptr;

    QFile *m_fileJSON = nullptr;
    QFile *m_fileJSONModified = nullptr;
    QProcess *m_processPythonScript = nullptr;
    QListWidgetItem *m_listWidgetItem = nullptr;

    QDir m_folderJSON;
    QStringList m_listVar;
    QStringList m_listJSON;
    QString m_folderExcel;
    QDir m_folderModifiedJSON;

};

#endif // MAINWINDOW_H


