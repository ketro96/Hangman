#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class Chat;
}

class Chat : public QWidget
{
    Q_OBJECT

public:
    explicit Chat(QString mode, QString username, QWidget *parent = 0);
    ~Chat();
public slots:
    void getMessage(QString message);
    void getRequestMessage(QString username);
    void gameStarted(bool started);
    void disconnect();

signals:
    void sendMessage(QString message);
    void gameRequest();
    void gameAnswer(bool accepted);

private slots:
    void on_btnSend_clicked();
    void newServerInfo(QString ipAdress, QString port);
    void on_edtChat_returnPressed();
    void sendChatMessage();
    void on_btnRequestGame_clicked();

private:
    QString mode;
    QString username;
    Ui::Chat *ui;
};

#endif // CHAT_H
