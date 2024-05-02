#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "logindialog.h"
#include "registerdialog.h"
#include "chatwindow.h"
#include "tcpmanager.h"
#include <QTimer>
#include <QJsonArray>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , loginDlg_(new LoginDialog())
    , registerDlg_(new RegisterDialog())
    , ChatWindow_(new ChatWindow())
{
    connect(loginDlg_, &LoginDialog::SwitchResister, this, &MainWindow::SwitchRegister);
    connect(registerDlg_, &RegisterDialog::SwitchLogin, this, &MainWindow::SwitchLogin);
    connect(loginDlg_, &LoginDialog::SwitchToMain, this, &MainWindow::OnLogin);
    connect(HttpManager::GetInstance().get(), &HttpManager::ChatSendFinished, this, &MainWindow::DoSendFinished);
    connect(this, &MainWindow::AddList, ChatWindow_, &ChatWindow::SwitchToLists);
    connect(&TcpManager::Instance(), &TcpManager::ReceivedMessage, this, &MainWindow::DoReceived);
    ui->setupUi(this);
    connect(ui->listWidget, &PersonList::OpenChatWindow, this, &MainWindow::DoOpenChatWindow);
    InitHandlers();
    //TODO decoupling login and registration
    if(loginDlg_->exec() != QDialog::Accepted) exit(0);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete loginDlg_;
    delete registerDlg_;
    delete ChatWindow_;
}

void MainWindow::InitHandlers()
{
    handlers_.insert(ID_USER_GET_PERSON_LIST, [this](QJsonObject jsonObj){
        int err = jsonObj["error"].toInt();
        if(err != ErrorCodes::SUCCESS) return;
        QJsonArray JsonArr = jsonObj["arr"].toArray();
        for(const QJsonValue& json : JsonArr){
            QString name = json["user_name"].toString();
            int uid = json["uid"].toString().toInt();
            ui->listWidget->AddPerson(name, uid, uid_);
        }
    });
    handlers_.insert(ID_ADD_PERSON, [this](QJsonObject jsonObj){
        int err = jsonObj["error"].toInt();
        if(err != ErrorCodes::SUCCESS){
            tip(tr("添加失败"));
            return;
        }
        QString name = jsonObj["user_name"].toString();
        int uid = jsonObj["uid"].toInt();
        ui->listWidget->AddPerson(name, uid, uid_);
    });
    handlers_.insert(ID_DEL_PERSON, [this](QJsonObject jsonObj){
        int err = jsonObj["error"].toInt();
        if(err != ErrorCodes::SUCCESS){
            QMessageBox::information(this, "删除好友", "删除失败!");
            return;
        }
        auto item = ui->listWidget->takeItem(ui->listWidget->currentRow());
        delete item;
    });
}

void MainWindow::tip(const QString &message)
{
    ui->tip->setText(message);
    QTimer::singleShot(2000, [this]{
        ui->tip->clear();
    });
}

void MainWindow::DoSendFinished(RequestID id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS)
    {
        QMessageBox::information(this, "Title", "操作失败！");
        return;
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if(jsonDoc.isNull() || !jsonDoc.isObject()){
        QMessageBox::information(this, "Title", "操作失败！");
        return;
    }
    handlers_[id](jsonDoc.object());
}

void MainWindow::DoReceived(RequestID id, QJsonObject data)
{
    if(id == ID_CHAT){
        int id_from = data["id_from"].toInt();
        QString msg = data["message"].toString();
        //查找id对应的item
        auto list = ui->listWidget;
        for(int i = 0; i < list->count(); ++i){
            auto item = list->item(i);
            int uid = item->data(Qt::UserRole).toInt();
            if(uid == id_from){
                ChatWindow_->ReceivedMessage(item, msg);
                return;
            }
        }
    }
}

void MainWindow::SwitchRegister()
{
    // setCentralWidget(registerDlg_);
    // loginDlg_->hide();
    registerDlg_->exec();
}

void MainWindow::SwitchLogin()
{
    // registerDlg_->close();
    // loginDlg_->show();
    registerDlg_->reject();
}

void MainWindow::OnLogin(QString name, int uid)
{
    name_ = name;
    uid_ = uid;
    ui->UserName->setText(name);
    QJsonObject json;
    json["uid"] = uid;
    HttpManager::GetInstance()->PostRequest(QUrl(HttpManager::GetPrefix()+"/get-friend"), json, RequestID::ID_USER_GET_PERSON_LIST);
}

void MainWindow::on_SearchButton_clicked()
{
    QString name = ui->SearchEdit->text();
    if(name.isEmpty()){
        tip(tr("用户名不能为空"));
        return;
    }
    QJsonObject json;
    json["user"] = name;
    json["uid"] = uid_;
    HttpManager::GetInstance()->PostRequest(QUrl(HttpManager::GetPrefix()+"/add-person"), json, RequestID::ID_ADD_PERSON);
}

void MainWindow::DoOpenChatWindow(QListWidgetItem *item)
{
    emit AddList(item);
    auto state = ChatWindow_->windowState();
    bool isMinimized = (state & Qt::WindowMinimized);
    if(isMinimized)
        ChatWindow_->showNormal();
    if(!ChatWindow_->isVisible())
        ChatWindow_->show();
    ChatWindow_->activateWindow();
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    ChatWindow_->close();
    QMainWindow::closeEvent(event);
}
