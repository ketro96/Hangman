#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);
public slots:
    bool startServer();
    void gameAccepted(bool accepted);

private slots:
    void readClientData();
    void disconnectClient();
    void sendToClient(QTcpSocket *client, QString message);
    void sendToAllClients(QString message);

protected:
    void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;
signals:
    void serverInfo(QString ipAdress, QString port);
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
