#include "gamecontroller.h"

GameController::GameController(QString mode, QString username, QObject *parent) : QObject(parent)
{
    this->mode = mode;
    this->username = username;
    gameView = NULL;
    dictionary = NULL;
    highscore = NULL;
    timer = NULL;
    qDebug() << mode;
    endOfGame = NULL;
}

GameController::~GameController()
{
    if(timer) timer->stop(); delete timer;
    if(dictionary) delete dictionary;
    if(highscore) delete highscore;
}


void GameController::initializeGameController(bool accepted)
{
    modeStringList.append("SP_EASY");
    modeStringList.append("SP_MEDIUM");
    modeStringList.append("SP_HARD");
    modeStringList.append("MP_CLIENT");
    modeStringList.append("MP_HOST");
    this->timer = new QTimer(this);

    switch (modeStringList.indexOf(this->mode)) {
    case 0:
        //standard settings
        accepted = true;
        break;
    case 1:
        this->roundTime = 10;
        setGameTimer(true);
        break;
    case 2:
        this->gameTime = 30;
        setGameTimer(false);
        break;
    case 3:
        //client settings
        break;
    case 4:
        //host setting
        break;
    default:
        qDebug() << "Invalid gamemode";
        break;
    }
    if(accepted)
    {
        this->gameView = new GameView();
        connect(gameView, SIGNAL(keyPressed(QString)), this, SLOT(checkKey(QString)));
        connect(gameView, SIGNAL(destroyed(QObject*)), this, SLOT(viewDestroyed()));
        gameView->setAttribute(Qt::WA_DeleteOnClose);
        this->word = "";
        this->dictionary = new Dictionary();
        this->highscore = new Highscore();
        this->lastWordPos = 0;

        dictionaryMap = dictionary->getDictionaryItemObject();
        getNextWord();
        gameView->show();
        initializeNewGame(true);
    }
}

void GameController::initializeNewGame(bool restart)
{
    if(restart)
    {
        this->failCounter = 0;
        this->correctCounter = 0;

        getNextWord();
        gameView->newGame(word.length());
        timer->start();
    }
    else
    {
        closeView();
    }
}

void GameController::getNextWord()
{

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    int pos = qrand() % ((dictionaryMap.size()) - 2) + 2;
    pos -= 2;
    if(pos == lastWordPos)
    {
        pos++;
    }
    this->word = dictionaryMap.keys().at(pos);
    lastWordPos = pos;
    qDebug() << pos;
}

int GameController::getScore()
{
    return 100 * (dictionaryMap.value(word)+1) * (6 - failCounter) / (word.length() * 0.5);
}

void GameController::setGameTimer(bool perRound)
{
    //timer->setSingleShot(!perRound);
    timer->setInterval(perRound ? roundTime * 1000 : gameTime * 1000);
    if(perRound){
        connect(timer, SIGNAL(timeout()), this, SLOT(wrongCharacter()));
    }
    else{
        connect(timer, SIGNAL(timeout()), this, SLOT(timeIsUp()));
    }
}

void GameController::wrongCharacter()
{
    failCounter++;
    if(failCounter > 5)
    {
        gameOver(false);
    }
    gameView->triggerPaintEvent(false);

}

void GameController::timeIsUp()
{
    gameOver(false);
}

void GameController::gameOver(bool win)
{
    timer->stop();
    gameView->enableKeyPressEvents(false);
    if(win){
        highscore->addScore(this->username, getScore());
    }
    endOfGame = new EndOfGame();
    connect(endOfGame, SIGNAL(buttonBoxAnswer(bool)), this, SLOT(initializeNewGame(bool)));
    endOfGame->setAttribute(Qt::WA_DeleteOnClose);
    endOfGame->showDialog(win, win ? getScore() : 0);
}

void GameController::checkKey(QString key)
{
    if(mode == "SP_MEDIUM"){
        timer->stop();
        timer->start();
    }
    if(word.contains(key, Qt::CaseInsensitive)){
        int posLastChar = 0;
        int characterCount = word.count(key, Qt::CaseInsensitive);
        for(int i = 0; i < characterCount; i++){
            posLastChar = word.indexOf(key, posLastChar, Qt::CaseInsensitive);
            gameView->addCharacter(key, posLastChar);
            posLastChar += 1;
        }
        if(!gameView->addUsedCharacter(key)){
            correctCounter += characterCount; //add the count of characters that where added
            gameView->triggerPaintEvent(true);
        }
        if(correctCounter >= word.length()){
            gameOver(true);
        }
    }
    else{
        if(!gameView->addUsedCharacter(key)){
            wrongCharacter();
        }
    }
}

void GameController::getGameMessage(QString message)
{
    if(message == "END")
    {
        QMessageBox::information(0,"End of game","Your opponent disconnected.");
        closeView();
    }
}

void GameController::closeView()
{
    if(gameView)
    {
        gameView->close();
    }
}

void GameController::viewDestroyed()
{
    gameView = NULL;
    emit closed();
}

