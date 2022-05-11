#include "mainwindow.h"

bool MainWindow::askSettings(){                                 //fonction permettant de recuperer les chemins des dossier JSON a modifier + dossier Excel, depuis le fichier de sauvegarde
    bool flag = true;
    QMessageBox msgBox;
    msgBox.setText("Utiliser les parametres par defaut ?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if (msgBox.exec() == QMessageBox::No){
        ui_settings->removeSettings();
        setPath();
        ui_settings->setSettings(m_folderJSON.path() + '/',m_folderExcel);
        flag = false;
//        qDebug() << "SETTINGS non utilisees";
    }
    else {
        flag = true;
//        qDebug() <<  "SETTINGS utilisees";
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
    if (!ui_settings->getSettings().isEmpty()){
        if (askSettings()){
            m_folderJSON.setPath(ui_settings->getSettings().value(1));
            m_folderExcel = ui_settings->getSettings().value(0);
        }
    }
    else {
        setPath();
        ui_settings->setSettings(m_folderJSON.path() + '/',m_folderExcel);
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
