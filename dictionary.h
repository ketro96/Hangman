#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class Dictionary;
}

class Dictionary : public QWidget
{
    Q_OBJECT

public:
    explicit Dictionary(QWidget *parent = 0);
    ~Dictionary();

private slots:
    void on_btnAdd_clicked();

    void on_btnDelete_clicked();

    QSqlQuery queryDB(QString queryString, bool &successful);

    void getDictionaryItems();

    void addDictionaryItems(QString word, int difficutly);

    void deleteDictionaryItems(int id);

    void readDB();

private:
    Ui::Dictionary *ui;
    QSqlDatabase db;
    QRegularExpression regex;
};

#endif // DICTIONARY_H

