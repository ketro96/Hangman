#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QLabel>
#include <QTcpSocket>
#include <QNetworkSession>
#include <QMessageBox>
#include <QDebug>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    QString startServer();

public slots:
    bool connectClient(QString ipAdress, int port);
    void sendMessage(QString message);
    void sendRequest();
    void endGame();

private slots:
    void clientReadyRead();
    void disconnected();

signals:
    void receivedChatMessage(QString dataString);
    void gameAnswer(bool accepted);
    void receivedGameMessage(QString dataString);
    void receivedCharMessage(QString dataString);
    void disconnect();
    void closed();

private:
    QTcpSocket *socket;
};

#endif // CLIENT_H
