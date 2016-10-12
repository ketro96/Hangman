#include "endofgame.h"
#include "ui_endofgame.h"

EndOfGame::EndOfGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EndOfGame)
{
    ui->setupUi(this);
}

EndOfGame::~EndOfGame()
{
    delete ui;
}

void EndOfGame::showDialog(bool won, int score)
{
    ui->lblPoints->setText(QString::number(score));
    ui->lblResult->setText(won ? "You won!" : "You lost!");
    this->show();
}

void EndOfGame::on_buttonBox_accepted()
{
    emit buttonBoxAnswer(true);
}

void EndOfGame::on_buttonBox_rejected()
{
    emit buttonBoxAnswer(false);
}
