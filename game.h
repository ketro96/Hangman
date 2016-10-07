#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QString mode, QString username, QWidget *parent = 0);
    ~Game();
public slots:
    void getMessage(QString message);
private slots:
    void on_btnSend_clicked();
    void newServerInfo(QString ipAdress, QString port);
    void on_edtChat_returnPressed();
    void sendChatMessage();

signals:
    void sendMessage(QString message);
private:
    QString mode;
    QString username;
    Ui::Game *ui;
};

#endif // GAME_H
