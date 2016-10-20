// =================================================
// AUTHOR       : Alexander Höhn & Adrian Werner
// CREATE DATE  : 2016-10-12
// PURPOSE      : SQL access on player highscore
// =================================================

#include "highscore.h"
#include "ui_highscore.h"

Highscore::Highscore(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Highscore)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/images/Hangman.png"));
    validDBPath = false;
    if(readDB())
    {
        getHighscore();
    }
}

Highscore::~Highscore()
{
    closeDB();
    delete ui;
}

//Load database
bool Highscore::readDB()
{
    QString dbPath = QApplication::applicationDirPath() + "/hangme.sqlite";
    QFileInfo check_file(dbPath);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile())
    {
        db = QSqlDatabase::addDatabase("QSQLITE"); //db declared in header
        db.setDatabaseName(dbPath);
        validDBPath = true;
        return validDBPath;
    }
    else
    {
        return validDBPath;
    }
}

bool Highscore::isValid()
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

//Load highscores into ListWidget
void Highscore::getHighscore()
{
    bool successful = false;

    QSqlQuery query = queryDB("SELECT `nickname`, `score`  FROM 'Highscore' ORDER BY score DESC;", successful);
    if (successful)
    {
        ui->lwHighscore->clear();
        successful = query.first(); //jump to first item
        while (successful)
        {
            ui->lwHighscore->addItem(query.value(0).toString() +"     "+ query.value(1).toString());
            successful = query.next();
        } //while successful
    } else
    { //Fehler beim Ausführen des SQL-Statements
        QMessageBox::information(0,"Error", query.lastError().text());
    } //else: Fehler
}

//Add a new username + score to the database
void Highscore::addScore(QString username, int score)
{
    bool successful = false;
    // nickname is primary key -> problems because of unique ??
    QSqlQuery query = queryDB("INSERT INTO 'Highscore' VALUES ('" +username+ "', " +QString::number(score)+ ");", successful);
    if (successful)
    {
        ui->lwHighscore->clear();
        successful = query.first(); //jump to first item
        while (successful)
        {
            ui->lwHighscore->addItem(query.value(0).toString() +"     "+ query.value(1).toString());
            successful = query.next();
        } //while successful
    } else
    { //Fehler beim Ausführen des SQL-Statements
        QMessageBox::information(0,"Error", query.lastError().text());
    } //else: Fehler
}

//Query sample
QSqlQuery Highscore::queryDB(QString queryString, bool &successful)
{
    if (!db.open())
    {
        QMessageBox::information(0,"Error","Failed to load Database.");
        // close UI
        QSqlQuery emptyQuery;
        return emptyQuery;

    } else
    {
        QSqlQuery query;
        successful = query.exec(queryString);
        return query;
    }
}

//Clear highscore
void Highscore::resetHighscore()
{
    bool successful = false;
    QSqlQuery query = queryDB("DELETE FROM 'Highscore'", successful);
    if (successful)
    {
        getHighscore();
    } else
    { //Error executing SQL statement
        QMessageBox::information(0,"Error", query.lastError().text());
    }
}

void Highscore::on_pushButton_clicked()
{
    QMessageBox::StandardButton reset;
    reset = QMessageBox::question(this, "Reset highscore table", "Are you sure to reset your highscore table?", QMessageBox::Yes|QMessageBox::No);
    if (reset == QMessageBox::Yes) {
        resetHighscore();
    } else {

    }
}

//Close all database connections
void Highscore::closeDB()
{
    QString connection;
    connection = db.connectionName();
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connection);
}

void Highscore::closeEvent(QCloseEvent *)
{
    emit closed();
}
