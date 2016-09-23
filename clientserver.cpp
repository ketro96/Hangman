#include "clientserver.h"

ClientServer::ClientServer(QObject *parent) : QObject(parent)
{

}

QString ClientServer::startServer()
{
    QString info = "";
    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen())
    {
        info = "Unable to start the server: " + tcpServer->errorString();
        tcpServer->close();
        return info;
    }
    else
    {
        connect(tcpServer, &QTcpServer::newConnection, this, &ClientServer::newClient());
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
            info = "The server is running on: " + ipAddress + " Port: " + QString::number(tcpServer->serverPort());
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
    {
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
        info = "The server is running on: " + ipAddress + " Port: " + QString::number(tcpServer->serverPort());
    }
    return info;
}


void ClientServer::sendMessage(QString message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);

    out << message;

    clientConnection->write(block);
    clientConnection->disconnectFromHost();
}

void ClientServer::newClient()
{
    if(tcpServer->hasPendingConnections())
    {
        QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
        connect(clientConnection, &QAbstractSocket::readyRead, this, &ClientServer::readClientData);
        connect(clientConnection, &QAbstractSocket::disconnected, clientConnection, &QObject::deleteLater);
        //clientConnection->peerAddress()
        connectedClients.append(clientConnection);
    }
}


void ClientServer::readClientData()
{
    //Choose socket that just connected!!!!
    ///Work
    QByteArray newData = socket->readAll();
}
