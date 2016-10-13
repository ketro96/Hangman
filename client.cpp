// =================================================
// AUTHOR       : Alexander Höhn & Adrian Werner
// CREATE DATE  : 2016-10-12
// PURPOSE      : Connect to server and send data
// =================================================

#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    socket = NULL;
}

//Create socket and try to connect to server
bool Client::connectClient(QString ipAdress, int port)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(clientReadyRead()),Qt::QueuedConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    socket->connectToHost(ipAdress, port);
    bool connected = false;
    if(socket->waitForConnected(30000))
    {
        connected = true;
    }
    if(!connected)
    {
        QMessageBox::information(0,"Connection failed",socket->errorString());
        emit closed();
    }
    return connected;
}

//Write message on socket
void Client::sendMessage(QString message)
{
    socket->write(message.toUtf8());
    socket->waitForBytesWritten(3000);
    delay(100);
}

//Send a game request
void Client::sendRequest()
{
    // send
    sendMessage("#GAME_REQUEST");
}

//Read messages from server and emit matching signals
void Client::clientReadyRead()
{
    QByteArray newData = socket->readAll();
    QStringList splitList;
    QString dataString(newData);

    if(dataString.contains("#GAME_") || dataString.contains("#CHAT_"))
    {
        //Clear tcp stream complications
        splitList =  dataString.split("#");
        foreach (QString message, splitList)
        {
            if(message.left(5)=="CHAT_")
            {

                emit receivedChatMessage(message.mid(5));
            }
            else
            {
                if(message.mid(5)=="ACCEPT")
                {
                    emit gameAnswer(true);
                }
                else if(message.mid(5)=="DENY")
                {
                    emit gameAnswer(false);
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

//Send a game aborted message
void Client::endGame()
{
    sendMessage("#GAME_END");
}

//Client disconnected from server
void Client::disconnected()
{
    socket->deleteLater();
    emit disconnect();
    QMessageBox::information(0,"Disconnect","Lost connection to host.");
}

//Delay for tcp messages to avoid chains of messages
void Client::delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);
    while( QTime::currentTime() < dieTime )
    {
        //wait for socket to write
    }
}

