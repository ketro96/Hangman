#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QtGui>
#include <QStringList>

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
    bool addUsedCharacter(QString key); //return if already exists
    void addCharacter(QString key, int pos);
    void newGame(int wordLength);
    void enableKeyPressEvents(bool enable);
    void showTimerTimeLeft(QString time);
    void setTurn(QString user);

signals:
    void openChat();

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *e){guessed(e);}

private slots:
    void guessed(QKeyEvent *e);

private:
    Ui::GameView *ui;
    int wordLength;
    QString characterArray;
    QList<QString> usedCharacterList;
    int counter;
    QRegularExpression regex;
    bool keyPressEventsEnabled;


signals:
    void keyPressed(QString key);

};

#endif // GAMEVIEW_H
