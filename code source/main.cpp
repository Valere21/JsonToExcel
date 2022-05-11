#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("SettingsQt");
    a.setApplicationName("JsonToExcel");
    MainWindow w;

    return a.exec();
}
