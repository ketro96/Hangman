#ifndef GAME_H
#define GAME_H

#include <QWidget>

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    ~Game();
public slots:
    void getMessage(QString message);
private slots:
    void on_btnSend_clicked();
    void newServerInfo(QString ipAdress, QString port);
signals:
    void sendMessage(QString message);
private:
    Ui::Game *ui;
};

#endif // GAME_H
