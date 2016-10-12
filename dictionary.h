#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>
#include <QStringList>

namespace Ui {
class Dictionary;
}

class Dictionary : public QWidget
{
    Q_OBJECT

public:
    explicit Dictionary(QWidget *parent = 0);
    ~Dictionary();

signals:
void closed();

public slots:
    QMap<QString, int> getDictionaryItemObject(); //return QString List

private slots:
    void on_btnAdd_clicked();

    void on_btnDelete_clicked();

    QSqlQuery queryDB(QString queryString, bool &successful);

    void addDictionaryItems(QString word, int difficutly);

    void deleteDictionaryItems(QString item);

    void readDB();

    void closeDB();

    void getDictionaryItems(); //show in UI

protected:
    void  closeEvent(QCloseEvent*);

private:
    Ui::Dictionary *ui;
    QSqlDatabase db;
    QRegularExpression regex;
};

#endif // DICTIONARY_H

