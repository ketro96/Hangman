#ifndef CONNECTIONSETUP_H
#define CONNECTIONSETUP_H

#include <QDialog>

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

signals:
    void connectClient(QString ipAdress, int port);

private:
    Ui::ConnectionSetup *ui;
};

#endif // CONNECTIONSETUP_H
