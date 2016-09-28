#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QtGui>
#include <QWidget>

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void guessed(QKeyEvent *e);

private:
    Ui::MyWidget *ui;

    int counter;
    int wordLenght;

};

#endif // MYWIDGET_H
