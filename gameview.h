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
    explicit GameView(QWidget *parent = 0);
    void triggerPaintEvent(bool includesCharacter, QString key);
    ~GameView();

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *e){guessed(e);}

private slots:
    void guessed(QKeyEvent *e);
    void endOfGame(bool won);

private:
    Ui::GameView*ui;
    int wordLength;
    QList<QString> *usedCharacterList;
    int counter;
    QRegularExpression regex;

signals:
    void keyPressed(QString key);

};

#endif // GAMEVIEW_H
