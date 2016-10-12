#include "chat.h"
#include "ui_chat.h"

Chat::Chat(QString mode, QString username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
    this->mode = mode;
    ui->btnRequestGame->hide();
    if(mode == "MP_CLIENT")
    {
        ui->lblHostInfo->hide();
        ui->btnRequestGame->show();
    }
    this->username = username;
}

Chat::~Chat()
{
    delete ui;
}

void Chat::on_btnSend_clicked()
{
    sendChatMessage();
}

void Chat::newServerInfo(QString ipAdress, QString port)
{
        ui->lblHostInfo->setText("This server is hosted on "+ipAdress+":"+port);
}


void Chat::getMessage(QString message)
{
    ui->lwChat->addItem(message);
    ui->lwChat->scrollToBottom();
}


void Chat::on_edtChat_returnPressed()
{
    sendChatMessage();
}

void Chat::sendChatMessage()
{
    QString message = ui->edtChat->text();
    if(mode=="MP_HOST")
    {
        message.prepend(username+": ");
        ui->lwChat->addItem(message);
        ui->lwChat->scrollToBottom();
    }
    message.prepend("CHAT_");
    ui->edtChat->clear();
    emit sendMessage(message);
}

void Chat::on_btnRequestGame_clicked()
{
    emit gameRequest();
}
