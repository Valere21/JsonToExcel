#include "mainwindow.h"

#define NAME 0
#define VAR  1


QStringList getDataOrName(QString dataVar){                         //Sépare le nom de la valeur d'une variable content, renvoie les 2 informations dans une QStringList
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
    qDebug() << dataFormat;

    QString result = regularData.insert(regularData.indexOf('{')+1,dataFormat);
    result.prepend("{\"");
    qDebug() << "result " << result;
    return result;
}


bool checkList(QStringList selectedData, QStringList dataWithVar){  // Incrémente un compteur si toutes les valeurs de "selectedData" existe dans la liste "dataWithVar". Renvoie true si ce nombre est identique. Permet de vérifier qu'un fichier contient bien toute les variables
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
    //    qDebug() << Q_FUNC_INFO;
    bool flag = false;
    switch (rule->getRule()) {
    case NaN :{
        QRegExp re("\\d*");
        if (!(re.exactMatch(getDataOrName(dataVar).at(VAR))))
            flag = true;
        break;
    }
    case Zero :{
        QRegExp re("\\d*");
        if (re.exactMatch(getDataOrName(dataVar).at(VAR)) && getDataOrName(dataVar).at(VAR).toInt() == 0){
            flag = true;
        }
        break;
    }
    case One :{
        QRegExp re("\\d*");
        if (re.exactMatch(getDataOrName(dataVar).at(VAR)) && getDataOrName(dataVar).at(VAR).toInt() == 1)
            flag = true;
        break;
    }
    case Egal :{
        if (rule->getOption().optionSel == Name){
            if (getDataOrName(rule->getVar()).at(VAR).toInt() == getDataOrName(rule->getOption().name).at(VAR).toInt()){
                qDebug() << "val 1 " << getDataOrName(rule->getVar()).at(VAR).toInt() << " val2 " << getDataOrName(rule->getOption().name).at(VAR).toInt();
                flag = true;
            }
        }
        if (rule->getOption().optionSel == Number){
            if (getDataOrName(rule->getVar()).at(VAR).toInt() == rule->getOption().val)
                flag = true;
        }
        break;
    }
    case Inf :{
        if (rule->getOption().optionSel == Name){
            if (getDataOrName(rule->getVar()).at(VAR).toInt() < getDataOrName(rule->getOption().name).at(VAR).toInt())
                flag = true;
        }
        if (rule->getOption().optionSel == Number){
            if (getDataOrName(rule->getVar()).at(VAR).toInt() < rule->getOption().val)
                flag = true;
        }
        break;
    }
    case Sup :{
        if (rule->getOption().optionSel == Name){
            if (getDataOrName(rule->getVar()).at(VAR).toInt() > getDataOrName(rule->getOption().name).at(VAR).toInt())
                flag = true;
        }
        if (rule->getOption().optionSel == Number){
            if (getDataOrName(rule->getVar()).at(VAR).toInt() > rule->getOption().val)
                flag = true;
        }
        break;
    }
    case InfEgal :{
        if (rule->getOption().optionSel == Name){
            if (getDataOrName(rule->getVar()).at(VAR).toInt() <= getDataOrName(rule->getOption().name).at(VAR).toInt())
                flag = true;
        }
        if (rule->getOption().optionSel == Number){
            if (getDataOrName(rule->getVar()).at(VAR).toInt() <= rule->getOption().val)
                flag = true;
        }
        break;    }
    case SupEgal :{
        if (rule->getOption().optionSel == Name){
            if (getDataOrName(rule->getVar()).at(VAR).toInt() >= getDataOrName(rule->getOption().name).at(VAR).toInt())
                flag = true;
        }
        if (rule->getOption().optionSel == Number){
            if (getDataOrName(rule->getVar()).at(VAR).toInt() >= rule->getOption().val)
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
                //                qDebug() << "HERE " << m_listRuleSelect->at(i)->getVar() << getDataOrName(dataWithVar.at(j)).at(VAR);
                if (isRuleRespected(m_listRuleSelect->at(i), dataWithVar.at(j))){
                    indexRuleRespected++;
                    qDebug() << "rule respected at i: " << i;
                }
                else {
                    qDebug() << "rule not respected at i: " << i;
                    //                    qDebug() << "VAR ? " << getDataOrName(dataWithVar.at(j)).at(VAR);
                    //                    qDebug() << m_listRuleSelect->at(i)->getOption().val;
                }
            }
        }
        //        if (!flag)
        //            return false;
    }
    if (indexRuleRespected == m_listRuleSelect->size()){
        qDebug() << "rule true";
        flag = true;
    }
    else{
        flag = false;
        qDebug() << "rule false";
    }
    return flag;
}

void MainWindow::formatFile(QStringList listSelectedVar){                                                          //Fonction permettant d'enlever les \ en trop dans les fichiers JSON ainsi que les 2 " prÃ©sent. Cette modification est necessaire pour que le scirpt python fonctionne correctement
    qDebug() << Q_FUNC_INFO;
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

            // 1) On vérifie que les règles sont respectées sur l'ensemble des variables
            // Si une variable n'existe pas dans le fichier alors qu'elle existe dans les règles, on zappe ce fichier
            //            qDebug() << dataWithVar;
            if (!m_isAllSelected){
                if (checkList(listSelectedVar, dataWithVar.split(','))){
                    //                qDebug() << "meme nombre !" << m_fileJSON->fileName();
                    if (isFileAccepted(dataWithVar.split(','))){
                        QString dataFormat = formatData(regularData,listSelectedVar,dataWithVar.split(','));
                        qDebug() << "here " << dataFormat,m_listJSON.at(i);
                        addModifiedFile(dataFormat,m_listJSON.at(i));                                                             //Appel fct de modification des JSON + enregistrement dans dossier
                    }
                }
                else {
                    qDebug() << "pas le meme nombre, fichier skip " << m_fileJSON->fileName();
                }
            }
            else if (m_isAllSelected){
                QString dataFormat = formatData(regularData,listSelectedVar,dataWithVar.split(','));
                addModifiedFile(dataFormat,m_listJSON.at(i));                                                             //Appel fct de modification des JSON + enregistrement dans dossier
            }
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









