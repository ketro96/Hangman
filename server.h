#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QTime>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);
public slots:
    bool startServer();
    void gameAccepted(bool accepted);
    void closeServer();
    void endGame();
    void sendToOpponent(QString message);

private slots:
    void readClientData();
    void disconnectClient();
    void sendToClient(QTcpSocket *client, QString message);
    void sendToAllClients(QString message);
    void delay(int millisecondsToWait);

protected:
    void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;

signals:
    void serverInfo(QString ipAdress, QString port);
    void serverFailInfo(QString title, QString errorMessage);
    void receivedChatMessage(QString message);
    void receivedGameMessage(QString message);
    void receivedRequestMessage(QString message);
    void receivedCharMessage(QString message);

private:
    QList<QTcpSocket *> connectedClients;
    QMap<QTcpSocket *, QString> clientMap;
    QTcpSocket *currentOpponent;
    bool busy;
};

#endif
