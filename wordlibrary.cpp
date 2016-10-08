#include "wordlibrary.h"
#include "ui_wordlibrary.h"

WordLibrary::WordLibrary(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WordLibrary)
{
    ui->setupUi(this);
}

WordLibrary::~WordLibrary()
{
    delete ui;
}
