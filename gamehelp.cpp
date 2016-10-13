// =========================================================
// AUTHOR       : Alexander Höhn & Adrian Werner
// CREATE DATE  : 2016-10-12
// PURPOSE      : Shows a help dialog that explains the game
// =========================================================

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
