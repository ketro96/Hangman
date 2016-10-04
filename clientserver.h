#ifndef CLIENTSERVER_H
#define CLIENTSERVER_H

#include <QObject>
#include <QLabel>
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

public slots:
    bool connectClient(QString ipAdress, int port);
    void sendMessage(QString message);

private slots:
    void clientReadyRead();
    void hostDisconnected();

signals:
    void receivedMessage(QString dataString);

private:
    QLabel *statusLabel;
    QTcpSocket *socket;
    QNetworkSession *networkSession;
    QList<QTcpSocket*> connectedClients;
};

#endif // CLIENTSERVER_H
