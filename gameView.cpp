#include "gameView.h"
#include "ui_gameView.h"

GameView::GameView(QString mode, QString username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameView)
{
    ui->setupUi(this);
    ui->setupUi(this);
    this->mode = mode;
    this->username = username;
    qDebug() << mode;

    this->word = "Hangman";

    this->tryCounter = 0;
    this->roundTime = 0;
    this->gameTime = 0;
    this->guesses = 0;
    this->counter = 0;
    this->characterArray = NULL;
    this->characterArray = new QString [word.length()];
    this->usedCharacterList = new QList<QString>();

    this->regex = QRegularExpression("[A-Za-z]");
    this->won = false;
    this->lost = false;
    this->dictionary = NULL;

    if(mode=="SP_EASY")
    {
        //standard settings
    }
    else if(mode=="SP_MEDIUM")
    {
        this->roundTime = 10;
    }
    else if(mode=="SP_HARD")
    {
        this->gameTime = 30;
    }
    else if(mode=="MP_CLIENT")
    {
        //client settings
    }
    else if(mode=="MP_HOST")
    {
        //host settings
    }
    else
    {
        qDebug() << "Invalid gamemode";
    }
}

GameView::~GameView()
{
    delete ui;
    delete characterArray;
    delete usedCharacterList;
    delete dictionary;
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

    for(int i = 0; i < word.length(); i++){
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

    for(int i = 0; i < usedCharacterList->count(); i++){

        painter.drawText(xPos, 350, usedCharacterList->at(i).toUpper());
        xPos += 18;
    }
}


void GameView::endOfGame(bool won){

    if(won){
        this->won = true;
    }
    else{
        lost = true;
    }
}

void GameView::guessed(QKeyEvent *e){
    guesses++;
    QRegularExpressionMatch match = regex.match(e->text());
    if(match.hasMatch()){

        if(word.contains(e->text(), Qt::CaseInsensitive)){
            int posLastChar = 0;
            for(int i = 0; i < word.count(e->text(), Qt::CaseInsensitive); i++){
                posLastChar = word.indexOf(e->text(), posLastChar, Qt::CaseInsensitive);
                characterArray[posLastChar] = e->text();
                posLastChar += 1;
            }
            if(!usedCharacterList->contains(e->text())){
                usedCharacterList->append(e->text());
            }
            if(counter > 6){
                endOfGame(true);
            }
        }
        else{
            counter++;
            if(counter < 7){

                if(!usedCharacterList->contains(e->text())){
                    usedCharacterList->append(e->text());
                }
            }
            else{
                endOfGame(false);
            }
        }
        update();
    }
}
