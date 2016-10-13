#ifndef GAMEHELP_H
#define GAMEHELP_H

#include <QWidget>

namespace Ui {
class GameHelp;
}

class GameHelp : public QWidget
{
    Q_OBJECT

public:
    explicit GameHelp(QWidget *parent = 0);
    ~GameHelp();

signals:
    void closed();

protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::GameHelp *ui;
};

#endif // GAMEHELP_H
