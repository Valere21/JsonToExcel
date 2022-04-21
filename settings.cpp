#include "settings.h"

Settings::Settings()
{
    //    QSettings m_settings("C://scriptExcelJsonSettings//configVariable.ini", QSettings::IniFormat);
    QSettings m_settings("QApplication::applicationDirPath() + configVariable.ini", QSettings::IniFormat);
}

QStringList Settings::getSettings(){
    for (int i = 0; i < m_settings.allKeys().size(); i++)
        qDebug() << m_settings.allKeys().at(i);
    //    m_settings.remove("pathJSON");
    //    m_settings.remove("pathExcel");
    //    m_settings.clear();
    //    m_settings.setValue("C:/JSONbrut/FolderExcel/", "pathEXCEL");
    //    m_settings.setValue("C:/JSONbrut/Safe/" , "pathJSON");
    return m_settings.allKeys();
}

void Settings::setSettings(QString pathJsonFolder, QString pathExcelFolder){
    m_settings.setValue(pathJsonFolder, "pathJSON");
    m_settings.setValue(pathExcelFolder, "pathEXCEL");
    m_settings.sync();
    qDebug() << "m_settings.status()" << m_settings.status();
}

Settings::~Settings(){
    delete this;
}
