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
    if(getUsername())
    {
        server = new Server();
        game = new Game();
        connect(server, SIGNAL(receivedChatMessage(QString)), game, SLOT(getMessage(QString)));
        connect(game, SIGNAL(sendMessage(QString)), server, SLOT(sendToAllClients(QString)));
        connect(server, SIGNAL(serverInfo(QString,QString)), game, SLOT(newServerInfo(QString, QString)));
        if(server->startServer())
        {
            game->show();
        }
        else
        {
            //game->disconnect()
            delete server;
            delete game;
            //Could not start
        }
    }
}

void Hangman::on_btnFindHost_clicked()
{
    if(getUsername())
    {
        client = new Client();
        ConnectionSetup *connectionSetup = new ConnectionSetup();
        //connect(client, SIGNAL(receivedMessage(QString)), this, SLOT(getMessage(QString)));
        connect(connectionSetup, SIGNAL(connectClient(QString, int)), this, SLOT(connectClient(QString,int)));
        connectionSetup->show();
    }
}

void Hangman::on_btnSingleplayer_clicked()
{
    if(getUsername())
    {
    }
    //start Singleplayer Game
}

void Hangman::connectClient(QString ipAdress, int port)
{
    if(client->connectClient(ipAdress, port))
    {
        client->sendMessage("USER_"+username);
        ui->lblStatus->setText("Connected");
        game = new Game();
        connect(client, SIGNAL(receivedChatMessage(QString)), game, SLOT(getMessage(QString)));
        connect(game, SIGNAL(sendMessage(QString)), client, SLOT(sendMessage(QString)));
        game->show();
    }
    else
    {
        ui->lblStatus->setText("Could not connect...");
    }
}

bool Hangman::getUsername()
{
    bool ok = false;
    username = QInputDialog::getText(this, tr("Type your user name"),
                                     tr("User name:"), QLineEdit::Normal,
                                     QDir::home().dirName(), &ok);
    if(ok && username.isEmpty())
    {
        ok = true;
    }
    return ok;
}
