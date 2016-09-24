#ifndef CONNECTIONSETUP_H
#define CONNECTIONSETUP_H

#include <QDialog>
#include <clientserver.h>
#include <chatroom.h>

namespace Ui {
class ConnectionSetup;
}

class ConnectionSetup : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionSetup(QWidget *parent = 0);
    ~ConnectionSetup();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::ConnectionSetup *ui;
    ClientServer *cServer;
    ChatRoom *chatRoom;
};

#endif // CONNECTIONSETUP_H
