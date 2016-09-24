#include "chatroom.h"
#include "ui_chatroom.h"

ChatRoom::ChatRoom(QWidget *parent, QString info) :
    QMainWindow(parent),
    ui(new Ui::ChatRoom)
{
    ui->setupUi(this);
    ui->lwChatWindow->addItem(info);
}

ChatRoom::~ChatRoom()
{
    delete ui;
}


void ChatRoom::getMessage(QString message)
{
     ui->lwChatWindow->addItem(message);
}
