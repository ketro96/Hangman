#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();

signals:
    void closed();

private slots:
    void on_btnEasterEgg_clicked();

protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::About *ui;
};

#endif // ABOUT_H
