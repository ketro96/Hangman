#include "server.h"

Server::Server(QObject *parent) :
     QTcpServer(parent)
{
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *connection = new QTcpSocket(this);
    connection->setSocketDescriptor(socketDescriptor);
    connect(connection, SIGNAL(readyRead()), this, SLOT(readClientData()));
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
    QString dataString = QString(data);
    qDebug() << dataString;
    if(dataString.left(5)=="GAME_")
    {
        if(dataString.mid(5)=="REQUEST")
        {
            QString username = clientMap.value(client);
            emit receivedRequestMessage(username);
        }
        else
        {
            emit receivedGameMessage(dataString.mid(5));
        }
        /*
         * START
         * FAIL
         * SUCCESS
         * WIN
         * LOSE
         */
    }
    else if(dataString.left(5)=="CHAR_")
    {
        //LENGTH from server? CHAR from client
        QString content = dataString.mid(5);
        emit receivedCharMessage(content);
    }
    else if(dataString.left(5)=="CHAT_")
    {
        //CHAT MESSAGE
        QString username = clientMap.value(client);
        QString content = dataString.mid(5);
        emit receivedChatMessage(username+": "+content);
        sendToAllClients("CHAT_"+username+": "+content);
    }
    else if(dataString.left(5)=="USER_")
    {
        QString username = dataString.mid(5);
        qDebug() << "User: " << username;
        if(!clientMap.contains(client))
        {
            clientMap.insert(client, username);
        }
    }
    else
    {
        qDebug() << "Received invalid Message.";
    }
}

void Server::sendToAllClients(QString message)
{   
    QByteArray messageData = message.toUtf8();
    qDebug() << "send _"+message+"_ to :";
    foreach(QTcpSocket *client, connectedClients)
    {
        qDebug() << clientMap.value(client);
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
