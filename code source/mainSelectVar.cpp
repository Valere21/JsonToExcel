#include "mainwindow.h"

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



void MainWindow::sl_getThreadIndex(int size, int indexMax){
    extern uint qGlobalPostedEventsCount(); // from qapplication.cpp

    //    qDebug() << Q_FUNC_INFO;
    if (size > m_currentSizeMaxThread){
        m_currentSizeMaxThread = size;
        m_currentIndexThread = indexMax;
    }

    //    qDebug() << Q_FUNC_INFO << "size " << size << " index" << indexMax;
    //    qDebug() << "indexMax " << indexMax << " m_listJSON.size() " << m_listJSON.size();
    //    qDebug() << ((100*indexMax)/m_listJSON.size());
    if (((100*indexMax)/m_listJSON.size()) != ui->progressBar->value()){                                                               //Calcule le pourcentage de fichier JSON modifie
        qDebug() << "perc " << ((100*indexMax)/m_listJSON.size()) << " and perc " << ui->progressBar->value();
        qDebug() << "pending event count " << qGlobalPostedEventsCount();
        //        while (qGlobalPostedEventsCount() > 30);
        ui->progressBar->setValue((100*indexMax)/m_listJSON.size());

    }

    //    delete object;
    //    object = nullptr;
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

    ///////////////


    this->setWindowTitle("Loading JSON file");
    QList<QThread*> listThread;
    int index = 0;
    here:
    for (int i = index;  i < m_listJSON.size(); i++){
        while (listThread.size() < 3200){
            qDebug() << "listThread size " << listThread.size();
            auto newProcess = new RefreshProgressBar(m_listJSON.at(i),i);
            auto newThread = new QThread;

            connect (newProcess, SIGNAL(si_getThreadIndex(int, int)), this, SLOT(sl_getThreadIndex(int, int)));
            connect (newThread, SIGNAL(finished()), this, SLOT(deleteLater()));

            newProcess->moveToThread(newThread);
            newThread->start();

            listThread.append(newThread);
        }
        if (index < m_listJSON.size()){
            for (int i = 0; i < listThread.size(); i++){
                delete listThread.value(i);
            }
        listThread.clear();
        qDebug() << "brefore goto";
        goto here;
        }
    }
        //while (listThread.value(listThread.at(listThread.size()-1)->isRunning()));

    //                    listTmpThread.append(newThread);
    //        newThread->run();
    // newThread->start();
    //QThread::currentThread()->eventDispatcher()->hasPendingEvents();
    //            }
    //            while (listTmpThread.at(listTmpThread.size()-1)->isRunning());
    //            qDebug() << "last thread " << listTmpThread.at(listTmpThread.size()-1)->isRunning();
    //            listTmpThread.clear();
    //        }
    //        else {
    //            RefreshProgressBar *newThread = new RefreshProgressBar(m_listJSON.at(i),i);
    //            connect (newThread, SIGNAL(si_getThreadIndex(int, int)), this, SLOT(sl_getThreadIndex(int, int)));
    //            connect (newThread, SIGNAL(finished()), this, SLOT(deleteLater()));
    //            //        m_thread->start();
    //            newThread->run();
    //            //m_thread->wait();
    //            //QThread::currentThread()->eventDispatcher()->hasPendingEvents();
    //        }
    //    }
    ///////////////////////

    ui->progressBar->setValue(0);


    //    m_fileJSON = new QFile(m_listJSON.at(indexMax));
    m_fileJSON = new QFile(m_listJSON.at(m_currentIndexThread));


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














