#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <QTcpSocket>
#include <QObject>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <mex_order.h>
#include <QMessageBox>

class TcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit TcpSocket(QObject *parent = 0);

signals:

public slots:

private:
    QTcpSocket *socket;
    QXmlStreamWriter xmlWriter;
    QXmlStreamReader* xmlReader;
    MEX_Order order;
    QString traderID;
};

#endif // TCPSOCKET_H
