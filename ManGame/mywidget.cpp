#include "mywidget.h"
#include "ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    this->counter = 0;
    this->wordLenght = 3;
}
MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::paintEvent(QPaintEvent *event)
{
    //create a QPainter and pass a pointer to the device.
    //A paint device can be a QWidget, a QPixmap or a QImage
    QPainter painter(this);


    //create a black pen that has solid line
    //and the width is 2.
    QPen myPen(Qt::black, 4, Qt::SolidLine);
    painter.setPen(myPen);
    painter.drawLine(50,50,50,300);
    painter.drawLine(30,300,160,300);
    painter.drawLine(50,50,140,50);
    painter.drawLine(140,50,140,90);

    if(counter == 1){
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));
        painter.drawRoundRect(115,90,50,50, 100,100);
    }

    if(counter == 2){
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));
        painter.drawRoundRect(115,90,50,50, 100,100);
        painter.drawLine(140, 140, 140, 200);
    }
    if(counter == 3){
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));
        painter.drawRoundRect(115,90,50,50, 100,100);
        painter.drawLine(140, 140, 140, 200);
        painter.drawLine(140,160, 110, 140);
    }
    if(counter == 4){
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));
        painter.drawRoundRect(115,90,50,50, 100,100);
        painter.drawLine(140, 140, 140, 200);
        painter.drawLine(140,160, 110, 140);
        painter.drawLine(140,160, 170, 140);
    }
    if(counter == 5){
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));
        painter.drawRoundRect(115,90,50,50, 100,100);
        painter.drawLine(140, 140, 140, 200);
        painter.drawLine(140,160, 110, 140);
        painter.drawLine(140,160, 170, 140);
        painter.drawLine(140, 200, 110, 230);
    }
    if(counter == 6){
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));
        painter.drawRoundRect(115,90,50,50, 100,100);
        painter.drawLine(140, 140, 140, 200);
        painter.drawLine(140,160, 110, 140);
        painter.drawLine(140,160, 170, 140);
        painter.drawLine(140, 200, 110, 230);
        painter.drawLine(140,200, 170, 230);
    }

    int xPos = 190;
    for(int i = 0; i < wordLenght; i++){
        painter.setRenderHint(QPainter::Antialiasing, false);
        painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));
        painter.drawLine(xPos, 300, xPos + 16, 300);

        painter.setFont(QFont("times",22));
        painter.drawText(xPos, 298, "A");

        xPos += 40;
    }

}


void MyWidget::guessed(QKeyEvent *e){

}

void MyWidget::on_pushButton_clicked() //Fail
{
    counter++;
    if(counter < 7)
        update();

}

void MyWidget::on_pushButton_2_clicked() //Reset
{
    counter = 0;
    update();

}
