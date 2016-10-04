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
    connect(connection, &QTcpSocket::disconnected, this, &Server::disconnectClient);
    qDebug() << "Incoming connection";
    connectedClients.append(connection);
}

bool Server::startServer()
{
    if (!this->listen())
    {
        emit serverInfo(this->errorString(), "");
        this->close();
        qDebug() << "Could not start Server";
        return false;
    }
    else
    {
        //connect(this, SIGNAL(newConnection()), this, SLOT(newClient()));
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
            qDebug() << "Server started1";
            emit serverInfo(ipAddress, QString::number(this->serverPort()));
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
    {
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
        qDebug() << "Server started2";
        emit serverInfo(ipAddress, QString::number(this->serverPort()));
    }
    return true;
}

void Server::readClientData()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    QByteArray data = client->readAll();
    QString incMessage = QString(data);
    qDebug() << incMessage;
    emit receivedMessage(incMessage);
    //only insert if nick does not already exist....
    if(!clientMap.contains(incMessage) && !connectedClients.contains(client))
    {
        clientMap.insert(incMessage, client);
    }
}

void Server::sendToAllClients(QString message)
{
    QByteArray messageData = message.toUtf8();

    foreach(QTcpSocket *client, connectedClients)
    {
        qDebug() << "send to 1client";
        client->write(messageData);
        client->flush();
        client->waitForBytesWritten(3000);
    }
}

void Server::disconnectClient()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    if (!client)
        return;

    connectedClients.removeAll(client);
    //clientMap.remove()
    client->deleteLater();
}
