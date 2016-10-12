#include "hangme.h"
#include "ui_hangme.h"

HangMe::HangMe(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HangMe)
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

HangMe::~HangMe()
{
    delete ui;
    if(server) delete server;
    if(client) delete client;
    if(chat) delete chat;
    if(gameController) delete gameController;
    if(dictionary) delete dictionary;
    if(highscore) delete highscore;
}

void HangMe::on_btnStartHost_clicked()
{
    server = new Server();
    chat = new Chat("MP_HOST", username);
    connect(server, SIGNAL(receivedChatMessage(QString)), chat, SLOT(getMessage(QString)));
    connect(server, SIGNAL(receivedRequestMessage(QString)), chat, SLOT(getRequestMessage(QString)));
    connect(chat, SIGNAL(sendMessage(QString)), server, SLOT(sendToAllClients(QString)));
    connect(chat, SIGNAL(closed()), this, SLOT(enable()));
    connect(server, SIGNAL(serverInfo(QString,QString)), chat, SLOT(newServerInfo(QString, QString)));
    if(server->startServer())
    {
        gameController = new GameController("MP_HOST", username);
        connect(server, SIGNAL(receivedGameMessage(QString)), gameController, SLOT(getGameMessage(QString)));
        connect(gameController, SIGNAL(closed()), this, SLOT(deleteController()));
        connect(chat, SIGNAL(closed()), gameController, SLOT(closeView()));
        connect(chat, SIGNAL(gameAnswer(bool)), gameController, SLOT(initializeGameController(bool)));
        connect(chat, SIGNAL(gameAnswer(bool)), server, SLOT(gameAccepted(bool)));
        this->setDisabled(true);
        chat->show();
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

void HangMe::on_btnFindHost_clicked()
{
    client = new Client();
    ConnectionSetup *connectionSetup = new ConnectionSetup();
    this->setDisabled(true);
    connect(connectionSetup, SIGNAL(closed()), this, SLOT(enable()));
    connect(connectionSetup, SIGNAL(connectClient(QString, int)), this, SLOT(connectClient(QString,int)));
    connect(client, SIGNAL(closed()), this, SLOT(enable()));
    connectionSetup->show();
}

void HangMe::on_btnSingleplayer_clicked()
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

void HangMe::on_btnMultiplayer_clicked()
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

void HangMe::connectClient(QString ipAdress, int port)
{
    if(client->connectClient(ipAdress, port))
    {
        client->sendMessage("USER_"+username);
        chat = new Chat("MP_CLIENT", username);
        this->setDisabled(true);
        gameController = new GameController("MP_CLIENT", username);
        connect(gameController, SIGNAL(closed()), this, SLOT(enable()));
        connect(gameController, SIGNAL(closed()), this, SLOT(deleteController()));
        connect(gameController, SIGNAL(closed()), client, SLOT(endGame()));
        connect(client, SIGNAL(receivedChatMessage(QString)), chat, SLOT(getMessage(QString)));
        connect(chat, SIGNAL(sendMessage(QString)), client, SLOT(sendMessage(QString)));
        connect(chat, SIGNAL(gameRequest()), client, SLOT(sendRequest()));
        connect(chat, SIGNAL(closed()), this, SLOT(enable()));
        connect(chat, SIGNAL(closed()), gameController, SLOT(closeView()));
        connect(client, SIGNAL(gameAnswer(bool)), gameController, SLOT(initializeGameController(bool)));
        connect(client, SIGNAL(gameAnswer(bool)), chat, SLOT(gameStarted(bool)));
        connect(client, SIGNAL(disconnect()), gameController, SLOT(closeView()));
        connect(client, SIGNAL(disconnect()), chat, SLOT(disconnect()));
        chat->show();
    }
}

bool HangMe::getUsername()
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

void HangMe::on_btnGoBack_clicked()
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

void HangMe::on_actionHighscore_triggered()
{
    this->setDisabled(true);
    highscore = new Highscore();
    highscore->setAttribute(Qt::WA_DeleteOnClose);
    connect(highscore, SIGNAL(destroyed(QObject*)), this, SLOT(enable()));
    connect(highscore, SIGNAL(closed()), this, SLOT(deleteHighscore()));
    highscore->show();
}

void HangMe::on_actionDictionary_triggered()
{
    this->setDisabled(true);
    dictionary = new Dictionary();
    dictionary->setAttribute(Qt::WA_DeleteOnClose);
    connect(dictionary, SIGNAL(destroyed(QObject*)), this, SLOT(enable()));
    connect(dictionary, SIGNAL(closed()), this, SLOT(deleteDict()));
    dictionary->show();
}

void HangMe::on_btnSP_Easy_clicked()
{
    this->setDisabled(true);
    gameController = new GameController("SP_EASY", username);
    connect(gameController, SIGNAL(closed()), this, SLOT(enable()));
    connect(gameController, SIGNAL(closed()), this, SLOT(deleteController()));
    gameController->initializeGameController(true);
}

void HangMe::on_btnSP_Medium_clicked()
{
    this->setDisabled(true);
    gameController = new GameController("SP_MEDIUM", username);
    connect(gameController, SIGNAL(closed()), this, SLOT(enable()));
    connect(gameController, SIGNAL(closed()), this, SLOT(deleteController()));
    gameController->initializeGameController(true);
}

void HangMe::on_btnSP_Hard_clicked()
{
    this->setDisabled(true);
    gameController = new GameController("SP_HARD", username);
    connect(gameController, SIGNAL(closed()), this, SLOT(enable()));
    connect(gameController, SIGNAL(closed()), this, SLOT(deleteController()));
    gameController->initializeGameController(true);
}

void HangMe::enable()
{
    this->setEnabled(true);
}

void HangMe::deleteController()
{
    delete gameController;
    gameController = NULL;
}

void HangMe::deleteHighscore()
{
    highscore = NULL;
}

void HangMe::deleteDict()
{
    dictionary = NULL;
}

void HangMe::deleteAbout()
{
    about = NULL;
}

void HangMe::closeEvent(QCloseEvent *)
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

void HangMe::on_actionAbout_triggered()
{
    this->setDisabled(true);
    about = new About();
    about->setAttribute(Qt::WA_DeleteOnClose);
    connect(about, SIGNAL(destroyed(QObject*)), this, SLOT(enable()));
    connect(about, SIGNAL(closed()), this, SLOT(deleteAbout()));
    about->show();
}
