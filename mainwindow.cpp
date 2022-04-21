#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);
    this->setWindowTitle("Modification des fichiers JSON en cours");
    show();

    settings = new Settings;
    getPath();
}

bool MainWindow::askSettings(){                                 //fonction permettant de recuperer les chemins des dossier JSON a modifier + dossier Excel, depuis le fichier de sauvegarde
    bool flag = false;
    QMessageBox msgBox;
    msgBox.setText("Utiliser les parametres par defaut ?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    //    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.exec();
    if (msgBox.exec() == QMessageBox::No){
        setPath();
        flag = true;
    }
    return flag;
}

void MainWindow::setPath(){
    m_folderJSON.setPath(QFileDialog::getExistingDirectory(0, ("Select folder wich contains JSON file"), QDir::currentPath()));
    if (m_folderJSON.path().isNull() || m_folderJSON.isEmpty()){
        QMessageBox msgBox;
        msgBox.setText("Dossier vide");
        msgBox.exec();
        this->~MainWindow();
    }
    m_folderExcel = QFileDialog::getExistingDirectory(0, ("Select a folder for the excel"), QDir::currentPath()); m_folderExcel.append('/');
    if (m_folderExcel.isNull()){
        QMessageBox msgBox;
        msgBox.setText("Erreur avec le dossier");
        msgBox.exec();
        this->~MainWindow();
    }
}

void MainWindow::getPath(){     //Recupere le path des fichiers JSON selectionee
    if (!settings->getSettings().isEmpty()){
        if (!askSettings()){
            m_folderJSON.setPath(settings->getSettings().at(1));
            m_folderExcel = settings->getSettings().at(0);
        }
    }
    else {
        setPath();
        settings->setSettings(m_folderJSON.path() + '/',m_folderExcel);
    }
    m_listJSON = m_folderJSON.entryList(QDir::Files, QDir::Name);
    m_folderModifiedJSON.setPath(QApplication::applicationDirPath() + "/tempJSON\\");
    if (m_folderModifiedJSON.exists())
        m_folderModifiedJSON.removeRecursively();
    m_folderModifiedJSON.mkdir(QApplication::applicationDirPath() + "/tempJSON\\");
    if (!m_folderModifiedJSON.exists())
        qDebug() << "probleme de creation dossier JSON modifie (AKA tempJSON)";
    for (int i = 0; i < m_listJSON.size(); i++) m_listJSON[i] = m_folderJSON.path() + '/' + m_listJSON[i];

    getVar();
}
void MainWindow::getVar(){              //Fonction permettant d'isoler les variables s�l�ctionn�s par l'utilisateur (oui c'est un copi� coller de la fonction format file, oui c'est pas opti, oui c'est moche, c'est moche hein)
    dialog = new Dialog;
    connect (dialog, SIGNAL(si_quitApp()), this, SLOT(sl_quitApp()));
    connect(this, SIGNAL(si_sendListVar(QString)), dialog, SLOT(sl_getListVar(QString)));
    connect (dialog, SIGNAL(si_sendSelectedVar(QStringList)), this, SLOT(sl_getSelectedVar(QStringList)));
    if (m_listJSON.isEmpty()){
        qDebug() << "mlistJSON empty";
        this->~MainWindow();
    }
    m_fileJSON = new QFile(m_listJSON.at(0));
    if (m_fileJSON->exists()){                           //Ouvre les fichiers afin de manipuler leurs donnee
        qDebug() << "exist";
        QString *allData = new QString;                  //Contient toute les donn�es JSON
        QString *midData = new QString;                 //Contient les donn�es corrig�s () et "
        QString *varData = new QString;                                //Contient uniquement les variables contenu dans la balise "content" des fichiers JSON
        if (!m_fileJSON->isOpen()){                              //Verifie que le fichier existe
            m_fileJSON->open(QIODevice::ReadWrite);
        }

        *allData = m_fileJSON->readAll();                       //Permet des manipulations sur les données des fichiers JSON
        *allData = allData->remove('\\');                               //Enlèvre les '\'
        *midData = allData->remove(0,1);                        // Enl�ve le premier char car c'est un {. Le second { est celui qui nous int�resse car il est plac� juste avant un " � enlever

        *varData = midData->mid(midData->indexOf('{')+1,-1);       //R�cup�re les donn�es contenues dans la balise content du fichier JSON.
        *varData = varData->left(varData->indexOf('}')+1);
        emit si_sendListVar(*varData);

        delete m_fileJSON;
        m_fileJSON = nullptr;

        delete allData;
        allData = nullptr;

        delete midData;
        midData = nullptr;
    }
    else
        qDebug() << "does not exist";
}

void MainWindow::sl_getSelectedVar(QStringList list){
    delete dialog;
    dialog = nullptr;
    formatFile(list);
}

void MainWindow::formatFile(QStringList listSelectedVar){                                                          //Fonction permettant d'enlever les \ en trop dans les fichiers JSON ainsi que les 2 " présent. Cette modification est n�cessaire pour que le scirpt python fonctionne correctement
    qDebug() << "selection de variable" << listSelectedVar;
    long percent = 0;
    for (int i = 0; i < m_listJSON.size(); i++){                                                                    //Boucle permettant de traiter tous les fichiers JSON selectionees
        m_fileJSON = new QFile(m_listJSON.at(i));
        if (m_fileJSON->exists()){                                                                                  //Ouvre les fichiers afin de manipuler leurs donnees
            QString *allData = new QString;                                                                         //Contient toute les donn�es JSON
            QString *midData = new QString;                                                                         //Contient les donn�es corrig�s () et ", et les donnees selectionnees par l'utilsateur
            QString *varData = new QString;                                                                         //Contient uniquement les variables contenu dans la balise "content" des fichiers JSON

            if (!m_fileJSON->isOpen()){                                                                             //Verifie que le fichier existe
                m_fileJSON->open(QIODevice::ReadWrite);
            }
            *allData = m_fileJSON->readAll();                                                                       //Permet des manipulations sur les données des fichiers JSON
            *allData = allData->remove('\\');                                                                       //Enleve les '\'

            *midData = allData->remove(0,1);                                                                        // Enl�ve le premier char car c'est un {. Le second { est celui qui nous int�resse car il est plac� juste avant un " � enlever
            *midData = midData->remove(midData->indexOf('{')-1,1);                                                  //Retire le premier "
            *midData = midData->remove(midData->indexOf('}')+1,1);                                                  //Retire le second "

            *varData = midData->mid(midData->indexOf('{')+1,-1);                                                    //R�cup�re les donn�es contenues dans la balise content du fichier JSON.
            *varData = varData->left(varData->indexOf('}'));                                                        //........

            *allData = removeUnwantedVariable(*varData, listSelectedVar) + midData->right(midData->indexOf('}')+1); //Fonction ne laissant que les variables selectionnees<

            *midData = midData->left(midData->indexOf('{')+1);                                                      //Manipulation pour ne recuperer que les donnees avant la balise content contenue dans les fichiers JSON
            midData->append(allData);

            midData->prepend('{');                                                                                  //Rajoute le { enlever en premier lieu


            addModifiedFile(*midData,m_listJSON.at(i));                                                             //Appel fct de modification des JSON + enregistrement dans dossier
            m_fileJSON->close();

            delete varData;
            varData = nullptr;

            delete m_fileJSON;
            m_fileJSON = nullptr;

            delete allData;
            allData = nullptr;

            delete midData;
            midData = nullptr;
        }
        if (((100*i)/m_listJSON.size()) != percent){                                                               //Calcule le pourcentage de fichier JSON modifie
            percent = (100*i)/m_listJSON.size();
            ui->progressBar->setValue(percent);
        }
    }
    ui->progressBar->setValue(100);
    executePythonScript();
    qDebug() << "python script end";
}

QString MainWindow::removeUnwantedVariable(QString allContentVariable /*toutes variables JSON*/, QStringList listSelected /*variables JSON s�lectionees*/){    // Fonction ne laissant que les variables s�lectionner par l'utilisateur
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
    m_fileJSONModified->write(dataModified.toLocal8Bit());              //Ecrit les donn�es JSON corrig�s
    m_fileJSONModified->close();
    delete m_fileJSONModified;
    m_fileJSONModified = nullptr;
}

void MainWindow::executePythonScript(){     //Execute le script python, pas de probl�me la-dessus
    m_processPythonScript = new QProcess();
    QString command = ("python.exe");
    QStringList argument;
//    argument.append("main.py");
    argument.append("C:\\PycharmProjects\\extractDataJSO:N\\main.py");       //0
    QString argPathFolderModi = m_folderModifiedJSON.path() + '/';
    argument.append(argPathFolderModi);                                     //1
    argument.append(m_folderExcel + '/');                                         //2
    argument.append(QString::number(QCoreApplication::applicationPid()));
    qDebug() << command + "  0" + argument.at(0) + "  1" + argument.at(1) + "   2" + argument.at(2) + "   3" + argument.at(3);


    m_processPythonScript->setProgram(command);
    m_processPythonScript->setArguments(argument);

    m_processPythonScript->start();
    int status = m_processPythonScript->exitStatus();
    qDebug() << "valeur sortie:" << status;
    //    while(m_processPythonScript->state() == QProcess::Running){
    //    }
    qDebug() << "NO RUNNING";
    this->~MainWindow();
}


MainWindow::~MainWindow()
{
    qDebug() << "in";
    delete dialog;
    delete settings;
    delete m_fileJSON;
    delete m_fileJSONModified;
    delete m_processPythonScript;
    delete m_listWidgetItem;
    delete settings;
    delete ui;
    exit(0);
}


void MainWindow::on_MainWindow_destroyed()
{
    QApplication::quit();
    this->~MainWindow();
}
