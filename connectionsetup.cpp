#include "connectionsetup.h"
#include "ui_connectionsetup.h"

ConnectionSetup::ConnectionSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionSetup)
{
    ui->setupUi(this);
}

ConnectionSetup::~ConnectionSetup()
{
    delete ui;
}


void ConnectionSetup::on_buttonBox_rejected()
{
    //go back
}


void ConnectionSetup::on_buttonBox_accepted()
{
    QString nickname = ui->edtNickname->text();
    QString ipAdress = ui->edtIpAdress->text();
    int port = ui->edtPort->text().toInt();

    emit connectClient(nickname, ipAdress, port);
}

