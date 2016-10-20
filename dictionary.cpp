// =================================================
// AUTHOR       : Alexander Höhn & Adrian Werner
// CREATE DATE  : 2016-10-12
// PURPOSE      : SQL access on word dictionary
// =================================================

#include "dictionary.h"
#include "ui_dictionary.h"

Dictionary::Dictionary(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dictionary)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/images/Hangman.png"));
    validDBPath = false;
    if(readDB())
    {
        getDictionaryItems();
    }
    this->regex = QRegularExpression("^[A-Za-z]{3,13}+$");
    ui->rbGroup->setId(ui->rbEasy, 0);
    ui->rbGroup->setId(ui->rbMedium, 1);
    ui->rbGroup->setId(ui->rbHard, 2);
}

Dictionary::~Dictionary()
{
    closeDB();
    delete ui;
}

//Load database
bool Dictionary::readDB()
{
    QString dbPath = QApplication::applicationDirPath() + "/hangme.sqlite";
    QFileInfo check_file(dbPath);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile())
    {
        db = QSqlDatabase::addDatabase("QSQLITE", "DictionaryConnection"); //db declared in header
        db.setDatabaseName(dbPath);
        validDBPath = true;
        return validDBPath;
    }
    else
    {
        return validDBPath;
    }
}

bool Dictionary::isValid()
{
    if(validDBPath)
    {
        return db.isValid();
    }
    else
    {
        return false;
    }
}

//Close all database connections
void Dictionary::closeDB()
{
    QString connection;
    connection = db.connectionName();
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connection);
}

//Query sample
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


//Load items from database
void Dictionary::getDictionaryItems()
{
    bool successful = false;
    QSqlQuery query = queryDB("SELECT `word` FROM 'Dictionary'", successful);
    if (successful)
    {
        successful = query.first(); //jump to first item
        while (successful)
        {
            ui->lwDictionary->addItem(query.value(0).toString());
            successful = query.next();
        } //while successful
    } else
    { //Error executing SQL statement
        QMessageBox::information(0,"Error", query.lastError().text());
    }
}

//Return map of words
QMap<QString, int> Dictionary::getDictionaryItemObject()
{
    bool successful = false;
    QSqlQuery query = queryDB("SELECT `word` FROM 'Dictionary'", successful);
    QMap<QString, int> wordMap;
    if (successful)
    {
        successful = query.first(); //jump to first item
        while (successful)
        {
            wordMap.insert(query.value(0).toString(), query.value(1).toInt());
            successful = query.next();
        } //while successful
    } else
    { //Error executing SQL statement
        QMessageBox::information(0,"Error", query.lastError().text());
        //Fill map with a single word
        wordMap.insert("dictionary",1);
    }
    return wordMap;
}

//Add new words + difficulty to database
void Dictionary::addDictionaryItems(QString word, int difficutly)
{
    bool successful = false;
    QSqlQuery query = queryDB("INSERT INTO 'Dictionary' VALUES ('" +word+ "', " +QString::number(difficutly)+ ");", successful);
    if (successful)
    {
        ui->lwDictionary->clear();
        ui->lineEdit->clear();
        getDictionaryItems();
    } else
    { //Error executing SQL statement
        QMessageBox::information(0,"Error", query.lastError().text());
    }
}

//Get word from ui
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

//Delete word from database
void Dictionary::deleteDictionaryItems(QString item)
{
    bool successful = false;
    QSqlQuery query = queryDB("DELETE FROM Dictionary WHERE `word` LIKE '" +item+ "';", successful);
    if (successful)
    {
        ui->lwDictionary->clear();
        getDictionaryItems();
    } else
    { //Error executing SQL statement
        QMessageBox::information(0,"Error", query.lastError().text());
    }
}

void Dictionary::on_btnDelete_clicked()
{
    deleteDictionaryItems(ui->lwDictionary->selectedItems().at(0)->text());
}

void Dictionary::closeEvent(QCloseEvent *)
{
    emit closed();
}
