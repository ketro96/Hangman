#include "hangman.h"
#include "ui_hangman.h"

Hangman::Hangman(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Hangman)
{
    ui->setupUi(this);
    cServer = new ClientServer();

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
