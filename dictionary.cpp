#include "dictionary.h"
#include "ui_dictionary.h"

Dictionary::Dictionary(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dictionary)
{
    ui->setupUi(this);
    readDB();
    getDictionaryItems(true);
    this->regex = QRegularExpression("^[A-Za-z]{3,20}+$");
    ui->rbGroup->setId(ui->rbEasy, 0);
    ui->rbGroup->setId(ui->rbMedium, 1);
    ui->rbGroup->setId(ui->rbHard, 2);
}

Dictionary::~Dictionary()
{
    closeDB();
    delete ui;
}

void Dictionary::readDB()
{
    QString dbPath = QApplication::applicationDirPath() + "/hangme.sqlite";
    db = QSqlDatabase::addDatabase("QSQLITE", "DictionaryConnection"); //db ist im Header deklariert
    db.setDatabaseName(dbPath);
}

void Dictionary::closeDB()
{
    QString connection;
    connection = db.connectionName();
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connection);
}

QSqlQuery Dictionary::queryDB(QString queryString, bool &successful)
{
    if (!db.open())
    {
        QMessageBox::information(0,"Error","Failed to load Database.");
        QSqlQuery emtpyQuery;
        return emtpyQuery;
        // close UI

    } else
    {
        QSqlQuery query(db);
        successful = query.exec(queryString);
        return query;
    }
}

QList<QString> Dictionary::getDictionaryItems(bool uiIsShown)
{
    bool successful = false;
    QSqlQuery query = queryDB("SELECT `word` FROM 'Dictionary'", successful);
    QList<QString> wordList;
    if (successful)
    {
        successful = query.first(); //jump to first item
        while (successful)
        {
            wordList.append(query.value(0).toString());
            if(uiIsShown){
                ui->lwDictionary->addItem(query.value(0).toString());
            }
            successful = query.next();
        } //while successful
    } else
    { //Fehler beim Ausführen des SQL-Statements
        QMessageBox::information(0,"Error", query.lastError().text());
    } //else: Fehler
    return wordList;
}

void Dictionary::addDictionaryItems(QString word, int difficutly)
{
    bool successful = false;
    QSqlQuery query = queryDB("INSERT INTO 'Dictionary' VALUES ('" +word+ "', " +QString::number(difficutly)+ ");", successful);
    if (successful)
    {
        ui->lwDictionary->clear();
        ui->lineEdit->clear();
        getDictionaryItems(true);
    } else
    { //Fehler beim Ausführen des SQL-Statements
        QMessageBox::information(0,"Error", query.lastError().text());
    } //else: Fehler
}

void Dictionary::on_btnAdd_clicked()
{
    QRegularExpressionMatch match = regex.match(ui->lineEdit->text());
    if(match.hasMatch())
    {
        addDictionaryItems(ui->lineEdit->text(), ui->rbGroup->checkedId());
    }else
    {
        QMessageBox::information(0,"Error", "Only words with 3-20 characters are valid.");
    }
}

void Dictionary::deleteDictionaryItems(QString item)
{
    bool successful = false;
    QSqlQuery query = queryDB("DELETE FROM Dictionary WHERE `word` LIKE '" +item+ "';", successful);
    if (successful)
    {
        ui->lwDictionary->clear();
        getDictionaryItems(true);
    } else
    { //Fehler beim Ausführen des SQL-Statements
        QMessageBox::information(0,"Error", query.lastError().text());
    } //else: Fehler
}

void Dictionary::on_btnDelete_clicked()
{
    deleteDictionaryItems(ui->lwDictionary->selectedItems().at(0)->text());
}

void Dictionary::closeEvent(QCloseEvent *)
{
    emit closed();
}
