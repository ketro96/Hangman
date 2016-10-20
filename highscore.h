#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>
#include <QFileInfo>

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
    bool isValid();

signals:
    void closed();

private slots:
    void getHighscore();
    bool readDB();
    QSqlQuery queryDB(QString queryString, bool &successful);
    void resetHighscore();
    void on_pushButton_clicked();
    void closeDB();

protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::Highscore *ui;
    QSqlDatabase db;
    bool validDBPath;
};

#endif // HIGHSCORE_H
