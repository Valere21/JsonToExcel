#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("My Company");
    a.setOrganizationDomain("mycompany.com");
    a.setApplicationName("My Application");
    MainWindow w;

    return a.exec();
}
