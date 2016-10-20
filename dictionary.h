#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>
#include <QStringList>
#include <QFileInfo>

namespace Ui {
class Dictionary;
}

class Dictionary : public QWidget
{
    Q_OBJECT

public:
    explicit Dictionary(QWidget *parent = 0);
    ~Dictionary();
    bool isValid();

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
    bool readDB();
    void closeDB();
    void getDictionaryItems(); //show in UI

protected:
    void  closeEvent(QCloseEvent*);

private:
    Ui::Dictionary *ui;
    QSqlDatabase db;
    QRegularExpression regex;
    bool validDBPath;
};

#endif // DICTIONARY_H

