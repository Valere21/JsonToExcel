#include "mainwindow.h"


int add(int a, int b){
    return a+b;
}

int getNbrVar(QString pathToJson){                          //Renvoie le nombre de variable contenue dans ce fichier JSON "pathToJson"

    QFile *fileJSON = new QFile(pathToJson);
    QString *allData = new QString;                  //Contient toute les donnees JSON
    if (fileJSON ->exists()){                           //Ouvre les fichiers afin de manipuler leurs donnee
        if (!fileJSON->isOpen()){                              //Verifie que le fichier existe
            fileJSON->open(QIODevice::ReadWrite);
        }

        *allData = fileJSON ->readAll();                       //Permet des manipulations sur les données des fichiers JSON
        *allData = allData->remove('\\');                               //Enlèvre les '\'
        *allData = allData->remove(0,1);                        // Enleve le premier char car c'est un {. Le second { est celui qui nous interesse car il est place juste avant un " e enlever

        *allData = allData->mid(allData->indexOf('{')+1,-1);       //Recupere les donnees contenues dans la balise content du fichier JSON.
        *allData = allData->left(allData->indexOf('}')+1);
    }
    int size = allData->split(',').size();
    fileJSON->close();
    delete allData;
    delete fileJSON;
    allData = nullptr;
    fileJSON = nullptr;
    return size;
}

void MainWindow::getVar(){              //Fonction permettant d'isoler les variables selectionnes par l'utilisateur (oui c'est un copie coller de la fonction format file, oui c'est pas opti, oui c'est moche, c'est moche hein)

    ui_dialog = new Dialog(this);
    connect(this, SIGNAL(si_sendListVar(QString)), ui_dialog, SLOT(sl_getListVar(QString)));

    connect (ui_dialog, SIGNAL(si_quitApp()), this, SLOT(sl_quitApp()));
    connect (ui_dialog, SIGNAL(si_sendSelectedVar(QStringList)), this, SLOT(sl_getSelectedVar(QStringList)));
    connect (ui_dialog, SIGNAL(si_isAllSelected(bool)), this, SLOT(sl_isAllSelected(bool)));
    connect (ui_dialog, SIGNAL(si_isAndOr(bool)), this, SLOT(sl_isAndOr(bool)));


    if (m_listJSON.isEmpty()){
        qDebug() << "mlistJSON empty";
        this->~MainWindow();
    }

//    int indexFileMaxVar = 0;                                        //Permet d'isoler le fichier JSON avec le plus de variables
//    for (int i = 0;  i < m_listJSON.size(); i++){
//        if (getNbrVar(m_listJSON.at(indexFileMaxVar)) > getNbrVar(m_listJSON.at(i)))
//            indexFileMaxVar = i;
//    }

    int indexMax = 0;
    int indexSizeMaxVar = getNbrVar(m_listJSON.at(0));                                        //Permet d'isoler le fichier JSON avec le plus de variables
    for (int i = 0;  i < m_listJSON.size(); i++){
        int indexAtI = getNbrVar(m_listJSON.at(i));
        if (indexAtI > indexSizeMaxVar){
            indexSizeMaxVar = indexAtI;
            indexMax = i;
        }
    }


    m_fileJSON = new QFile(m_listJSON.at(indexMax));

    if (m_fileJSON->exists()){                           //Ouvre les fichiers afin de manipuler leurs donnee
        if (!m_fileJSON->isOpen()){                              //Verifie que le fichier existe
            m_fileJSON->open(QIODevice::ReadWrite);
        }


        QString *all = new QString(m_fileJSON->readAll());
        QString *var = new QString;

        *all = all->remove(0,1);
        *all = all->remove('\\');

        *var = all->mid(all->indexOf('{')+1,-1);
        *var = var->left(var->indexOf('}')-1);

        *all = all->left(all->indexOf(('{')));
        *all += all->rightRef(all->indexOf(('}')));

        emit si_sendListVar(*var);

        m_fileJSON->close();

        delete var;
        delete all;
        delete m_fileJSON;

        all = nullptr;
        var = nullptr;
        m_fileJSON = nullptr;
    }
    else if (!m_fileJSON->exists()){
        qDebug() << "does not exist";
    }
}

void MainWindow::sl_isAllSelected(bool flag){
    m_isAllSelected = flag;
}

void MainWindow::sl_isAndOr(bool ruleOrga){
    m_isAndOr = ruleOrga;
}

void MainWindow::sl_getSelectedVar(QStringList listSelected){
    m_listRuleSelect = ui_dialog->getListRule();

    delete ui_dialog;
    ui_dialog = nullptr;
    formatFile(listSelected);
}














