#include "gameview.h"
#include "ui_gameView.h"

GameView::GameView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameView)
{
    ui->setupUi(this);
    this->regex = QRegularExpression("[A-Za-z]");
}

GameView::~GameView()
{
    delete ui;
}

void GameView::paintEvent(QPaintEvent *event)
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

    for(int i = 0; i < wordLength; i++){
        painter.setRenderHint(QPainter::Antialiasing, false);
        painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));
        painter.drawLine(xPos, 300, xPos + 16, 300);

        painter.setFont(QFont("times",22));
        painter.drawText(xPos, 298, characterArray[i].toUpper());
        xPos += 40;
    }

    xPos =20;
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));


    painter.setFont(QFont("arial",20));
    painter.drawText(xPos, 350, "Benutzte Buchstaben:");
    xPos += 200;

    for(int i = 0; i < usedCharacterList.count(); i++){

        painter.drawText(xPos, 350, usedCharacterList.at(i).toUpper());
        xPos += 18;
    }
}


void GameView::endGame(bool won){


}

void GameView::triggerPaintEvent(bool includesCharacter)
{
    if(!includesCharacter)
    {
        counter++;
    }
    update();
}

void GameView::newGame(int wordLength)
{
    this->wordLength = wordLength;
    this->usedCharacterList.clear();
    this->characterArray;
    this->counter = 0;
    update();
}

void GameView::addCharacter(QString key, int pos)
{
    characterArray[pos] = key[0];
}


void GameView::addUsedCharacter(QString key)
{
    if(!usedCharacterList.contains(key)){
        usedCharacterList.append(key);
    }
}


void GameView::guessed(QKeyEvent *e){
    QRegularExpressionMatch match = regex.match(e->text());
    if(match.hasMatch()){
        emit keyPressed(e->text());
    }
}
