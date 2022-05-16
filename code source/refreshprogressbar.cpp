#include "refreshprogressbar.h"
#include <QMessageBox>

RefreshProgressBar::RefreshProgressBar(QStringList listJSON) : m_listJSON(listJSON)
{

}

void RefreshProgressBar::run(){
    getIndexMax(m_listJSON);
}

int RefreshProgressBar::getNbr(QString pathToJson){
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

void RefreshProgressBar::getIndexMax(QStringList listJSON){
    float percent = 0;
    long indexMax = 0;
    long indexSizeMaxVar = getNbr(listJSON.at(0));                                        //Permet d'isoler le fichier JSON avec le plus de variables
    //    QThread *thread = QThread::create(getNbrVar(listJSON.at(0)));

    for (long i = 0;  i < listJSON.size(); i++){
        long indexAtI = getNbr(listJSON.at(i));
        if (indexAtI > indexSizeMaxVar){
            indexSizeMaxVar = indexAtI;
            indexMax = i;
        }
        if (((100*i)/listJSON.size()) != percent){                                                               //Calcule le pourcentage de fichier JSON modifie
//            if (percent == 10 || percent == 20 || percent == 30){
//                QMessageBox msgBox;
//                msgBox.setText("10 20 ou 30%");
//                msgBox.exec();
//            }

            qDebug() << "new percent" << percent;
            percent = (100*i)/listJSON.size();
            emit si_getThreadUpdatePercent(percent);
        }
    }
    emit si_getThreadUpdatePercent(100);
    emit si_getThreadMaxIndex(indexMax);
}
