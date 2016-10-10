#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QtGui>
#include <QStringList>
#include <QDebug>
#include <dictionary.h>

namespace Ui {
class GameView;
}

class GameView : public QWidget
{
    Q_OBJECT

public:
    explicit GameView(QString mode, QString username, QWidget *parent = 0);
    ~GameView();

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *e){guessed(e);}

private slots:
    void guessed(QKeyEvent *e);
    void endOfGame(bool won);

private:
    Ui::GameView*ui;
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

#endif // GAMEVIEW_H
