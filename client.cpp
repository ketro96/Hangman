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
        QMessageBox::information(0,"Connected","Connected");
    }
    if(!connected)
    {
        QMessageBox::information(0,"Not connected","Could not connect to host.");
        qDebug() << "Client connection error:";
        qDebug() << socket->errorString();
    }

    return connected;
}

void Client::sendMessage(QString message)
{
    // send
    socket->write(message.toUtf8());
    socket->waitForBytesWritten(1000);
    //socket->waitForReadyRead(-1);
}

void Client::clientReadyRead()
{
    QByteArray newData = socket->readAll();

    QString dataString(newData);
    qDebug() << dataString;
    if(dataString.left(5)=="GAME_")
    {
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
    ///Programm Absturz?? bei delete? vlt funkt mit deletelater -> testen
    QMessageBox::information(0,"Disconnect","Lost connection to host.");
}
