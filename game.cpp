#include "game.h"
#include "ui_game.h"

Game::Game(QString mode, QString username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    this->mode = mode;
    this->username = username;
    qDebug() << mode;
}

Game::~Game()
{
    delete ui;
}

void Game::on_btnSend_clicked()
{
    sendChatMessage();
}

void Game::newServerInfo(QString ipAdress, QString port)
{
        ui->lblHostInfo->setText("This server is hosted on "+ipAdress+":"+port+" .");
}


void Game::getMessage(QString message)
{
    ui->lwChat->addItem(message);
}


void Game::on_edtChat_returnPressed()
{
    sendChatMessage();
}

void Game::sendChatMessage()
{
    QString message = ui->edtChat->text();
    if(mode=="MP_HOST")
    {
        message.prepend(username+": ");
        ui->lwChat->addItem(message);
    }
    message.prepend("CHAT_");
    ui->edtChat->clear();
    emit sendMessage(message);
}
