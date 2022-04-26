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

void MainWindow::formatFile(QStringList listSelectedVar){                                                          //Fonction permettant d'enlever les \ en trop dans les fichiers JSON ainsi que les 2 " présent. Cette modification est necessaire pour que le scirpt python fonctionne correctement
    long percent = 0;
    for (int i = 0; i < m_listJSON.size(); i++){                                                                    //Boucle permettant de traiter tous les fichiers JSON selectionees
        m_fileJSON = new QFile(m_listJSON.at(i));
        if (m_fileJSON->exists()){                                                                                  //Ouvre les fichiers afin de manipuler leurs donnees
            if (!m_fileJSON->isOpen()){                                                                             //Verifie que le fichier existe
                m_fileJSON->open(QIODevice::ReadWrite);
            }

            QString *allData = new QString;                                                                         //Contient toute les donnees JSON
            QString *midData = new QString;                                                                         //Contient les donnees corriges () et ", et les donnees selectionnees par l'utilsateur
            QString *varData = new QString;                                                                         //Contient uniquement les variables contenu dans la balise "content" des fichiers JSON

            QString *all = new QString(m_fileJSON->readAll());
            QString *var = new QString;

            *all = all->remove(0,1);
            *all = all->remove('\\');
            *var = all->mid(all->indexOf(('{')),-1);
            *var = all->left(all->indexOf(('}')));
            *all = all->left(all->indexOf(('{')));
            *all += all->rightRef(all->indexOf(('}')));

//            qDebug() << "VAR " << *var;
//            qDebug() << "ALL " << *all;


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
    delete ui_dialog;
    delete ui_settings;
    delete m_fileJSON;
    delete m_fileJSONModified;
    delete m_listWidgetItem;
    delete ui;

    delete m_processPythonScript;
    qDebug() << "About to quit";
    QApplication::quit();
    exit(0);
}


