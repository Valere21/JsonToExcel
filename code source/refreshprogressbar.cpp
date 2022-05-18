#include "refreshprogressbar.h"
#include <QMessageBox>


//void RefreshProgressBar::run(){
//    getIndex();
//}


void RefreshProgressBar::getIndex(){

    QString *allData = new QString;                  //Contient toute les donnees JSON
    if (m_fileJson.exists()){                           //Ouvre les fichiers afin de manipuler leurs donnee
        if (!m_fileJson.isOpen()){                              //Verifie que le fichier existe
            m_fileJson.open(QIODevice::ReadWrite);
        }

        *allData = m_fileJson.readAll();                       //Permet des manipulations sur les données des fichiers JSON
        *allData = allData->remove('\\');                               //Enlèvre les '\'
        *allData = allData->remove(0,1);                        // Enleve le premier char car c'est un {. Le second { est celui qui nous interesse car il est place juste avant un " e enlever

        *allData = allData->mid(allData->indexOf('{')+1,-1);       //Recupere les donnees contenues dans la balise content du fichier JSON.
        *allData = allData->left(allData->indexOf('}')+1);
    }
    int size = allData->split(',').size();
    m_fileJson.close();

    delete allData;
    allData = nullptr;
    emit si_getThreadIndex(size, m_numeroThread);
    //    qDebug() << Q_FUNC_INFO;
    delete this;
}
