#include "dictionary.h"
#include "ui_dictionary.h"

Dictionary::Dictionary(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dictionary)
{
    ui->setupUi(this);
}

Dictionary::~Dictionary()
{
    delete ui;
}
