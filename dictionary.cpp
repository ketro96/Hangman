#include "dictionary.h"
#include "ui_dictionary.h"

Dictionary::Dictionary(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dictionary)
{
    ui->setupUi(this);
    readDB();
    getDictionaryItems();
    this->regex = QRegularExpression("^[A-Za-z]{3,20}+$");
    ui->rbGroup->setId(ui->rbEasy, 0);
    ui->rbGroup->setId(ui->rbMedium, 1);
    ui->rbGroup->setId(ui->rbHard, 2);
}

Dictionary::~Dictionary()
{
    delete ui;
}

void Dictionary::readDB()
{
    QString dbPath = "/Users/Alexander/Programmieren/Hangman/hangme.sqlite";
    db = QSqlDatabase::addDatabase("QSQLITE"); //db ist im Header deklariert
    db.setDatabaseName(dbPath);
}

QSqlQuery Dictionary::queryDB(QString queryString, bool &successful)
{
    if (!db.open())
    {
        QMessageBox::information(0,"Error","Failed to load Database.");
        // close UI

    } else
    {
        QSqlQuery query;
        successful = query.exec(queryString);
        return query;
    }
}

QString *Dictionary::getDictionaryItems(int difficulty)
{
    bool successful;
    QSqlQuery query = queryDB("SELECT `word` FROM 'Dictionary' WHERE difficulty = " +QString::number(difficulty)+ ";", successful);
    QString *wordArray = new QString [query.size()];
    if (successful)
    {
        int i = 0;
        successful = query.first(); //jump to first item
        while (successful)
        {
            wordArray[i] = query.value(0).toString();
            successful = query.next();
        } //while successful
    } else
    { //Fehler beim Ausführen des SQL-Statements
        QMessageBox::information(0,"Error", query.lastError().text());
    } //else: Fehler
    return wordArray;
}

void Dictionary::getDictionaryItems()
{
    bool successful;
    QSqlQuery query = queryDB("SELECT `word` FROM 'Dictionary' ORDER BY rowid;", successful);
    if (successful)
    {
        ui->lwDictionary->clear();
        successful = query.first(); //jump to first item
        while (successful)
        {
            ui->lwDictionary->addItem(query.value(0).toString());
            successful = query.next();
        } //while successful
    } else
    { //Fehler beim Ausführen des SQL-Statements
        QMessageBox::information(0,"Error", query.lastError().text());
    } //else: Fehler
}

void Dictionary::addDictionaryItems(QString word, int difficutly)
{
    bool successful;
    QSqlQuery query = queryDB("INSERT INTO 'Dictionary' VALUES ('" +word+ "', " +QString::number(difficutly)+ ");", successful);
    if (successful)
    {
        getDictionaryItems();
        ui->lineEdit->clear();
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

void Dictionary::deleteDictionaryItems(int id)
{
    bool successful;
    QSqlQuery query = queryDB("DELETE FROM Dictionary WHERE rowid = (SELECT COUNT(*) FROM Dictionary b WHERE " +QString::number(id)+ " >= b.rowid ORDER BY rowid);", successful);
    if (successful)
    {
        getDictionaryItems();
    } else
    { //Fehler beim Ausführen des SQL-Statements
        QMessageBox::information(0,"Error", query.lastError().text());
    } //else: Fehler
}

void Dictionary::on_btnDelete_clicked()
{
    //deleteDictionaryItems(ui->lwDictionary->SelectRows +1);
}
