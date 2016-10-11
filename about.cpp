#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
}

About::~About()
{
    delete ui;
}

void About::on_btnEasterEgg_clicked()
{
    this->setStyleSheet("background-color:black;");
    ui->lblAboutUs->setStyleSheet("color: rgb(255, 255, 255)");
    ui->lblAboutUs_2->setStyleSheet("color: rgb(255, 255, 255)");
    ui->lblAboutUs_3->setStyleSheet("color: rgb(255, 255, 255)");
    ui->lblAboutUs_4->setStyleSheet("color: rgb(255, 255, 255)");
    ui->lblAboutUs_5->setStyleSheet("color: rgb(255, 255, 255)");
    ui->lblAboutUs_6->setStyleSheet("color: rgb(255, 255, 255)");
    ui->lblAboutUs_7->setStyleSheet("color: rgb(255, 255, 255)");
    ui->lblAboutUs_8->setStyleSheet("color: rgb(255, 255, 255)");
    ui->lblAboutUs_9->setStyleSheet("color: rgb(255, 255, 255)");
    ui->lblAboutUs_10->setStyleSheet("color: rgb(255, 255, 255)");
    ui->lblAboutUs_11->setStyleSheet("color: rgb(255, 255, 255)");
    ui->lblAboutUs_12->setStyleSheet("color: rgb(255, 255, 255)");
    ui->lblCopyright->setStyleSheet("color: rgb(255, 255, 255)");
}

void About::closeEvent(QCloseEvent *)
{
    emit closed();
}
