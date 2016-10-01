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
