// ===============================================
// AUTHOR       : Alexander Höhn & Adrian Werner
// CREATE DATE  : 2016-10-12
// PURPOSE      : Start HangMe
// ===============================================

#include "hangme.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HangMe w;
    w.show();

    return a.exec();
}
