#ifndef HANGMAN_H
#define HANGMAN_H

#include <QMainWindow>
#include <QInputDialog>
#include <QDir>
#include <client.h>
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
public slots:
    void connectClient(QString ipAdress, int port);

private slots:
    void on_btnStartHost_clicked();

    void on_btnFindHost_clicked();

    void on_btnSingleplayer_clicked();

    bool getUsername();
    void on_btnGoBack_clicked();

    void on_btnMultiplayer_clicked();

private:
    Ui::Hangman *ui;
    Server *server;
    Game *game;
    Client *client;
    QString username = "";
};

#endif // HANGMAN_H
