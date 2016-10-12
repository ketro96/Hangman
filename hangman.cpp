#include "hangman.h"
#include "ui_hangman.h"


Hangman::Hangman(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Hangman)
{
    ui->setupUi(this);
    ui->btnGoBack->hide();
    ui->btnGoBack->setIcon(QIcon(":/images/images/Back.png"));
    ui->btnSP_Easy->hide();
    ui->btnSP_Medium->hide();
    ui->btnSP_Hard->hide();
    ui->btnStartHost->hide();
    ui->btnFindHost->hide();
    server = NULL;
    client = NULL;
    chat = NULL;
    gameController = NULL;
    dictionary = NULL;
    highscore = NULL;
    about = NULL;
}

Hangman::~Hangman()
{
    //delete ui;
    if(server) delete server;
    if(client) delete client;
    if(chat) delete chat;
    if(gameController) delete gameController;
    if(dictionary) delete dictionary;
    if(highscore) delete highscore;
}


void Hangman::on_btnStartHost_clicked()
{
    server = new Server();
    chat = new Chat("MP_HOST", username);
    ///Same for chat as gC?
    connect(server, SIGNAL(receivedChatMessage(QString)), chat, SLOT(getMessage(QString)));
    connect(server, SIGNAL(receivedRequestMessage(QString)), chat, SLOT(getRequestMessage(QString)));
    connect(chat, SIGNAL(sendMessage(QString)), server, SLOT(sendToAllClients(QString)));
    connect(server, SIGNAL(serverInfo(QString,QString)), chat, SLOT(newServerInfo(QString, QString)));
    if(server->startServer())
    {
        this->setDisabled(true);
        chat->show();
        gameController = new GameController("MP_HOST", username);
        connect(gameController, SIGNAL(closed()), this, SLOT(enable()));
        connect(gameController, SIGNAL(closed()), this, SLOT(deleteController()));
    }
    else
    {
        //chat->disconnect()
        delete server;
        server = NULL;
        delete chat;
        chat = NULL;
        delete gameController;
        gameController = NULL;
        QMessageBox::information(0,"Error","Could not start server.");
    }
}

void Hangman::on_btnFindHost_clicked()
{
    client = new Client();
    ConnectionSetup *connectionSetup = new ConnectionSetup();
    //connect(client, SIGNAL(receivedMessage(QString)), this, SLOT(getMessage(QString)));
    connect(connectionSetup, SIGNAL(connectClient(QString, int)), this, SLOT(connectClient(QString,int)));
    connectionSetup->show();
}

void Hangman::on_btnSingleplayer_clicked()
{
    if(getUsername())
    {
        ui->btnSingleplayer->hide();
        ui->btnMultiplayer->hide();
        ui->btnGoBack->show();
        ui->btnSP_Easy->show();
        ui->btnSP_Medium->show();
        ui->btnSP_Hard->show();
    }
    //start Singleplayer gameView
}

void Hangman::on_btnMultiplayer_clicked()
{
    if(getUsername())
    {
        ui->btnSingleplayer->hide();
        ui->btnMultiplayer->hide();
        ui->btnGoBack->show();
        ui->btnFindHost->show();
        ui->btnStartHost->show();
    }
}

void Hangman::connectClient(QString ipAdress, int port)
{
    if(client->connectClient(ipAdress, port))
    {
        client->sendMessage("USER_"+username);
        chat = new Chat("MP_CLIENT", username);
        ///Same for chat as gC?
        this->setDisabled(true);
        gameController = new GameController("MP_CLIENT", username);
        connect(gameController, SIGNAL(closed()), this, SLOT(enable()));
        connect(gameController, SIGNAL(closed()), this, SLOT(deleteController()));
        //connect gameView
        connect(client, SIGNAL(receivedChatMessage(QString)), chat, SLOT(getMessage(QString)));
        connect(chat, SIGNAL(sendMessage(QString)), client, SLOT(sendMessage(QString)));
        connect(chat, SIGNAL(gameRequest()), client, SLOT(sendRequest()));
        connect(client, SIGNAL(gameAnswer(bool)), gameController, SLOT(initializeGameController(bool)));
        chat->show();
    }
    else
    {
        QMessageBox::information(0,"Error","Could not connect to server.");
    }
}

bool Hangman::getUsername()
{
    bool ok = false;
    username = QInputDialog::getText(this, tr("Who are you?"),
                                     tr("User name:"), QLineEdit::Normal,
                                     QDir::home().dirName(), &ok);
    if(ok && username.isEmpty())
    {
        ok = true;
    }
    return ok;
}

void Hangman::on_btnGoBack_clicked()
{
    ui->btnGoBack->hide();
    ui->btnSP_Easy->hide();
    ui->btnSP_Medium->hide();
    ui->btnSP_Hard->hide();
    ui->btnStartHost->hide();
    ui->btnFindHost->hide();
    ui->btnSingleplayer->show();
    ui->btnMultiplayer->show();
}

void Hangman::on_actionHighscore_triggered()
{
    this->setDisabled(true);
    highscore = new Highscore();
    highscore->setAttribute(Qt::WA_DeleteOnClose);
    connect(highscore, SIGNAL(destroyed(QObject*)), this, SLOT(enable()));
    connect(highscore, SIGNAL(closed()), this, SLOT(deleteHighscore()));
    highscore->show();
}

void Hangman::on_actionDictionary_triggered()
{
    this->setDisabled(true);
    dictionary = new Dictionary();
    dictionary->setAttribute(Qt::WA_DeleteOnClose);
    connect(dictionary, SIGNAL(destroyed(QObject*)), this, SLOT(enable()));
    connect(dictionary, SIGNAL(closed()), this, SLOT(deleteDict()));
    dictionary->show();
}

void Hangman::on_btnSP_Easy_clicked()
{
    this->setDisabled(true);
    gameController = new GameController("SP_EASY", username);
    connect(gameController, SIGNAL(closed()), this, SLOT(enable()));
    connect(gameController, SIGNAL(closed()), this, SLOT(deleteController()));
    gameController->initializeGameController(true);
}

void Hangman::on_btnSP_Medium_clicked()
{
    this->setDisabled(true);
    gameController = new GameController("SP_MEDIUM", username);
    connect(gameController, SIGNAL(closed()), this, SLOT(enable()));
    connect(gameController, SIGNAL(closed()), this, SLOT(deleteController()));
    gameController->initializeGameController(true);
}

void Hangman::on_btnSP_Hard_clicked()
{
    this->setDisabled(true);
    gameController = new GameController("SP_HARD", username);
    connect(gameController, SIGNAL(closed()), this, SLOT(enable()));
    connect(gameController, SIGNAL(closed()), this, SLOT(deleteController()));
    gameController->initializeGameController(true);
}

void Hangman::enable()
{
    this->setEnabled(true);
}

void Hangman::deleteController()
{
    delete gameController;
    gameController = NULL;
}

void Hangman::deleteHighscore()
{
    highscore = NULL;
}

void Hangman::deleteDict()
{
    dictionary = NULL;
}

void Hangman::deleteAbout()
{
    about = NULL;
}

void Hangman::closeEvent(QCloseEvent *)
{
    if(gameController) gameController->closeView();
    if(chat)
    {
        if(chat->isVisible()) chat->close();
    }
    if(highscore)
    {
        if(highscore->isVisible()) highscore->close();
    }
    if(dictionary)
    {
        if(dictionary->isVisible()) dictionary->close();
    }
    if(about)
    {
        if(about->isVisible()) about->close();
    }
}

void Hangman::on_actionAbout_triggered()
{
    this->setDisabled(true);
    about = new About();
    about->setAttribute(Qt::WA_DeleteOnClose);
    connect(about, SIGNAL(destroyed(QObject*)), this, SLOT(enable()));
    connect(about, SIGNAL(closed()), this, SLOT(deleteAbout()));
    about->show();
}
