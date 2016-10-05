#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QtGui>
#include <QWidget>
#include <QStringList>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *e){
        guessed(e);
    };

private slots:
    void guessed(QKeyEvent *e);
    void endOfGame(bool won);

private:
    Ui::MyWidget *ui;

    int counter;
    QString word;
    QString *characterArray;
    QList<QString> *usedCharacterList;
    int guesses;
    QRegularExpression regex;
    bool won;
    bool lost;

};

#endif // MYWIDGET_H
