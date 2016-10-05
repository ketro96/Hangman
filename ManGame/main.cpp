#include "mainwindow.h"
#include <QApplication>
#include <mywidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    MyWidget myWidget;
    myWidget.show();

    return a.exec();
}
