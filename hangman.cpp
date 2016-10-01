#include "hangman.h"
#include "ui_hangman.h"


Hangman::Hangman(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Hangman)
{
    ui->setupUi(this);
    server = new Server();
    connect(server, SIGNAL(receivedMessage(QString)), this, SLOT(getMessage(QString)));
}

Hangman::~Hangman()
{
    delete ui;

}


void Hangman::on_btnStartHost_clicked()
{
    if(server->startServer())
    {
        game = new Game();
        game->show();
    }


}

void Hangman::on_btnFindHost_clicked()
{
    ConnectionSetup *connectionSetup = new ConnectionSetup();

    connect(connectionSetup, SIGNAL(connectClient(QString, int)), this, SLOT(connectClient(QString,int));
            connectionSetup->show();

}

void Hangman::on_btnSingleplayer_clicked()
{
    //start Singleplayer Game
}

void Hangman::connectClient(QString nickname, QString ipAdress, int port)
{
    if(client->connectClient(ipAdress, port))
    {

    }
    else
    {

    }
}
