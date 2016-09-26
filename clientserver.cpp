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
        connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newClient()));
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

bool ClientServer::connectClient(QString ipAdress, int port)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(clientReadyRead()),Qt::DirectConnection); //Ohne Directconnection? DC = Multithreaded?
    connect(socket, SIGNAL(disconnected()), this, SLOT(hostDisconnected()));
    socket->connectToHost(ipAdress, port);
    bool connected = false;
    if(socket->waitForConnected(3000))
    {
        connected = true;
    }

    return connected;
}

void ClientServer::sendMessage(QString message)
{
    // send
    socket->write(message.toUtf8());
    socket->waitForBytesWritten(1000);
    socket->waitForReadyRead(-1);
    qDebug() << "Reading: " << socket->bytesAvailable();
}

void ClientServer::newClient()
{
    if(tcpServer->hasPendingConnections())
    {
        QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
        connect(clientConnection, &QAbstractSocket::readyRead, this, &ClientServer::readClientData);
        connect(clientConnection, &QAbstractSocket::disconnected, clientConnection, &QObject::deleteLater);
        //clientConnection->peerAddress()
        ///in Map mit sockets speichern und später mit nicknames verbinden?


        clientConnection->write("Hello client\r\n");
        clientConnection->flush();

        clientConnection->waitForBytesWritten(3000);

        connectedClients.append(clientConnection);
    }
}


void ClientServer::readClientData()
{
    //Choose socket that just connected!!!!
    ///Work
    QByteArray newData = socket->readAll();
}

void ClientServer::clientReadyRead()
{
    QByteArray newData = socket->readAll();

    QString dataString(newData);

    emit receivedMessage(dataString);

}

void ClientServer::hostDisconnected()
{
    qDebug() << "Host disconnected";
}
