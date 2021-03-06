#ifndef ENDOFGAME_H
#define ENDOFGAME_H

#include <QDialog>

namespace Ui {
class EndOfGame;
}

class EndOfGame : public QDialog
{
    Q_OBJECT

public:
    explicit EndOfGame(QWidget *parent = 0);
    ~EndOfGame();
    void showDialog(bool won, int score);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();



signals:
    void buttonBoxAnswer(bool restartGame);

private:
    Ui::EndOfGame *ui;
};

#endif // ENDOFGAME_H
