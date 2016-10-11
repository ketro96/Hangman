#include "hangman.h"
#include "ui_hangman.h"


Hangman::Hangman(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Hangman)
{
    ui->setupUi(this);
    ui->btnGoBack->hide();
    ui->btnGoBack->setIcon(QIcon(":/images/images/Back.png"));
    ui->btnSP_Easy->hide();
    ui->btnSP_Medium->hide();
    ui->btnSP_Hard->hide();
    ui->btnStartHost->hide();
    ui->btnFindHost->hide();
}

Hangman::~Hangman()
{
    delete ui;
    if(server) delete server;
    if(client) delete client;
    if(chat) delete chat;
    if(game) delete game;
}


void Hangman::on_btnStartHost_clicked()
{
    server = new Server();
    chat = new Chat("MP_HOST", username);
    game = new Game("MP_HOST", username);
    //connect game
    connect(server, SIGNAL(receivedChatMessage(QString)), chat, SLOT(getMessage(QString)));
    connect(chat, SIGNAL(sendMessage(QString)), server, SLOT(sendToAllClients(QString)));
    connect(server, SIGNAL(serverInfo(QString,QString)), chat, SLOT(newServerInfo(QString, QString)));
    if(server->startServer())
    {
        chat->show();
        game->show();
    }
    else
    {
        //chat->disconnect()
        delete server;
        delete chat;
        delete game;
        QMessageBox::information(0,"Error","Could not start server.");
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
        chat = new Chat("MP_CLIENT", username);
        game = new Game("MP_CLIENT", username);
        //connect game
        connect(client, SIGNAL(receivedChatMessage(QString)), chat, SLOT(getMessage(QString)));
        connect(chat, SIGNAL(sendMessage(QString)), client, SLOT(sendMessage(QString)));
        chat->show();
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



void Hangman::on_btnSP_Easy_clicked()
{
    game = new Game("SP_EASY", username);
    //connects

    game->show();
}

void Hangman::on_btnSP_Medium_clicked()
{
    game = new Game("SP_EASY", username);
    //connects

    game->show();
}

void Hangman::on_btnSP_Hard_clicked()
{
    game = new Game("SP_EASY", username);
    //connects

    game->show();
    //disable hangman gui
}
