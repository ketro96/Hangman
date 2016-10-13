#include "gamehelp.h"
#include "ui_gamehelp.h"

GameHelp::GameHelp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameHelp)
{
    ui->setupUi(this);
}

GameHelp::~GameHelp()
{
    delete ui;
}

void GameHelp::closeEvent(QCloseEvent *)
{
    emit closed();
}
