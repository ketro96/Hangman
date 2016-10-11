#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QStringList>
#include <QDebug>
#include <dictionary.h>
#include <random>
#include <gameView.h>
#include <endofgame.h>
#include <QTime>

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(QString mode="", QString username="", QObject *parent = 0);
    ~GameController();
signals:
    void keyChecked(bool includesCharacter);
    void closed();

public slots:
    void closeView();

private slots:
    void getNextWord();

    void initializeGameController();

    void initializeNewGame(bool restart);

    void checkKey(QString key);

    void viewDestroyed();

    int getScore();

    void setGameTimer(bool perRound);

    void wrongCharacter();

    void gameOver(bool win);



private:
    GameView *gameView;
    int failCounter;
    int tryCounter;
    int correctCounter;
    int roundTime;
    int gameTime;
    QString word;
    int guesses;
    QString mode;
    QString username;
    Dictionary *dictionary;
    QList<QString> dictionaryList;
    QList<QString> modeStringList;
    QTimer timer;


    EndOfGame *endOfGame;
};

#endif // GAMECONTROLLER_H
