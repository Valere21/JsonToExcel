#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);
    this->setWindowTitle("Modification des fichiers JSON en cours");
    show();
    ui_settings = new Settings;
    getPath();    
}

QStringList MainWindow::parseVar(QString readAll){

    QStringList list;

    QString all(readAll);
    QString var;

    all = all.remove(0,1);
    all = all.remove('\\');

    var = all.mid(all.indexOf('{')+1,-1);
    var = var.left(var.indexOf('}')-1);

    all = all.remove(all.indexOf('{')+1,var.size()+1);
    list.append(var);
    list.append(all);

    qDebug() << "1 " << list.at(0) << Qt::endl;
    qDebug() << "2 " << list.at(1)  << Qt::endl;
    qDebug() << "INSERTION" << list.value(0).insert(all.indexOf('{'),list.value(1));

    return list;
}



QString MainWindow::removeUnwantedVariable(QString allContentVariable /*toutes variables JSON*/, QStringList listSelected /*variables JSON selectionees*/){    // Fonction ne laissant que les variables selectionner par l'utilisateur
    QStringList listAll = allContentVariable.split(',');

    QString strModified;
    for (int i = 0; i < listSelected.size(); i++){
        for (int j = 0; j < listAll.size(); j++){
            if (listSelected.at(i).contains(listAll.at(j).left(listAll.at(j).indexOf(':')-1))){
                //                qDebug() << "oui " << listAll.at(j).left(listAll.at(j).indexOf(':')-1);
                strModified.append(listAll.at(j) +',');

            }
        }
    }
    strModified = strModified.remove(strModified.lastIndexOf(','),1);
    return strModified;
}

void MainWindow::addModifiedFile(QString dataModified, QString name){
    name = name.remove(0, name.lastIndexOf('/'));                       //Retire le chemin des fichiers JSON (et ne conserve que le nom du fichier)
    name = name.prepend(m_folderModifiedJSON.path());                   //Ajoute le nouveau chemin
    name = name.replace(name.lastIndexOf('.'),-1, "_MODIFIED");         //Ajoute la mention MODIFIED
    m_fileJSONModified = new QFile(name);
    m_fileJSONModified->open(QIODevice::ReadWrite);
    m_fileJSONModified->write(dataModified.toLocal8Bit());              //Ecrit les donnees JSON corriges
    m_fileJSONModified->close();
    delete m_fileJSONModified;
    m_fileJSONModified = nullptr;
}




void MainWindow::executePythonScript(){     //Execute le script python, pas de probleme la-dessus
    m_processPythonScript = new QProcess();
    QString command = ("python.exe");
    QStringList argument;
    //        argument.append("main.py");
    argument.append("C:\\PycharmProjects\\extractDataJSON\\main.py");       //0
    QString argPathFolderModi = m_folderModifiedJSON.path() + '/';
    argument.append(argPathFolderModi);                                     //1
    argument.append(m_folderExcel + '/');                                         //2
    argument.append(QString::number(QCoreApplication::applicationPid()));
    qDebug() << command + "  0 " + argument.at(0) + "  1 " + argument.at(1) + "   2 " + argument.at(2) + "   3 " + argument.at(3);

    m_processPythonScript->setProgram(command);
    m_processPythonScript->setArguments(argument);
    m_processPythonScript->start();
    connect(m_processPythonScript, SIGNAL(stateChanged(QProcess::ProcessState)), this, SLOT(sl_onProcessStateChanged()));
}

void MainWindow::sl_onProcessStateChanged(){
    qDebug() << "PYTHON FINISHED";
    this->~MainWindow();
}

void MainWindow::on_MainWindow_destroyed()
{
    this->~MainWindow();
}

MainWindow::~MainWindow()
{
    qDebug() << "in";
    delete ui_dialog;
    delete ui_settings;
    delete m_fileJSON;
    delete m_fileJSONModified;
    delete ui;

    delete m_processPythonScript;
    qDebug() << "About to quit";
    QApplication::quit();
    exit(0);
}


