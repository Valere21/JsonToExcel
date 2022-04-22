#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSettings>
#include <QDebug>
class Settings
{
public:
    Settings();
    QStringList getSettings();
    void setSettings(QString pathJsonFolder, QString pathExcelFolder);
    void removeSettings();
//    ~Settings();
private:
    QSettings m_settings;

};

#endif // SETTINGS_H
