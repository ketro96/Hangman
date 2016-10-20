// =========================================================
// AUTHOR       : Alexander Höhn & Adrian Werner
// CREATE DATE  : 2016-10-12
// PURPOSE      : Show highscore dialog and ask for restart
// =========================================================

#include "endofgame.h"
#include "ui_endofgame.h"

EndOfGame::EndOfGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EndOfGame)
{
    ui->setupUi(this);
        this->setWindowIcon(QIcon(":/images/images/Hangman.png"));
}

EndOfGame::~EndOfGame()
{
    delete ui;
}

//show endOfGame dialog with win or lose message
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
