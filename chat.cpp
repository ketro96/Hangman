#include "chat.h"
#include "ui_chat.h"

Chat::Chat(QString mode, QString username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
    this->mode = mode;
    ui->btnRequestGame->hide();
    if(mode == "MP_CLIENT")
    {
        ui->lblHostInfo->hide();
        ui->btnRequestGame->show();
    }
    this->username = username;
}

Chat::~Chat()
{
    delete ui;
}

void Chat::on_btnSend_clicked()
{
    sendChatMessage();
}

void Chat::newServerInfo(QString ipAdress, QString port)
{
    ui->lblHostInfo->setText("This server is hosted on "+ipAdress+":"+port);
}


void Chat::getMessage(QString message)
{
    QListWidgetItem *messageItem = new QListWidgetItem(message);
    /** Set own user messsages blue
    if(message.contains(username+": "))
    {
         messageItem->setForeground(Qt::blue);
    }**/
    ui->lwChat->addItem(messageItem);
    ui->lwChat->scrollToBottom();
}

void Chat::getRequestMessage(QString username)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Game Request", "Dou you want to play against "+username+" ?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        emit gameAnswer(true);
    }
    else
    {
        emit gameAnswer(false);
    }
}


void Chat::on_edtChat_returnPressed()
{
    sendChatMessage();
}

void Chat::sendChatMessage()
{
    QString message = ui->edtChat->text();
    if(mode=="MP_HOST")
    {
        message.prepend(username+": ");
        QListWidgetItem *messageItem = new QListWidgetItem(message);
        ///Set own user messages = blue
        /// messageItem->setForeground(Qt::blue);
        ui->lwChat->addItem(messageItem);
        ui->lwChat->scrollToBottom();
    }
    message.prepend("#CHAT_");
    ui->edtChat->clear();
    emit sendMessage(message);
}

void Chat::on_btnRequestGame_clicked()
{
    emit gameRequest();
}

void Chat::disconnect()
{
    gameStarted(false);
}

void Chat::gameClosed()
{
    gameStarted(false);
}

void Chat::gameStarted(bool started)
{
    if(started)
    {
        ui->btnRequestGame->setDisabled(started);
        ui->btnRequestGame->setStyleSheet("background:gray;");
    }
    else
    {
        ui->btnRequestGame->setDisabled(started);
        ui->btnRequestGame->setStyleSheet("background:qlineargradient(spread:pad, x1:0.483318, y1:0.011, x2:0.483318, y2:1, stop:0 rgba(49, 97, 255, 255), stop:1 rgba(52, 157, 255, 255));");
    }
}

void Chat::closeEvent(QCloseEvent *)
{
    emit closed();
}
