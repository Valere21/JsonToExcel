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
    bool flag = true;
    QMessageBox msgBox;
    msgBox.setText("Utiliser les parametres par defaut ?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if (msgBox.exec() == QMessageBox::No){
        settings->removeSettings();
        setPath();
        settings->setSettings(m_folderJSON.path() + '/',m_folderExcel);
        flag = false;
        qDebug() << "SETTINGS non utilisées";
    }
    else {
        flag = true;
        qDebug() <<  "SETTINGS utilisées";
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
        if (askSettings()){
            m_folderJSON.setPath(settings->getSettings().value(1));
            m_folderExcel = settings->getSettings().value(0);
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

int getNbrVar(QString pathToJson){                          //Renvoie le nombre de variable contenue dans ce fichier JSON "pathToJson"

    QFile *fileJSON = new QFile(pathToJson);
    QString *allData = new QString;                  //Contient toute les donnees JSON
    if (fileJSON ->exists()){                           //Ouvre les fichiers afin de manipuler leurs donnee
        if (!fileJSON ->isOpen()){                              //Verifie que le fichier existe
            fileJSON ->open(QIODevice::ReadWrite);
        }

        *allData = fileJSON ->readAll();                       //Permet des manipulations sur les données des fichiers JSON
        *allData = allData->remove('\\');                               //Enlèvre les '\'
        *allData = allData->remove(0,1);                        // Enleve le premier char car c'est un {. Le second { est celui qui nous interesse car il est place juste avant un " e enlever

        *allData = allData->mid(allData->indexOf('{')+1,-1);       //Recupere les donnees contenues dans la balise content du fichier JSON.
        *allData = allData->left(allData->indexOf('}')+1);
    }
    int size = allData->split(',').size();
    delete allData;
    delete fileJSON;
    allData = nullptr;
    fileJSON = nullptr;
    return size;
}

void MainWindow::getVar(){              //Fonction permettant d'isoler les variables selectionnes par l'utilisateur (oui c'est un copie coller de la fonction format file, oui c'est pas opti, oui c'est moche, c'est moche hein)
    dialog = new Dialog;
    connect (dialog, SIGNAL(si_quitApp()), this, SLOT(sl_quitApp()));
    connect(this, SIGNAL(si_sendListVar(QString)), dialog, SLOT(sl_getListVar(QString)));
    connect (dialog, SIGNAL(si_sendSelectedVar(QStringList)), this, SLOT(sl_getSelectedVar(QStringList)));

    if (m_listJSON.isEmpty()){
        qDebug() << "mlistJSON empty";
        this->~MainWindow();
    }
    int indexFileMaxVar = 0;                                        //Permet d'isoler le fichier JSON avec le plus de variables
    for (int i = 0;  i < m_listJSON.size(); i++){
        if (getNbrVar(m_listJSON.at(indexFileMaxVar)) > getNbrVar(m_listJSON.at(i)))
            indexFileMaxVar = i;
    }
    qDebug() <<  "fichier n°" << indexFileMaxVar;
    m_fileJSON = new QFile(m_listJSON.at(indexFileMaxVar));
    if (m_fileJSON->exists()){                           //Ouvre les fichiers afin de manipuler leurs donnee
        QString *allData = new QString;                  //Contient toute les donnees JSON
        QString *midData = new QString;                 //Contient les donnees corriges () et "
        QString *varData = new QString;                                //Contient uniquement les variables contenu dans la balise "content" des fichiers JSON
        if (!m_fileJSON->isOpen()){                              //Verifie que le fichier existe
            m_fileJSON->open(QIODevice::ReadWrite);
        }

        *allData = m_fileJSON->readAll();                       //Permet des manipulations sur les données des fichiers JSON
        *allData = allData->remove('\\');                               //Enlèvre les '\'
        *midData = allData->remove(0,1);                        // Enleve le premier char car c'est un {. Le second { est celui qui nous interesse car il est place juste avant un " e enlever

        *varData = midData->mid(midData->indexOf('{'),-1);       //Recupere les donnees contenues dans la balise content du fichier JSON.
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

QString getVarData(QStringList listSelectedVar, QStringList listAllVar){
    QString strVarDataSelect;
    for (int i = 0; i < listAllVar.size(); i++){
        for (int j = 0; j < listSelectedVar.size(); j++){
            if (listAllVar.at(i).contains(listSelectedVar.at(j))){
                strVarDataSelect.append(listAllVar.at(i));
            }
            else ;
        }
    }
    return strVarDataSelect;
}

void MainWindow::formatFile(QStringList listSelectedVar){                                                          //Fonction permettant d'enlever les \ en trop dans les fichiers JSON ainsi que les 2 " présent. Cette modification est necessaire pour que le scirpt python fonctionne correctement
    long percent = 0;
    for (int i = 0; i < m_listJSON.size(); i++){                                                                    //Boucle permettant de traiter tous les fichiers JSON selectionees
        m_fileJSON = new QFile(m_listJSON.at(i));
        if (m_fileJSON->exists()){                                                                                  //Ouvre les fichiers afin de manipuler leurs donnees
            QString *allData = new QString;                                                                         //Contient toute les donnees JSON
            QString *midData = new QString;                                                                         //Contient les donnees corriges () et ", et les donnees selectionnees par l'utilsateur
            QString *varData = new QString;                                                                         //Contient uniquement les variables contenu dans la balise "content" des fichiers JSON

            if (!m_fileJSON->isOpen()){                                                                             //Verifie que le fichier existe
                m_fileJSON->open(QIODevice::ReadWrite);
            }
            *allData = m_fileJSON->readAll();                                                                       //Permet des manipulations sur les données des fichiers JSON
            *allData = allData->remove('\\');                                                                       //Enleve les '\'

            *midData = allData->remove(0,1);                                                                        // Enleve le premier char car c'est un {. Le second { est celui qui nous interesse car il est place juste avant un " e enlever
            *midData = midData->remove(midData->indexOf('{')-1,1);                                                  //Retire le premier "
            *midData = midData->remove(midData->indexOf('}')+1,1);                                                  //Retire le second "

            *varData = midData->mid(midData->indexOf('{')+1,-1);                                                    //Recupere les donnees contenues dans la balise content du fichier JSON.
            *varData = varData->left(varData->indexOf('}'));                                                        //........
            //            qDebug() << "allData" << *varData;
            //                qDebug() << " NEW : " << getVarData(listSelectedVar,varData->split(','));
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
    //    qDebug() << "python script end";
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
    delete dialog;
    delete settings;
    delete m_fileJSON;
    delete m_fileJSONModified;
    delete m_listWidgetItem;
    delete ui;

    delete m_processPythonScript;
    qDebug() << "About to quit";
    QApplication::quit();
    exit(0);
}


