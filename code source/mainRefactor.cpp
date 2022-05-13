#include "mainwindow.h"

#define NAME 0
#define VAR  1


QStringList getDataOrName(QString dataVar){                         //Separe le nom de la valeur d'une variable content, renvoie les 2 informations dans une QStringList
    QStringList list;
    list.append(dataVar.left(dataVar.indexOf(':')));                //position 0 => name
    QString strVar = dataVar.remove(0,dataVar.indexOf(':')+1);
    strVar.remove(' ');
    list.append(strVar);              //position 1 => value
    return list;
}

QString formatData(QString regularData, QStringList selectedData, QStringList dataWithVar){  // Format les donnees a ecrire dans le fichier JSON
    QString dataFormat;
    for (int i = 0; i < dataWithVar.size(); i++){
        for (int j = 0; j < selectedData.size(); j++){
            if (getDataOrName(dataWithVar.at(i)).at(NAME) == selectedData.at(j))
                dataFormat.append(dataWithVar.at(i) + ',');
        }
    }
    dataFormat.chop(1);
    dataFormat.append('}');
    regularData.remove('\\');
    dataFormat.remove('\\');

    regularData.remove(0,1);
    regularData.remove(regularData.indexOf('{')-1,1);
    regularData.remove(regularData.indexOf('{')+1,1);

    QString result = regularData.insert(regularData.indexOf('{')+1,dataFormat);
    result.prepend("{\"");
    return result;
}


bool checkList(QStringList selectedData, QStringList dataWithVar){  // Incremente un compteur si toutes les valeurs de "selectedData" existe dans la liste "dataWithVar". Renvoie true si ce nombre est identique. Permet de verifier qu'un fichier contient bien toute les variables
    int index = 0;
    for (int i = 0; i < dataWithVar.size(); i++){
        for (int j = 0; j < selectedData.size(); j++){
            //            qDebug() << "selectedData.at(j)" << selectedData.at(j) << "dataWithVar.at(i)" << dataWithVar.at(i);
            if (getDataOrName(dataWithVar.at(i)).at(NAME) == selectedData.at(j))
                index++;
        }
    }
    return (index == selectedData.size());
}

bool isRuleRespected(Rule *rule, QString dataVar){
    bool flag = false;
    switch (rule->getRule()) {
    case NaN :{
        QRegExp re("\\d*");
        if ((re.exactMatch(getDataOrName(dataVar).at(VAR))))
            flag = true;
        break;
    }
    case Zero :{
        QRegExp re("\\d*");
        if (re.exactMatch(getDataOrName(dataVar).at(VAR)) && getDataOrName(dataVar).at(VAR).toFloat(NULL) == 0){
            flag = true;
        }
        break;
    }
    case One :{
        QRegExp re("\\d*");
        if (re.exactMatch(getDataOrName(dataVar).at(VAR)) && getDataOrName(dataVar).at(VAR).toFloat(NULL) == 1)
            flag = true;
        break;
    }
    case Egal :{
        if (rule->getOption().optionSel == Name){
            if (getDataOrName(rule->getVar()).at(VAR).toFloat(NULL) == getDataOrName(rule->getOption().name).at(VAR).toFloat(NULL)){
                flag = true;
            }
        }
        if (rule->getOption().optionSel == Number){
            if (getDataOrName(dataVar).at(VAR).toFloat() == rule->getOption().val)
                flag = true;
        }
        break;
    }
    case Inf :{
        if (rule->getOption().optionSel == Name){
            if (getDataOrName(rule->getVar()).at(VAR).toFloat(NULL) < getDataOrName(rule->getOption().name).at(VAR).toFloat(NULL))
                flag = true;
        }
        if (rule->getOption().optionSel == Number){
            if (getDataOrName(dataVar).at(VAR).toFloat() < rule->getOption().val)
                flag = true;
        }
        break;
    }
    case Sup :{
        if (rule->getOption().optionSel == Name){
            if (getDataOrName(rule->getVar()).at(VAR).toFloat(NULL) > getDataOrName(rule->getOption().name).at(VAR).toFloat(NULL))
                flag = true;
        }
        if (rule->getOption().optionSel == Number){
            if (getDataOrName(dataVar).at(VAR).toFloat() > rule->getOption().val)
                flag = true;
        }
        break;
    }
    case InfEgal :{
        if (rule->getOption().optionSel == Name){
            if (getDataOrName(rule->getVar()).at(VAR).toFloat(NULL) <= getDataOrName(rule->getOption().name).at(VAR).toFloat(NULL))
                flag = true;
        }
        if (rule->getOption().optionSel == Number){
            if (getDataOrName(dataVar).at(VAR).toFloat() <= rule->getOption().val)
                flag = true;
        }
        break;    }
    case SupEgal :{
        if (rule->getOption().optionSel == Name){
            if (getDataOrName(rule->getVar()).at(VAR).toFloat(NULL) >= getDataOrName(rule->getOption().name).at(VAR).toFloat(NULL))
                flag = true;
        }
        if (rule->getOption().optionSel == Number){
            if (getDataOrName(dataVar).at(VAR).toFloat() >= rule->getOption().val)
                flag = true;
        }
        break;
    }
    default:
        break;
    }
    return flag;
}

bool MainWindow::isFileAccepted(QStringList dataWithVar){
    //    qDebug() << Q_FUNC_INFO;
    if (!m_listRuleSelect || m_listRuleSelect->isEmpty()){
        qDebug() << "rule empty";
        return true;
    }
    bool flag = false;

    int indexRuleRespected = 0;
    for (int i = 0; i < m_listRuleSelect->size(); i++){
        for (int j = 0; j < dataWithVar.size(); j++){
            if (m_listRuleSelect->at(i)->getVar() == getDataOrName(dataWithVar.at(j)).at(NAME)){
                if (isRuleRespected(m_listRuleSelect->at(i), dataWithVar.at(j))){
                    indexRuleRespected++;
                }
            }
        }
    }
    if (m_isAndOr == AND){
        if (indexRuleRespected == m_listRuleSelect->size()){
            //            qDebug() << "rule AND true";
            flag = true;
        }
        else if (indexRuleRespected != m_listRuleSelect->size()){
            flag = false;
            //            qDebug() << "rule AND false";
        }
    }
    else if (m_isAndOr == OR){
        if (indexRuleRespected >= 1){
            //            qDebug() << "rule OR true";
            flag = true;
        }
        else if (indexRuleRespected == 0){
            flag = false;
            //            qDebug() << "rule OR false";
        }
    }

    return flag;
}

void algoPacked(QString allData){                                       //Nous assumons ici que allData ne contient que les donnees contenues dans "content"

    QString tmpAll = allData;
    QPair<QString,QList<float>> storeData;

    //    for (int i = 0; i < )
}

void MainWindow::formatFile(QStringList listSelectedVar){                                                          //Fonction permettant d'enlever les \ en trop dans les fichiers JSON ainsi que les 2 " présent. Cette modification est necessaire pour que le scirpt python fonctionne correctement
    this->setWindowTitle("Processing JSON file");
    long percent = 0;
    for (int i = 0; i < m_listJSON.size(); i++){                                                                    //Boucle permettant de traiter tous les fichiers JSON selectionees
        m_fileJSON = new QFile(m_listJSON.at(i));

        if (m_fileJSON->exists()){                           //Ouvre les fichiers afin de manipuler leurs donnee
            if (!m_fileJSON->isOpen()){                              //Verifie que le fichier existe
                m_fileJSON->open(QIODevice::ReadWrite);
            }
            QString regularData;
            QString dataWithVar;
            QStringList list = parseVar(m_fileJSON->readAll());
            regularData = list.at(1);
            dataWithVar = list.at(0);

            // 1) On verifie que les regles sont respectees sur l'ensemble des variables
            // Si une variable n'existe pas dans le fichier alors qu'elle existe dans les regles, on zappe ce fichier
            //            qDebug() << dataWithVar;
            if (!m_isAllSelected){
                if (checkList(listSelectedVar, dataWithVar.split(','))){
                    //                qDebug() << "meme nombre !" << m_fileJSON->fileName();
                    if (isFileAccepted(dataWithVar.split(','))){
                        QString dataFormat = formatData(regularData,listSelectedVar,dataWithVar.split(','));
                        //                        qDebug() << "here " << dataFormat,m_listJSON.at(i);
                        addModifiedFile(dataFormat,m_listJSON.at(i));                                                             //Appel fct de modification des JSON + enregistrement dans dossier
                    }
                }
                else {
                    //                    qDebug() << "pas le meme nombre, fichier skip " << m_fileJSON->fileName();
                }
            }
            else if (m_isAllSelected){
                QString dataFormat = formatData(regularData,listSelectedVar,dataWithVar.split(','));
                addModifiedFile(dataFormat,m_listJSON.at(i));                                                             //Appel fct de modification des JSON + enregistrement dans dossier
            }
            m_fileJSON->close();
            m_fileJSON = nullptr;
            delete m_fileJSON;
            if (((100*i)/m_listJSON.size()) != percent){                                                               //Calcule le pourcentage de fichier JSON modifie
                qDebug() << "percent have changed " << percent;
                percent = (100*i)/m_listJSON.size();
                ui->progressBar->setValue(percent);
            }
        }
    }
    ui->progressBar->setValue(100);
    executePythonScript();
    //    qDebug() << "python script end";
}









