// =================================================
// AUTHOR       : Alexander Höhn & Adrian Werner
// CREATE DATE  : 2016-10-12
// PURPOSE      : Get server IP and port
// =================================================

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

//Rejected setup
void ConnectionSetup::on_buttonBox_rejected()
{
    emit closed();
}

//Get IP and port from ui and emit connect signal
void ConnectionSetup::on_buttonBox_accepted()
{
    QString ipAdress = ui->edtIpAdress->text();
    int port = ui->edtPort->text().toInt();

    emit connectClient(ipAdress, port);
}

void ConnectionSetup::closeEvent(QCloseEvent *)
{
    emit closed();
}

