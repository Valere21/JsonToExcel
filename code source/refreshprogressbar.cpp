#include "refreshprogressbar.h"

RefreshProgressBar::RefreshProgressBar()
{

}

void RefreshProgressBar::run(){

}

int RefreshProgressBar::getNrb(QString pathToJson){

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

void RefreshProgressBar::getIndexMax(){
//    float percent = 0;
//    int indexMax = 0;
//    int indexSizeMaxVar = getNbrVar(m_listJSON.at(0));                                        //Permet d'isoler le fichier JSON avec le plus de variables
//    //    QThread *thread = QThread::create(getNbrVar(m_listJSON.at(0)));


//    this->setWindowTitle(QString::number(percent) + " Loading JSON file");
//    for (int i = 0;  i < m_listJSON.size(); i++){
//        int indexAtI = getNbrVar(m_listJSON.at(i));
//        if (indexAtI > indexSizeMaxVar){
//            indexSizeMaxVar = indexAtI;
//            indexMax = i;
//        }
//        if (((100*i)/m_listJSON.size()) != percent){                                                               //Calcule le pourcentage de fichier JSON modifie
//            percent = (100*i)/m_listJSON.size();
//            ui->progressBar->setValue(percent);
//        }
//    }
}
