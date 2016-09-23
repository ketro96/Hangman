#ifndef CLIENTSERVER_H
#define CLIENTSERVER_H

#include <QObject>
#include <QLabel>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkSession>
#include <QMessageBox>
#include <QDebug>

class ClientServer : public QObject
{
    Q_OBJECT
public:
    explicit ClientServer(QObject *parent = 0);
    QString startServer();
    QString connectClient(QString ipAdress, int port);
    void sendMessage(QString message);

private slots:
    void newClient();
    void readClientData();
    void clientReadyRead();
    void hostDisconnected();

signals:
    void receivedMessage(QString dataString);

private:
    QLabel *statusLabel;
    QTcpServer *tcpServer;
    QTcpSocket *socket;
    QStringList fortunes;
    QNetworkSession *networkSession;
    QList<QTcpSocket*> connectedClients;
};

#endif // CLIENTSERVER_H
