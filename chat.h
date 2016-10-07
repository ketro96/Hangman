#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
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
    Ui::Chat *ui;
};

#endif // CHAT_H
