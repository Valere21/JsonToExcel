#include "mainwindow.h"

void MainWindow::formatFile(QStringList listSelectedVar){                                                          //Fonction permettant d'enlever les \ en trop dans les fichiers JSON ainsi que les 2 " présent. Cette modification est necessaire pour que le scirpt python fonctionne correctement

    //    qDebug() <<  listSelectedVar;

    long percent = 0;
    for (int i = 0; i < m_listJSON.size(); i++){                                                                    //Boucle permettant de traiter tous les fichiers JSON selectionees
        m_fileJSON = new QFile(m_listJSON.at(i));

        if (m_fileJSON->exists()){                           //Ouvre les fichiers afin de manipuler leurs donnee
            if (!m_fileJSON->isOpen()){                              //Verifie que le fichier existe
                m_fileJSON->open(QIODevice::ReadWrite);
            }
            QString regularData;
            QString selectData;
            QString insertStr;
            QStringList list = parseVar(m_fileJSON->readAll());

            regularData = list.at(1);
            selectData = list.at(0);
            insertStr = regularData;
            insertStr = insertStr.insert(regularData.indexOf('{')+1,selectData);

            m_listRuleSelect = ui_dialog->getListRule();

            if (m_listRuleSelect){
                if (!m_listRuleSelect->isEmpty()){
                    if (isFileCorrect(m_fileJSON, selectData.split(','))){
                        if (isFileAccepted(m_fileJSON, selectData.split(','))){
                            addModifiedFile(selectData, m_fileJSON->fileName());
                        }
                    }
                }
            }

            qDebug() <<"selected " << selectData;
            //            qDebug() << m_fileJSON->fileName() << "; INSERT " << insertStr;
            addModifiedFile(selectData,m_listJSON.at(i));                                                             //Appel fct de modification des JSON + enregistrement dans dossier

            m_fileJSON = nullptr;
            if (((100*i)/m_listJSON.size()) != percent){                                                               //Calcule le pourcentage de fichier JSON modifie
                percent = (100*i)/m_listJSON.size();
                ui->progressBar->setValue(percent);
            }
        }
    }
    ui->progressBar->setValue(100);
    executePythonScript();
    //    qDebug() << "python script end";
}

bool MainWindow::isFileCorrect(QFile *fileJson, QStringList varDataJson){
    bool flag = false;

    for (int i = 0; i < m_listRuleSelect->size(); i++){
        //        if (varDataJson.contains())
    }
    return flag;
}

bool MainWindow::isFileAccepted(QFile *file, QStringList varDataJson){
    bool flag = false;

    if (!m_listRuleSelect->isEmpty()){
        for (int i = 0; i < m_listRuleSelect->size(); i++){
            Rule *nextRule = m_listRuleSelect->at(i);
            if (nextRule->getRule() < Egal){

            }
            switch (nextRule->getRule()) {
            case Egal :{
                break;
            }
            case Inf :{
                break;
            }
            case Sup :{
                break;
            }
            case InfEgal :{
                break;
            }
            case SupEgal :{
                break;
            }
            default:
                break;
            }
        }
    }
    else {
        flag = true;
    }


    return flag;
}
