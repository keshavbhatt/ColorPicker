#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("ColorPicker");
    QApplication::setOrganizationName("org.keshavnrj.ubuntu");
    QApplication::setApplicationVersion(VERSIONSTR);

    MainWindow w;
    w.show();

    return a.exec();
}
