#include "server.h"

Server::Server(QObject *parent) :
    QTcpServer(parent)
{
    currentOpponent = NULL;
    busy = false;
}

//connect new client and save in list
void Server::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *connection = new QTcpSocket(this);
    connection->setSocketDescriptor(socketDescriptor);
    connect(connection, SIGNAL(readyRead()), this, SLOT(readClientData()));
    connect(connection, &QTcpSocket::disconnected, this, &Server::disconnectClient);
    connectedClients.append(connection);
}

//Start server and listen to any available port
bool Server::startServer()
{

    if (!this->listen())
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

void Server::closeServer()
{
    this->close();
}

//Read data received from client
void Server::readClientData()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    QByteArray data = client->readAll();
    QString dataString = QString(data);
    QStringList splitList;

    //Clear tcp stream complications
    if(dataString.contains("#GAME_") || dataString.contains("#CHAT_") || dataString.contains("#USER_"))
    {
        splitList =  dataString.split("#");
        foreach (QString message, splitList)
        {
            if(message.left(5)=="CHAT_")
            {
                //CHAT MESSAGE
                QString username = clientMap.value(client);
                QString content = message.mid(5);
                emit receivedChatMessage(username+": "+content);
                sendToAllClients("#CHAT_"+username+": "+content);
            }
            else if(message.left(5)=="USER_")
            {
                QString username = message.mid(5);
                if(!clientMap.contains(client))
                {
                    clientMap.insert(client, username);
                }
            }
            else
            {
                if(message.mid(5)=="REQUEST")
                {
                    QString username = clientMap.value(client);
                    currentOpponent = client;
                    if(busy)
                    {
                        sendToClient(currentOpponent, "#GAME_DENY");
                    }
                    else
                    {
                        emit receivedRequestMessage(username);
                    }
                }
                else if(message.mid(5)=="END")
                {
                    busy = false;
                    currentOpponent = NULL;
                    emit receivedGameMessage(message.mid(5));
                }
                else
                {
                    emit receivedGameMessage(message.mid(5));
                }
            }
        }
    }
    else
    {
        //qDebug() << "Received invalid Message.";
        //Received invalid Message.
    }
}

//send accepted response to client
void Server::gameAccepted(bool accepted)
{
    if(accepted)
    {
        sendToClient(currentOpponent, "#GAME_ACCEPT");
        busy = true;
    }
    else
    {
        sendToClient(currentOpponent, "#GAME_DENY");
        busy = false;
    }
}

//send a message to all clients
void Server::sendToAllClients(QString message)
{   
    QByteArray messageData = message.toUtf8();
    foreach(QTcpSocket *client, connectedClients)
    {
        client->write(messageData);
        client->flush();
        client->waitForBytesWritten(3000);
    }
}

//send a message to a specific client
void Server::sendToClient(QTcpSocket *client, QString message)
{
    if(client)
    {
        QByteArray messageData = message.toUtf8();
        client->write(messageData);
        client->flush();
        client->waitForBytesWritten(3000);
    }
    delay(100);
}

//send a message to the current opponent
void Server::sendToOpponent(QString message)
{
    if(currentOpponent)
    {
        QByteArray messageData = message.toUtf8();
        currentOpponent->write(messageData);
        currentOpponent->flush();
        currentOpponent->waitForBytesWritten(3000);
    }
    delay(100);
}

//tell the client to end the game
void Server::endGame()
{
    sendToClient(currentOpponent, "#GAME_END");
}

//remove a client if it disconnected
void Server::disconnectClient()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    if (!client)
        return;
    if(currentOpponent)
    {
        if(client == currentOpponent)
        {
            currentOpponent = NULL;
            busy = false;
        }
    }
    connectedClients.removeAll(client);
    client->deleteLater();
}

void Server::delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);
    while( QTime::currentTime() < dieTime )
    {
        //wait for socket to write
    }
}
