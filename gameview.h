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
    ~GameView();

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *e){guessed(e);}

private slots:
    void guessed(QKeyEvent *e);
    void endOfGame(bool won);
    void triggerPaintEvent(bool includesCharacter);

private:
    Ui::GameView*ui;

    bool won;
    bool lost;

    QRegularExpression regex;

signals:
    void keyPressed(QString key);

};

#endif // GAMEVIEW_H
