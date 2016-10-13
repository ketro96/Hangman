#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QStringList>
#include <dictionary.h>
#include <random>
#include <gameView.h>
#include <endofgame.h>
#include <QTime>
#include <highscore.h>

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(QString mode="", QString username="", QObject *parent = 0);
    ~GameController();
signals:
    void keyChecked(bool includesCharacter);
    void closed();
    void gameMessage(QString message);

public slots:
    void closeView();
    void initializeGameController(bool accepted);
    void getGameMessage(QString message);

private slots:
    void getNextWord();
    void initializeNewGame(bool restart);
    void checkKey(QString key);
    void serverCheckKey(QString key);
    void clientCheckKey(QString key);
    void clientSendKey(QString key);
    void viewDestroyed();
    int getScore();
    void setGameTimer(bool perRound);
    void wrongCharacter();
    void serverWrongCharacter();
    void clientWrongCharacter();
    void gameOver(bool win);
    void serverGameOver(bool win);
    void timeIsUp();
    void updateTimerTimeLeftLabel();


private:
    GameView *gameView;
    int failCounter;
    int serverFailCounter;
    int clientFailCounter;
    int correctCounter;
    int serverCorrectCounter;
    int clientCorrectCounter;
    int serverCheckCount;
    int roundTime;
    int gameTime;
    bool gameEnded;
    QString word;
    QString mode;
    QString username;
    Dictionary *dictionary;
    QMap<QString, int> dictionaryMap;
    QList<QString> modeStringList;
    QTimer *timer;
    Highscore *highscore;
    int lastWordPos;
    EndOfGame *endOfGame;
    int gameDifficulty;
    QTimer *updateLabelTimer;
    int timerTimeLeft;
};

#endif // GAMECONTROLLER_H
