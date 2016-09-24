#include "hangman.h"
#include "ui_hangman.h"

Hangman::Hangman(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Hangman)
{
    ui->setupUi(this);
    cServer = new ClientServer();
    connect(cServer, SIGNAL(receivedMessage(QString)), this, SLOT(getMessage(QString)));
}

Hangman::~Hangman()
{
    delete ui;
    delete cServer;
}

void Hangman::on_btnStartHost_clicked()
{
    ui->lblStatus->setText(cServer->startServer());
}

void Hangman::on_btnSend_clicked()
{
    cServer->sendMessage(ui->edtMessage->text());
}

void Hangman::getMessage(QString message)
{
    ui->lwChatWindow->addItem(message);
}

void Hangman::on_btnFindHost_clicked()
{
    QString ipAdress = ui->edtIpAdress->text();
    int port = ui->edtPort->text().toInt();
    ui->lblStatus->setText(cServer->connectClient(ipAdress, port));
}
