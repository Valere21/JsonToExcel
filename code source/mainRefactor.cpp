#include "mainwindow.h"

void MainWindow::formatFile(QStringList listSelectedVar){                                                          //Fonction permettant d'enlever les \ en trop dans les fichiers JSON ainsi que les 2 " présent. Cette modification est necessaire pour que le scirpt python fonctionne correctement

    qDebug() <<  listSelectedVar;

    long percent = 0;
    for (int i = 0; i < m_listJSON.size(); i++){                                                                    //Boucle permettant de traiter tous les fichiers JSON selectionees
        m_fileJSON = new QFile(m_listJSON.at(i));

        if (m_fileJSON->exists()){                           //Ouvre les fichiers afin de manipuler leurs donnee
            if (!m_fileJSON->isOpen()){                              //Verifie que le fichier existe
                m_fileJSON->open(QIODevice::ReadWrite);
            }
            QString regularData;
            QString selectData;
            regularData = parseVar(m_fileJSON->readAll()).at(0);
            selectData = parseVar(m_fileJSON->readAll()).at(1);

            //            QString *all = new QString(m_fileJSON->readAll());
            //            QString *var = new QString;

            //            *all = all->remove(0,1);
            //            *all = all->remove('\\');

            //            *var = all->mid(all->indexOf('{')+1,-1);
            //            *var = var->left(var->indexOf('}')-1);

            //            *all = all->left(all->indexOf(('{')));
            //            *all += all->rightRef(all->indexOf(('}')));

            //            emit si_sendListVar(*var);

            //            delete var;
            //            delete all;
            //            delete m_fileJSON;

            //            all = nullptr;
            //            var = nullptr;
            addModifiedFile(selectData,m_listJSON.at(i));                                                             //Appel fct de modification des JSON + enregistrement dans dossier

            m_fileJSON = nullptr;
            if (((100*i)/m_listJSON.size()) != percent){                                                               //Calcule le pourcentage de fichier JSON modifie
                percent = (100*i)/m_listJSON.size();
                ui->progressBar->setValue(percent);
            }
        }
        ui->progressBar->setValue(100);
        executePythonScript();
        //    qDebug() << "python script end";
    }
}
