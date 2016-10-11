#include "highscore.h"
#include "ui_highscore.h"

Highscore::Highscore(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Highscore)
{
    ui->setupUi(this);
    readDB();
    getHighscore();
}

Highscore::~Highscore()
{
    delete ui;
}

void Highscore::readDB()
{
    QString dbPath = QApplication::applicationDirPath() + "/hangme.sqlite";
    db = QSqlDatabase::addDatabase("QSQLITE"); //db ist im Header deklariert
    db.setDatabaseName(dbPath);
}

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

QSqlQuery Highscore::queryDB(QString queryString, bool &successful)
{
    if (!db.open())
    {
        QMessageBox::information(0,"Error","Failed to load Database.");
        // close UI
        //return NULL;

    } else
    {
        QSqlQuery query;
        successful = query.exec(queryString);
        return query;
    }
}

void Highscore::resetHighscore()
{
    bool successful = false;
    QSqlQuery query = queryDB("DELETE FROM 'Highscore'", successful);
    if (successful)
    {
        getHighscore();
    } else
    { //Fehler beim Ausführen des SQL-Statements
        QMessageBox::information(0,"Error", query.lastError().text());
    } //else: Fehler
}

void Highscore::on_pushButton_clicked()
{
    QMessageBox::StandardButton reset;
    reset = QMessageBox::question(this, "Reset Highscore Table", "Are you sure to reset your Highscore Table?", QMessageBox::Yes|QMessageBox::No);
    if (reset == QMessageBox::Yes) {
        resetHighscore();
    } else {

    }
}
