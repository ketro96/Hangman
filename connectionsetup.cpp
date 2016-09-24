#include "connectionsetup.h"
#include "ui_connectionsetup.h"

ConnectionSetup::ConnectionSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionSetup)
{
    ui->setupUi(this);
    cServer = new ClientServer();
    connect(cServer, SIGNAL(receivedMessage(QString)), this, SLOT(ChatRoom::getMessage(QString)));
}

ConnectionSetup::~ConnectionSetup()
{
    delete ui;
    delete cServer;
    delete chatRoom;
}


void ConnectionSetup::on_buttonBox_rejected(){

//go back
}


void ConnectionSetup::on_buttonBox_accepted(){

     QString ipAdress = ui->edtIpAdress->text();
     int port = ui->edtPort->text().toInt();

     if(cServer->connectClient(ipAdress, port)){
        chatRoom = new ChatRoom(0, "Connected!");
        chatRoom->show();
     }
     else{
        ui->lblStatus->setText("Could not Connect!");
     }


}

