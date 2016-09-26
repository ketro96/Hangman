#ifndef CONNECTION_H
#define CONNECTION_H
//#include <QTcpSocket>
#include <QtNetwork>

class Connection : public QTcpSocket
{
public:
    Connection(QObject *parent = 0);
    enum ConnectionState {
        WaitingForGreeting,
        ReadingGreeting,
        ReadyForUse
    };
    enum DataType {
        PlainText,
        Ping,
        Pong,
        Greeting,
        Undefined
    };

    QString name() const;
    void setGreetingMessage(const QString &message);
    bool sendMessage(const QString &message);

signals:
    void readyForUse();
    void newMessage(const QString &from, const QString &message);

protected:
    void timerEvent(QTimerEvent *timerEvent) Q_DECL_OVERRIDE;

private slots:
    void processReadyRead();
    void sendPing();
    void sendGreetingMessage();

private:
    int readDataIntoBuffer(int maxSize = MaxBufferSize);
    int dataLengthForCurrentDataType();
    bool readProtocolHeader();
    bool hasEnoughData();
    void processData();

    QString greetingMessage;
    QString username;
    QTimer pingTimer;
    QTime pongTime;
    QByteArray buffer;
    ConnectionState state;
    DataType currentDataType;
    int numBytesForCurrentDataType;
    int transferTimerId;
    bool isGreetingMessageSent;
    static const int TransferTimeout = 30 * 1000;
    static const int PongTimeout = 60 * 1000;
    static const int PingInterval = 5 * 1000;
    static const char SeparatorToken = ' ';

};

#endif // CONNECTION_H
