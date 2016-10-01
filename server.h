#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);
public slots:
    QString startServer();
private slots:
    void readClientData();
    void disconnectClient();
    void sendToAllClients(QString message);

protected:
    void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;
signals:
     void serverInfo(QString ipAdress, QString port);
private:
    QList<QTcpSocket *> connectedClients;
    QMap<QString, QTcpSocket *> clientMap;
    QTcpSocket *currentOpponent;
};

#endif
