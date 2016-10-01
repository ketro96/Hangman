#ifndef HANGMAN_H
#define HANGMAN_H

#include <QMainWindow>
#include <clientserver.h>
#include <server.h>
#include <game.h>
#include <connectionsetup.h>


namespace Ui {
class Hangman;
}

class Hangman : public QMainWindow
{
    Q_OBJECT

public:
    explicit Hangman(QWidget *parent = 0);
    ~Hangman();
    void connectClient(QString nickname, QString ipAdress, int port);

private slots:
    void on_btnStartHost_clicked();

    void on_btnFindHost_clicked();

    void on_btnSingleplayer_clicked();

private:
    Ui::Hangman *ui;
    Server *server;
    Game *game;
};

#endif // HANGMAN_H
