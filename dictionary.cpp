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

void Dictionary::getDictionaryItems()
{
    bool successful;
    QSqlQuery query = queryDB("SELECT `word` FROM 'Dictionary';", successful);
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
        addDictionaryItems(ui->lineEdit->text(), ui->rbGroup->checkedId() +3);
    }else
    {
        QMessageBox::information(0,"Error", "Only words with 3-20 characters are valid.");
    }


}

void Dictionary::deleteDictionaryItems()
{

}

void Dictionary::on_btnDelete_clicked()
{
    bool successful;
    QSqlQuery query = queryDB("SELECT `word` FROM 'Dictionary';", successful);
    if (successful)
    {

    } else
    { //Fehler beim Ausführen des SQL-Statements
        QMessageBox::information(0,"Error", query.lastError().text());
    } //else: Fehler
}
