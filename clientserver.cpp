#include "clientserver.h"

ClientServer::ClientServer(QObject *parent) : QObject(parent)
{

}

bool ClientServer::connectClient(QString ipAdress, int port)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(clientReadyRead()),Qt::DirectConnection); //Ohne Directconnection? DC = Multithreaded?
    connect(socket, SIGNAL(disconnected()), this, SLOT(hostDisconnected()));
    socket->connectToHost(ipAdress, port);
    bool connected = false;
    if(socket->waitForConnected(10000))
    {
        connected = true;
    }
    if(!connected)
    {
        qDebug() << "not connected";
    }
    qDebug() << socket->errorString();
    return connected;
}

void ClientServer::sendMessage(QString message)
{
    // send
    socket->write(message.toUtf8());
    socket->waitForBytesWritten(1000);
    //socket->waitForReadyRead(-1);
}

void ClientServer::clientReadyRead()
{
    qDebug() << "readyRead";
    QByteArray newData = socket->readAll();

    QString dataString(newData);
    qDebug() << dataString;
    emit receivedMessage(dataString);
}

void ClientServer::hostDisconnected()
{
    qDebug() << "Host disconnected";
}
