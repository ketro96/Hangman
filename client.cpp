#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    socket = NULL;
}

bool Client::connectClient(QString ipAdress, int port)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(clientReadyRead()),Qt::DirectConnection); //Ohne Directconnection? DC = Multithreaded?
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    socket->connectToHost(ipAdress, port);
    bool connected = false;
    if(socket->waitForConnected(10000))
    {
        connected = true;
    }
    if(!connected)
    {
        QMessageBox::information(0,"Not connected to host",socket->errorString());
    }
    return connected;
}

void Client::sendMessage(QString message)
{
    // send
    socket->write(message.toUtf8());
    socket->waitForBytesWritten(1000);
}

void Client::sendRequest()
{
    // send
    sendMessage("GAME_REQUEST");
}

void Client::clientReadyRead()
{
    QByteArray newData = socket->readAll();

    QString dataString(newData);
    qDebug() << dataString;
    if(dataString.left(5)=="GAME_")
    {
        if(dataString.mid(5)=="ACCEPT")
        {
            emit gameAnswer(true);
        }
        else if(dataString.mid(5)=="DENY")
        {
            emit gameAnswer(false);
        }
        /*
         * START
         * FAIL
         * SUCCESS
         * WIN
         * LOSE
         */
        emit receivedGameMessage(dataString.mid(5));
    }
    else if(dataString.left(5)=="CHAR_")
    {
        //LENGTH
        emit receivedCharMessage(dataString.mid(5));
    }
    else if(dataString.left(5)=="CHAT_")
    {
        //MESSAGE
        emit receivedChatMessage(dataString.mid(5));
    }
    else
    {
        qDebug() << "Received invalid Message.";
    }
}

void Client::disconnected()
{
    socket->deleteLater();
    emit disconnect();
    ///Programm Absturz?? bei delete? vlt funkt mit deletelater -> testen
    QMessageBox::information(0,"Disconnect","Lost connection to host.");
}
