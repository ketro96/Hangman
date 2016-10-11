#include "gamecontroller.h"

GameController::GameController(QString mode, QString username, QObject *parent) : QObject(parent)
{
    this->mode = mode;
    this->username = username;
    gameView = NULL;
    dictionary = NULL;
    qDebug() << mode;
    initializeGameController();
    endOfGame = new EndOfGame();
}

GameController::~GameController()
{
    delete dictionary;
    delete gameView;
    if(endOfGame) delete endOfGame;
}


void GameController::initializeGameController()
{
    this->gameView = new GameView();
    gameView->setAttribute(Qt::WA_DeleteOnClose);
    connect(gameView, SIGNAL(destroyed(QObject*)), this, SLOT(viewDestroyed()));
    this->word = "";
    this->dictionary = new Dictionary();

    modeStringList.append("SP_EASY");
    modeStringList.append("SP_MEDIUM");
    modeStringList.append("SP_HARD");
    modeStringList.append("MP_CLIENT");
    modeStringList.append("MP_HOST");

    switch (modeStringList.indexOf(this->mode)) {
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
    connect(endOfGame, SIGNAL(buttonBoxAnswer(bool)), this, SLOT(initializeNewGame(bool)));
    dictionaryList = dictionary->getDictionaryItems();
    getNextWord();
    gameView->show();
    initializeNewGame(true);
}

void GameController::initializeNewGame(bool restart)
{
    if(restart)
    {
        if(endOfGame) delete endOfGame;

        this->tryCounter = 0;
        this->roundTime = 0;
        this->gameTime = 0;
        this->guesses = 0;
        this->failCounter = 0;
        this->correctCounter = 0;

        getNextWord();
        gameView->newGame(word.length());
    }
    else
    {
        //close or show hauptmenue
    }
}

void GameController::getNextWord()
{
    /*
    std::default_random_engine generator;
    std::uniform_int_distribution dist(0, dictionaryArray->size() - 1);
    int StringIndex = dist(generator);
    */
    //word = dictionaryList.at(0);
    word = "KackGruening";
}

int GameController::getScore()
{
    return 100;
}

void GameController::checkKey(QString key)
{
    bool includesKey = false;
    guesses++;
    gameView->addUsedCharacter(key);

    if(word.contains(key, Qt::CaseInsensitive)){
        int posLastChar = 0;
        for(int i = 0; i < word.count(key, Qt::CaseInsensitive); i++){
            posLastChar = word.indexOf(key, posLastChar, Qt::CaseInsensitive);
            gameView->addCharacter(key, posLastChar);
            posLastChar += 1;
        }
        gameView->addUsedCharacter(key);

        if(correctCounter >= word.length()){
            gameView->enableKeyPressEvents(false);
            endOfGame->showDialog(true, getScore());
        }
        includesKey = true;
    }
    else{
        failCounter++;
        if(failCounter > 6){
            gameView->enableKeyPressEvents(false);
            endOfGame->showDialog(false, 0);

            //gameView->endGame(false);
        }
    }
    gameView->triggerPaintEvent(includesKey);
}

void GameController::closeView()
{
    gameView->close();
}

void GameController::viewDestroyed()
{
    emit deleted();
}
