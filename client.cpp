#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    socket = NULL;
}

bool Client::connectClient(QString ipAdress, int port)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(clientReadyRead()),Qt::QueuedConnection); //Ohne Directconnection? DC = Multithreaded?
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

void Client::sendMessage(QString message)
{
    // send
    socket->write(message.toUtf8());
    socket->waitForBytesWritten(3000);
    delay(100);
}

void Client::sendRequest()
{
    // send
    sendMessage("#GAME_REQUEST");
}

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

void Client::endGame()
{
    sendMessage("#GAME_END");
}

void Client::disconnected()
{
    socket->deleteLater();
    emit disconnect();
    QMessageBox::information(0,"Disconnect","Lost connection to host.");
}

void Client::delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);
    while( QTime::currentTime() < dieTime )
    {
        //wait for socket to write
    }
}

