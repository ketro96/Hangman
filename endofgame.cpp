#include "endofgame.h"
#include "ui_endofgame.h"

EndOfGame::EndOfGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EndOfGame)
{
    ui->setupUi(this);
}

EndOfGame::~EndOfGame()
{
    delete ui;
}

void EndOfGame::on_buttonBox_accepted()
{

}

void EndOfGame::on_buttonBox_rejected()
{

}
