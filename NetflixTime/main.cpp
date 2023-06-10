#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Main menu");
    QIcon icon(":/resource/icon.png");
    a.setWindowIcon(icon);
    w.show();
    return a.exec();
}
