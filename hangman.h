#ifndef HANGMAN_H
#define HANGMAN_H

#include <QMainWindow>
#include <clientserver.h>
#include <connectionsetup.h>
#include <chatroom.h>

namespace Ui {
class Hangman;
}

class Hangman : public QMainWindow
{
    Q_OBJECT

public:
    explicit Hangman(QWidget *parent = 0);
    ~Hangman();

private slots:
    void on_btnStartHost_clicked();

   // void on_btnSend_clicked();

    void on_btnFindHost_clicked();
    //void showConnectionSetup();

    void on_btnSingleplayer_clicked();

private:
    Ui::Hangman *ui;
    ClientServer *cServer;
    ConnectionSetup *connectionSetup;
    ChatRoom *chatRoom;
};

#endif // HANGMAN_H
