#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class Highscore;
}

class Highscore : public QWidget
{
    Q_OBJECT

public:
    explicit Highscore(QWidget *parent = 0);
    ~Highscore();
    void addScore(QString username, int score);


signals:
    void closed();

private slots:
    void getHighscore();

    void readDB();

    QSqlQuery queryDB(QString queryString, bool &successful);

    void resetHighscore();

    void on_pushButton_clicked();

protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::Highscore *ui;
    QSqlDatabase db;
};

#endif // HIGHSCORE_H
