#include "logindialog.h"
#include "ui_logindialog.h"
#include "httpmanager.h"
#include "tcpmanager.h"

//TODO add change password

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog),
    uid_(0),
{
    ui->setupUi(this);
    connect(ui->RegisterButton, &QPushButton::clicked, this, &LoginDialog::SwitchResister);
    connect(HttpManager::GetInstance().get(), &HttpManager::LoginFinished, this, &LoginDialog::DoLoginFinished);
    connect(this, &LoginDialog::ConnectToTcp, &TcpManager::Instance(), &TcpManager::OnConnect);
    connect(&TcpManager::Instance(), &TcpManager::connected, this, &LoginDialog::DoConnected);
    InitHandlers();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::InitHandlers()
{
    handlers_.insert(RequestID::ID_USER_LOGIN, [this](QJsonObject jsonObj){
        int err = jsonObj["error"].toInt();
        if(err != ErrorCodes::SUCCESS)
        {
            ShowState(tr("数据错误"));
            return;
        }
        ServerInfo s;
        s.host = jsonObj["host"].toString();
        s.port = jsonObj["port"].toString();
        s.token = jsonObj["token"].toString();
        s.uid = jsonObj["uid"].toInt();

        uid_ = s.uid;
        token_ = s.token;

        TcpManager::Instance().OnConnect(s);
        // emit ConnectToTcp(s);
        // Debug
        // ShowState("登录成功");
        // qDebug() << jsonObj["user"].toString();
    });
}

void LoginDialog::ShowState(const QString &msg)
{
    ui->stateLable->setText(msg);
}

void LoginDialog::DoLoginFinished(RequestID id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS)
    {
        ShowState("网络错误");
        return;
    }
    // 解析 JSON 字符串,res需转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if(jsonDoc.isNull() || !jsonDoc.isObject()){
        ShowState("json解析错误");
        return;
    }
    handlers_[id](jsonDoc.object());
}

void LoginDialog::DoConnected(bool success)
{
    if(success)
    {
        QJsonObject json;
        json["uid"] = uid_;
        json["token"] = token_;

        QJsonDocument doc(json);
        QString data = doc.toJson();
        TcpManager::Instance().SendData(RequestID::ID_USER_LOGIN, data);
    }
    else
    {
        ShowState(tr("登录失败"));
    }
}

void LoginDialog::on_showPwd_toggled(bool checked)
{
    if(checked) ui->passwordEdit->setEchoMode(QLineEdit::Normal);
    else ui->passwordEdit->setEchoMode(QLineEdit::Password);
}

void LoginDialog::on_LoginButton_clicked()
{
    QString usr = ui->userEdit->text();
    QString password = ui->passwordEdit->text();
    if(usr.isEmpty() || password.isEmpty())
    {
        ShowState(tr("用户名或密码为空"));
        return;
    }

    QJsonObject json;
    json["user"] = usr;
    json["password"] = password;
    HttpManager::GetInstance()->PostRequest(QUrl(HttpManager::GetPrefix()+"/login"),
                                            json, RequestID::ID_USER_LOGIN);
}

