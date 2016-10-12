#include "server.h"

Server::Server(QObject *parent) :
    QTcpServer(parent)
{
    currentOpponent = NULL;
    busy = false;
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
    if (!this->listen(QHostAddress::Any, 44444))
    {
        emit serverFailInfo("Could not start Server", this->errorString());
        this->close();
        return false;
    }
    else
    {
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
            currentOpponent = client;
            if(busy)
            {
                sendToClient(currentOpponent, "GAME_DENY");
            }
            else
            {
                emit receivedRequestMessage(username);
            }
        }
        else if(dataString.mid(5)=="END")
        {
            busy = false;
            emit receivedGameMessage(dataString.mid(5));
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

void Server::gameAccepted(bool accepted)
{
    if(accepted)
    {
        sendToClient(currentOpponent, "GAME_ACCEPT");
        busy = true;
    }
    else
    {
        sendToClient(currentOpponent, "GAME_DENY");
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

void Server::sendToClient(QTcpSocket *client, QString message)
{
    QByteArray messageData = message.toUtf8();
    client->write(messageData);
    client->flush();
    client->waitForBytesWritten(3000);
}

void Server::disconnectClient()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    if (!client)
        return;
    if(currentOpponent)
    {
        if(client == currentOpponent)
        {
            busy = false;
        }
    }
    connectedClients.removeAll(client);
    //clientMap.remove()
    client->deleteLater();
}
