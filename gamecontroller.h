#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QStringList>
#include <QDebug>
#include <dictionary.h>
#include <random>
#include <gameView.h>

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(QString mode="", QString username="", QObject *parent = 0);
    ~GameController();
signals:

private slots:
    void getNextWord();

    void initializeGameController();

    void initializeNewGame();

    void checkKey(QString key);

    void viewDestroyed();


private:
    GameView *gameView;
    int counter;
    int tryCounter;
    int roundTime;
    int gameTime;
    QString word;
    int guesses;
    QString mode;
    QString username;
    Dictionary *dictionary;
    QList<QString> dictionaryList;
    QList<QString> modeStringList;

public slots:
void closeView();

signals:
    void keyChecked(bool includesCharacter);
    void deleted();
};

#endif // GAMECONTROLLER_H
