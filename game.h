#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QtGui>
#include <QStringList>
#include <QDebug>
#include <dictionary.h>

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QString mode, QString username, QWidget *parent = 0);
    ~Game();

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *e){guessed(e);}

private slots:
    void guessed(QKeyEvent *e);
    void endOfGame(bool won);

private:
    Ui::Game *ui;
    int counter;
    int tryCounter;
    int roundTime;
    int gameTime;
    QString word;
    QString *characterArray;
    QList<QString> *usedCharacterList;
    int guesses;
    QRegularExpression regex;
    bool won;
    bool lost;
    QString mode;
    QString username;
    Dictionary *dictionary;
};

#endif // GAME_H
