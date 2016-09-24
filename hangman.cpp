#include "hangman.h"
#include "ui_hangman.h"


Hangman::Hangman(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Hangman)
{
    ui->setupUi(this);
    cServer = new ClientServer();
    connect(cServer, SIGNAL(receivedMessage(QString)), this, SLOT(getMessage(QString)));

    chatRoom = new ChatRoom();
}

Hangman::~Hangman()
{
    delete ui;
    delete cServer;
    delete chatRoom;
}


void Hangman::on_btnStartHost_clicked()
{

    chatRoom = new ChatRoom(0, cServer->startServer());
    chatRoom ->show();
}

/*
void Hangman::on_btnSend_clicked()
{
    cServer->sendMessage(ui->edtMessage->text());
}

void Hangman::getMessage(QString message)
{
    ui->lwChatWindow->addItem(message);
}

*/
void Hangman::on_btnFindHost_clicked()
{
    connectionSetup = new ConnectionSetup();
    connectionSetup->show();

}

void Hangman::on_btnSingleplayer_clicked()
{
    //start Singleplayer Game
}
