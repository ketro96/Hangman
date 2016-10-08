#include "hangman.h"
#include "ui_hangman.h"


Hangman::Hangman(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Hangman)
{
    ui->setupUi(this);
    ui->btnGoBack->hide();
    ui->btnSP_Easy->hide();
    ui->btnSP_Medium->hide();
    ui->btnSP_Hard->hide();
    ui->btnStartHost->hide();
    ui->btnFindHost->hide();
}

Hangman::~Hangman()
{
    delete ui;
}


void Hangman::on_btnStartHost_clicked()
{
    server = new Server();
    game = new Game("MP_HOST", username);
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

void Hangman::on_btnFindHost_clicked()
{
        client = new Client();
        ConnectionSetup *connectionSetup = new ConnectionSetup();
        //connect(client, SIGNAL(receivedMessage(QString)), this, SLOT(getMessage(QString)));
        connect(connectionSetup, SIGNAL(connectClient(QString, int)), this, SLOT(connectClient(QString,int)));
        connectionSetup->show();
}

void Hangman::on_btnSingleplayer_clicked()
{
    if(getUsername())
    {
        ui->btnSingleplayer->hide();
        ui->btnMultiplayer->hide();
        ui->btnGoBack->show();
        ui->btnSP_Easy->show();
        ui->btnSP_Medium->show();
        ui->btnSP_Hard->show();
    }
    //start Singleplayer Game
}

void Hangman::on_btnMultiplayer_clicked()
{
    if(getUsername())
    {
        ui->btnSingleplayer->hide();
        ui->btnMultiplayer->hide();
        ui->btnGoBack->show();
        ui->btnFindHost->show();
        ui->btnStartHost->show();
    }
}

void Hangman::connectClient(QString ipAdress, int port)
{
    if(client->connectClient(ipAdress, port))
    {
        client->sendMessage("USER_"+username);
        ui->lblStatus->setText("Connected");
        game = new Game("MP_CLIENT", username);
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
    username = QInputDialog::getText(this, tr("Who are you?"),
                                     tr("User name:"), QLineEdit::Normal,
                                     QDir::home().dirName(), &ok);
    if(ok && username.isEmpty())
    {
        ok = true;
    }
    return ok;
}

void Hangman::on_btnGoBack_clicked()
{
    ui->btnGoBack->hide();
    ui->btnSP_Easy->hide();
    ui->btnSP_Medium->hide();
    ui->btnSP_Hard->hide();
    ui->btnStartHost->hide();
    ui->btnFindHost->hide();
    ui->btnSingleplayer->show();
    ui->btnMultiplayer->show();
}


void Hangman::on_actionDictionary_triggered()
{
    wordLibrary = new WordLibrary();
    wordLibrary->show();
}
