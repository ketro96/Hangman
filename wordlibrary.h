#ifndef WORDLIBRARY_H
#define WORDLIBRARY_H

#include <QWidget>

namespace Ui {
class WordLibrary;
}

class WordLibrary : public QWidget
{
    Q_OBJECT

public:
    explicit WordLibrary(QWidget *parent = 0);
    ~WordLibrary();

private:
    Ui::WordLibrary *ui;
};

#endif // WORDLIBRARY_H
