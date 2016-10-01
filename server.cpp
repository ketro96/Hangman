#include "server.h"

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *connection = new QTcpSocket(this);
    connection->setSocketDescriptor(socketDescriptor);
    connect(connection, &QTcpSocket::readyRead, this, readClientData);
    connect(connection, &QTcpSocket::disconnected, clientConnection, &Server::disconnectClient);

    connectedClients.append(connection);
}

bool Server::startServer()
{
    if (!this->listen())
    {
        emit serverInfo((this->errorString(), ""));
        this->close();
        return false;
    }
    else
    {
        connect(this, SIGNAL(newConnection()), this, SLOT(newClient()));
    }
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address())
        {
            ipAddress = ipAddressesList.at(i).toString();
            emit serverInfo(ipAddress, QString::number(this->serverPort()));
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
    {
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
        emit serverInfo(ipAddress, QString::number(this->serverPort()));
    }
    return true;
}

void Server::readClientData()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    QByteArray data = client->readAll();
    QString incMessage = QString(data);

    //only insert if nick does not already exist....
    if(!clientMap.contains(client))
    {
        clientMap.insert(incMessage, client);
    }
}

void Server::sendToAllClients(QString message)
{
    QByteArray messageData = message.toUtf8();

    foreach(QTcpSocket *client, connectedClients)
    {
        client->write("Hello client\r\n");
        client->flush();
        client->waitForBytesWritten(3000);
    }
}

void Server::clientDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    if (!client)
        return;

    connectedClients.removeAll(client);
    //clientMap.remove()
    client->deleteLater();
}
