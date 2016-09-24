#ifndef CHATROOM_H
#define CHATROOM_H

#include <QMainWindow>

namespace Ui {
class ChatRoom;
}

class ChatRoom : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatRoom(QWidget *parent = 0, QString info ="");
    ~ChatRoom();


public slots:
    void getMessage(QString message);

private:
    Ui::ChatRoom *ui;
};

#endif // CHATROOM_H
