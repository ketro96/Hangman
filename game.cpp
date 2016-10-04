#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
}

Game::~Game()
{
    delete ui;
}

void Game::on_btnSend_clicked()
{
    emit sendMessage(ui->edtChat->text());
}

void Game::newServerInfo(QString ipAdress, QString port)
{
    ui->teIpAdress->setText(ipAdress);
    ui->tePort->setText(port);
}


void Game::getMessage(QString message)
{
    ui->lwChat->addItem(message);
}

