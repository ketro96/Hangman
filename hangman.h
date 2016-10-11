#ifndef HANGMAN_H
#define HANGMAN_H

#include <QMainWindow>
#include <QInputDialog>
#include <QDir>
#include <client.h>
#include <server.h>
#include <chat.h>
#include <connectionsetup.h>
#include <dictionary.h>
#include <highscore.h>
#include <gamecontroller.h>
#include <about.h>


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

    void on_actionDictionary_triggered();

    void on_btnSP_Easy_clicked();

    void on_btnSP_Medium_clicked();

    void on_btnSP_Hard_clicked();


    void on_actionHighscore_triggered();

    void enable();

    void deleteController();

    void deleteDict();

    void deleteHighscore();

    void on_actionAbout_triggered();

    void deleteAbout();

protected:
    void  closeEvent(QCloseEvent*);

private:
    Ui::Hangman *ui;
    Server *server;
    Client *client;
    Chat *chat;
    GameController *gameController;
    QString username = "";
    Dictionary *dictionary;
    Highscore *highscore;
    About *about;

};

#endif // HANGMAN_H
