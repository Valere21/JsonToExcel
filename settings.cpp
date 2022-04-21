#include "settings.h"

Settings::Settings()
{
    //    QSettings m_settings("C://scriptExcelJsonSettings//configVariable.ini", QSettings::IniFormat);
    QSettings m_settings("QApplication::applicationDirPath() + configVariable.ini", QSettings::IniFormat);
}

QStringList Settings::getSettings(){
    QStringList pathValue;
    if (!m_settings.allKeys().isEmpty()){
        qDebug() << "pas de settings détecté";
        pathValue.append(m_settings.value(m_settings.allKeys().at(0)).toString());
        pathValue.append(m_settings.value(m_settings.allKeys().at(1)).toString());
    }
    //    qDebug() << "group" << m_settings.fileName();
    //    for (int i = 0; i < m_settings.allKeys().size(); i++)
    //        qDebug() << "SETTINGS " << i  << ' ' << m_settings.value(m_settings.allKeys().at(i));
    //    return m_settings.allKeys();
    return pathValue;
}

void Settings::setSettings(QString pathJsonFolder, QString pathExcelFolder){
    m_settings.setValue("pathJSON", pathJsonFolder);
    m_settings.setValue("pathEXCEL", pathExcelFolder);
    m_settings.sync();
    qDebug() << "m_settings.status()" << m_settings.status();
}

Settings::~Settings(){
    //    delete this;
}
