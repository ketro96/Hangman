// =======================================================================================
// AUTHOR       : Alexander Höhn & Adrian Werner
// CREATE DATE  : 2016-10-12
// PURPOSE      : Backend class that controls the view and manages client/server requests
// =======================================================================================

#include "gamecontroller.h"

GameController::GameController(QString mode, QString username, QObject *parent) : QObject(parent)
{
    this->mode = mode;
    this->username = username;
    gameEnded = false;
    serverCheckCount = 0;
    gameView = NULL;
    dictionary = NULL;
    highscore = NULL;
    timer = NULL;
    updateLabelTimer = NULL;
    endOfGame = NULL;
}

GameController::~GameController()
{
    if(timer)
    {
        if(timer->isActive())
        {
            timer->stop();
        }
        delete timer;
    }
    if(updateLabelTimer) updateLabelTimer->stop(); delete updateLabelTimer;
    if(dictionary) delete dictionary;
    if(highscore) delete highscore;
}


void GameController::initializeGameController(bool accepted)
{
    //Check wich type of game was startet
    modeStringList.append("SP_EASY");
    modeStringList.append("SP_MEDIUM");
    modeStringList.append("SP_HARD");
    modeStringList.append("MP_CLIENT");
    modeStringList.append("MP_HOST");
    this->timer = new QTimer(this);
    this->updateLabelTimer = new QTimer(this);

    switch (modeStringList.indexOf(this->mode)) {
    case 0:
        //standard settings
        gameDifficulty = 1;
        break;
    case 1:
        this->roundTime = 10;
        gameDifficulty = 2;
        setGameTimer(true);
        break;
    case 2:
        this->gameTime = 30;
        gameDifficulty = 3;
        setGameTimer(false);
        break;
    case 3:
        //client settings
        gameDifficulty = 1;
        break;
    case 4:
        //host setting
        gameDifficulty = 1;
        break;
    default:
        accepted = false;
        //Invalid gamemode
        break;
    }
    if(accepted && mode != "MP_CLIENT" && mode != "MP_HOST")
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
    //Initialize attributes for server, connect signals and open game view
    else if(accepted && mode == "MP_HOST")
    {
        this->gameView = new GameView();
        connect(gameView, SIGNAL(keyPressed(QString)), this, SLOT(serverCheckKey(QString)));
        connect(gameView, SIGNAL(destroyed(QObject*)), this, SLOT(viewDestroyed()));
        gameView->setAttribute(Qt::WA_DeleteOnClose);
        this->word = "";
        this->dictionary = new Dictionary();
        this->lastWordPos = 0;
        dictionaryMap = dictionary->getDictionaryItemObject();
        //set current word
        getNextWord();
        gameView->setTurn("Your turn");
        gameView->show();
        initializeNewGame(true);
    }
    //Set attributes for client, connect signals and open game view
    else if(accepted && mode == "MP_CLIENT")
    {
        this->gameView = new GameView();
        connect(gameView, SIGNAL(keyPressed(QString)), this, SLOT(clientSendKey(QString)));
        connect(gameView, SIGNAL(destroyed(QObject*)), this, SLOT(viewDestroyed()));
        gameView->setAttribute(Qt::WA_DeleteOnClose);
        gameView->setTurn("Opponent's turn");
        gameView->show();
    }
}

void GameController::initializeNewGame(bool restart)
{
    //Initialize attributes for starting or restarting a game
    if(restart)
    {
        this->failCounter = 0;
        this->serverFailCounter = 0;
        this->clientFailCounter = 0;
        this->correctCounter = 0;
        this->serverCorrectCounter = 0;
        this->clientCorrectCounter = 0;

        if(gameDifficulty == 2)
        {
            updateLabelTimer->stop();
            this->timerTimeLeft = roundTime +1;
            updateTimerTimeLeftLabel();
            updateLabelTimer->start();

        }
        else if (gameDifficulty == 3)
        {
            updateLabelTimer->stop();
            this->timerTimeLeft = gameTime +1;
            updateTimerTimeLeftLabel();
            updateLabelTimer->start();
        }
        getNextWord();
        gameView->newGame(word.length());
        if(gameDifficulty != 1)
        {
            timer->start();
        }
    }
    else
    {
        closeView();
    }
}

void GameController::getNextWord()
{
    //Grab next random word of the dictionary
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    int pos = qrand() % ((dictionaryMap.size() + 3) - 3) + 3;
    pos -= 3;
    if(pos == lastWordPos)
    {
        pos >= dictionaryMap.size()-1 ? pos-- : pos++;
    }
    this->word = dictionaryMap.keys().at(pos);
    lastWordPos = pos;
}

int GameController::getScore()
{
    //Calculate the game score; 100 * word difficulty * guesses left / 0.5* length of the word * game level difficult
    return 100 * (dictionaryMap.value(word)+1) * (6 - failCounter) / (word.length() * 0.5) * gameDifficulty;
}

void GameController::setGameTimer(bool perRound)
{
    //Set and connect the timer for level 2 and 3
    timer->setInterval(perRound ? roundTime * 1000 : gameTime * 1000);
    updateLabelTimer->setInterval(1000);
    connect(updateLabelTimer, SIGNAL(timeout()), this, SLOT(updateTimerTimeLeftLabel()));
    if(perRound){
        connect(timer, SIGNAL(timeout()), this, SLOT(wrongCharacter()));
    }
    else{
        connect(timer, SIGNAL(timeout()), this, SLOT(timeIsUp()));
    }
}

void GameController::updateTimerTimeLeftLabel()
{
    //Update the time left label on the gameView
    gameView->showTimerTimeLeft("Time left: " + QString::number(timerTimeLeft-=1));
}

void GameController::wrongCharacter()
{
    failCounter++;
    if(failCounter > 5)
    {
        gameOver(false);
    }

    gameView->triggerPaintEvent(false);
    if(gameDifficulty == 2)
    {
        updateLabelTimer->stop();
        this->timerTimeLeft = roundTime +1;
        updateTimerTimeLeftLabel();
        updateLabelTimer->start();
    }
}

void GameController::serverWrongCharacter()
{
    serverFailCounter++;
    if(serverFailCounter > 5)
    {
        serverGameOver(false);
    }
    gameView->triggerPaintEvent(false);
}

void GameController::clientWrongCharacter()
{
    clientFailCounter++;
    if(clientFailCounter > 5)
    {
        serverGameOver(true);
    }
}

void GameController::timeIsUp()
{
    gameOver(false);
}

void GameController::gameOver(bool win)
{
    updateLabelTimer->stop();
    timer->stop();
    gameView->enableKeyPressEvents(false);
    if(win)
    {
        highscore->addScore(this->username, getScore());
    }
    endOfGame = new EndOfGame();
    connect(endOfGame, SIGNAL(buttonBoxAnswer(bool)), this, SLOT(initializeNewGame(bool)));
    endOfGame->setAttribute(Qt::WA_DeleteOnClose);
    endOfGame->showDialog(win, win ? getScore() : 0);
}

//Display Win/Lose message and send message to client
void GameController::serverGameOver(bool win)
{
    if(win)
    {
        //Server user wins
        QMessageBox::information(0,"Game Over","Game Over - You win!");
        emit gameMessage("#GAME_LOSE");
    }
    else
    {
        //Client user wins
        QMessageBox::information(0,"Game Over","Game Over - You lose!");
        emit gameMessage("#GAME_WIN");
    }
    gameEnded = true;
    closeView();
}

void GameController::checkKey(QString key)
{
    if(word.contains(key, Qt::CaseInsensitive))
    {
        int posLastChar = 0;
        int characterCount = word.count(key, Qt::CaseInsensitive);
        for(int i = 0; i < characterCount; i++)
        {
            posLastChar = word.indexOf(key, posLastChar, Qt::CaseInsensitive);
            gameView->addCharacter(key, posLastChar);
            posLastChar += 1;
        }
        if(!gameView->addUsedCharacter(key))
        {
            correctCounter += characterCount; //add the count of characters that where added
            gameView->triggerPaintEvent(true);
            if(mode == "SP_MEDIUM")
            {
                //Restart the timer
                timer->stop();
                timer->start();
                updateLabelTimer->stop();
                this->timerTimeLeft = roundTime +1;
                updateTimerTimeLeftLabel();
                updateLabelTimer->start();
            }
        }
        if(correctCounter >= word.length())
        {
            gameOver(true);
        }
    }
    else{
        //Add character to list if not added yet
        if(!gameView->addUsedCharacter(key))
        {
            wrongCharacter();
            if(mode == "SP_MEDIUM")
            {
                timer->stop();
                timer->start();
                updateLabelTimer->stop();
                this->timerTimeLeft = roundTime +1;
                updateTimerTimeLeftLabel();
                updateLabelTimer->start();
            }
        }
    }
}

//Check if key on server is valid and  send information to client
void GameController::serverCheckKey(QString key)
{
    gameView->setTurn("Opponent's turn");
    gameView->enableKeyPressEvents(false);
    serverCheckCount++;
    //initialize client view
    if(serverCheckCount == 1)
    {
        emit gameMessage("#GAME_LENGTH_"+QString::number(word.length()));
    }
    if(word.contains(key, Qt::CaseInsensitive))
    {
        int posLastChar = 0;
        int characterCount = word.count(key, Qt::CaseInsensitive);
        for(int i = 0; i < characterCount; i++)
        {
            posLastChar = word.indexOf(key, posLastChar, Qt::CaseInsensitive);
            emit gameMessage("#GAME_CHAR_"+key+"_"+QString::number(posLastChar));
            gameView->addCharacter(key, posLastChar);
            posLastChar += 1;
        }
        if(!gameView->addUsedCharacter(key))
        {
            serverCorrectCounter += characterCount; //add the count of characters that where added
            gameView->triggerPaintEvent(true);
        }
        if(serverCorrectCounter >= word.length())
        {
            serverGameOver(true);
        }
    }
    else{
        if(!gameView->addUsedCharacter(key))
        {
            serverWrongCharacter();
        }
    }
    if(serverCheckCount > 1)
    {
        emit gameMessage("#GAME_TURN");
    }
}

//Check if key from client is valid and send information to client
void GameController::clientCheckKey(QString key)
{
    if(word.contains(key, Qt::CaseInsensitive))
    {
        int posLastChar = 0;
        int characterCount = word.count(key, Qt::CaseInsensitive);
        for(int i = 0; i < characterCount; i++)
        {
            posLastChar = word.indexOf(key, posLastChar, Qt::CaseInsensitive);
            emit gameMessage("#GAME_CHAR_"+key+"_"+QString::number(posLastChar));
            emit gameMessage("#GAME_FCHAR_"+key);
            gameView->addCharacter(key, posLastChar);
            posLastChar += 1;
        }
        if(!gameView->addUsedCharacter(key))
        {
            clientCorrectCounter += characterCount; //add the count of characters that where added
            gameView->triggerPaintEvent(true);
        }
        if(clientCorrectCounter >= word.length())
        {
            serverGameOver(false);
        }
    }
    else
    {
        clientWrongCharacter();
        emit gameMessage("#GAME_FCHAR_"+key);
    }
    gameView->setTurn("          Your turn");
    gameView->enableKeyPressEvents(true);
}

//send pressed key from client to server
void GameController::clientSendKey(QString key)
{
    gameView->setTurn("Opponent's turn");
    gameView->enableKeyPressEvents(false);
    emit gameMessage("#GAME_CHAR_"+key);
}

//Get mesages from client/server and call matching functions
void GameController::getGameMessage(QString message)
{
    if(message == "END")
    {
        QMessageBox::information(0,"Game Over","Your opponent disconnected.");
        closeView();
    }
    else if(message.left(7) == "LENGTH_")
    {
        gameView->setTurn("          Your turn");
        gameView->newGame(message.mid(7).toInt());
    }
    else if(message.left(3) == "WIN")
    {
        QMessageBox::information(0,"Game Over","Game Over - You win!");
    }
    else if(message.left(4) == "LOSE")
    {
        QMessageBox::information(0,"Game Over","Game Over - You lose!");
    }
    else if(message.left(5) == "CHAR_" && mode == "MP_CLIENT")
    {
        gameView->addCharacter(message.mid(5,1),message.mid(7).toInt());
        gameView->triggerPaintEvent(true);
    }
    else if(message.left(6) == "FCHAR_")
    {
        gameView->addUsedCharacter(message.mid(6,1));
        gameView->triggerPaintEvent(true);
        gameView->triggerPaintEvent(false);
    }
    else if(message.left(5) == "CHAR_" && mode == "MP_HOST")
    {
        clientCheckKey(message.mid(5,1));
    }
    else if(message.left(4) == "TURN")
    {
        //Set active user
        gameView->setTurn("          Your turn");
        gameView->enableKeyPressEvents(true);
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
    if(!gameEnded)
    {
        emit closed();
    }
}

