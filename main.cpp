#include "hangme.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HangMe w;
    w.show();

    return a.exec();
}
