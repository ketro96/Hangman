#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QtGui>
#include <QStringList>
#include <QDebug>
#include <dictionary.h>
#include <endofgame.h>

namespace Ui {
class GameView;
}

class GameView : public QWidget
{
    Q_OBJECT

public:
    explicit GameView(QWidget *parent = 0);
    void triggerPaintEvent(bool includesCharacter);
    ~GameView();
    void addUsedCharacter(QString key);
    void addCharacter(QString key, int pos);
    void newGame(int wordLength);
    void endGame(bool won);

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *e){guessed(e);}

private slots:
    void guessed(QKeyEvent *e);

private:
    Ui::GameView*ui;
    int wordLength;
    QString characterArray;
    QList<QString> usedCharacterList;
    int counter;
    QRegularExpression regex;
    EndOfGame *endOfGame;

signals:
    void keyPressed(QString key);

};

#endif // GAMEVIEW_H
