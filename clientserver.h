#ifndef CLIENTSERVER_H
#define CLIENTSERVER_H

#include <QObject>
#include <QLabel>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkSession>
#include <QMessageBox>

class ClientServer : public QObject
{
    Q_OBJECT
public:
    explicit ClientServer(QObject *parent = 0);
    QString startServer();

private slots:
    //void sessionOpened();
    //void sendFortune();
    void sendMessage(QString message);
    void newClient();
    void readClientData();

private:
    QLabel *statusLabel;
    QTcpServer *tcpServer;
    QTcpSocket *socket;
    QStringList fortunes;
    QNetworkSession *networkSession;
    QList<QTcpSocket*> connectedClients;
};

#endif // CLIENTSERVER_H
