#include "gamecontroller.h"

GameController::GameController(QString mode, QString username, QObject *parent) : QObject(parent)
{

    this->mode = mode;
    this->username = username;
    qDebug() << mode;
    initializeGameController();

}

void GameController::initializeGameController()
{
    this->gameView = new GameView();
    this->word = "";
    this->dictionary = new Dictionary();

    this->modeStringList = new QList<QString>();
    modeStringList->append("SP_EASY");
    modeStringList->append("SP_MEDIUM");
    modeStringList->append("SP_HARD");
    modeStringList->append("MP_CLIENT");
    modeStringList->append("MP_HOST");

    switch (modeStringList->indexOf(this->mode)) {
    case 0:
        //standard settings
        break;
    case 1:
        this->roundTime = 10;
        break;
    case 2:
        this->gameTime = 30;
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
    connect(gameView, SIGNAL(keyPressed(QString)), this, SLOT(checkKey(QString)));
    //connect(this, SIGNAL(keyChecked(bool)), gameView, SLOT(triggerPaintEvent(bool, QString)));
    //connect(gameView, SIGNAL(startNewGame()), this, SLOT(initializeNewGame()));

    dictionaryList = dictionary->getDictionaryItems();
    getNextWord();
    gameView->show();
    initializeNewGame();
}

void GameController::initializeNewGame()
{
    this->tryCounter = 0;
    this->roundTime = 0;
    this->gameTime = 0;
    this->guesses = 0;
    this->counter = 0;
    this->characterArray = new QString [word.length()];
    this->usedCharacterList = new QList<QString>();

    getNextWord();
}

void GameController::getNextWord()
{
    /*
    std::default_random_engine generator;
    std::uniform_int_distribution dist(0, dictionaryArray->size() - 1);
    int StringIndex = dist(generator);
    */
    //word = dictionaryArray[0];
}

void GameController::checkKey(QString key)
{
    bool includesKey = false;
    guesses++;

    if(word.contains(key, Qt::CaseInsensitive)){
        int posLastChar = 0;
        for(int i = 0; i < word.count(key, Qt::CaseInsensitive); i++){
            posLastChar = word.indexOf(key, posLastChar, Qt::CaseInsensitive);
            characterArray[posLastChar] = key;
            posLastChar += 1;
        }
        if(!usedCharacterList->contains(key)){
            usedCharacterList->append(key);
        }
        if(counter > 6){
            //endOfGame(true);
        }
    }
    else{
        counter++;
        if(counter < 7){

            if(!usedCharacterList->contains(key)){
                usedCharacterList->append(key);
            }
        }
        else{
            //endOfGame(false);
        }
    }


}

