#include "hangman.h"
#include "ui_hangman.h"


Hangman::Hangman(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Hangman)
{
    ui->setupUi(this);
}

Hangman::~Hangman()
{
    delete ui;

}


void Hangman::on_btnStartHost_clicked()
{
    server = new Server();
    game = new Game();
    connect(server, SIGNAL(receivedMessage(QString)), game, SLOT(getMessage(QString)));
    connect(game, SIGNAL(sendMessage(QString)), server, SLOT(sendToAllClients(QString)));
    connect(server, SIGNAL(serverInfo(QString,QString)), game, SLOT(newServerInfo(QString, QString)));
    if(server->startServer())
    {
        game->show();
    }
    else
    {
        //game->disconnect()
        delete(game);
        //Could not start
    }

}

void Hangman::on_btnFindHost_clicked()
{
    client = new ClientServer();
    ConnectionSetup *connectionSetup = new ConnectionSetup();
    //connect(client, SIGNAL(receivedMessage(QString)), this, SLOT(getMessage(QString)));
    connect(connectionSetup, SIGNAL(connectClient(QString, QString, int)), this, SLOT(connectClient(QString, QString,int)));
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
        client->sendMessage(nickname);
        ui->lblStatus->setText("Connected");
        game = new Game();
        connect(client, SIGNAL(receivedMessage(QString)), game, SLOT(getMessage(QString)));
        connect(game, SIGNAL(sendMessage(QString)), client, SLOT(sendMessage(QString)));
        game->show();
    }
    else
    {
    ui->lblStatus->setText("Could not connect...");
    }
}
