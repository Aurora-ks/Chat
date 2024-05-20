#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QUrl>
#include <QSettings>
#include <QTimer>

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    connect(ui->CancelButton, &QPushButton::clicked, this, &RegisterDialog::SwitchLogin);
    connect(HttpManager::GetInstance().get(), &HttpManager::RegFinished, this, &RegisterDialog::DoRegFinished);
    InitHandlers();
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::ShowState(QString str)
{
    ui->StateLable->setText(str);
}

void RegisterDialog::InitHandlers()
{
    //获取验证码回调
    handlers_.insert(RequestID::ID_GET_VARIFY_CODE, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            ShowState(tr("数据错误"));
            return;
        }
        ShowState(tr("验证码发送成功"));
    });

    //注册用户回调
    handlers_.insert(RequestID::ID_USER_REG, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            ShowState(tr("注册失败"));
            return;
        }
        auto email = jsonObj["email"].toString();
        qDebug() << "email: " << email;
        ShowState(tr("注册成功, 3s后自动返回登录界面"));
        QTimer *timer = new QTimer(this);
        QObject::connect(timer, &QTimer::timeout, this, [this, timer]{
            timer->stop();
            this->accept();
        });
        timer->start(3000);
    });
}

void RegisterDialog::DoRegFinished(RequestID id, QString res, ErrorCodes err)
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
    //根据id调用对应的逻辑
    handlers_[id](jsonDoc.object());
}

void RegisterDialog::on_GetCodeBtn_clicked()
{
    QString email = ui->EmailEdit->text();
    QRegularExpression regular("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    //验证邮箱格式是否正确
    if(regular.match(email).hasMatch())
    {
        //发送验证码
        QJsonObject jsonObj;
        jsonObj["email"] = email;
        HttpManager::GetInstance()->PostRequest(QUrl(HttpManager::GetPrefix()+"/verify"),
                                                jsonObj, RequestID::ID_GET_VARIFY_CODE);
    }
    else
    {
        ShowState("邮箱不正确");
    }
}


void RegisterDialog::on_RegisterButton_clicked()
{
    //TODO use "QLineEdit::editingFinished" signal to check
    if(ui->usrNameEdit->text() == ""){
        ShowState(tr("用户名不能为空"));
        return;
    }

    if(ui->EmailEdit->text() == ""){
        ShowState(tr("邮箱不能为空"));
        return;
    }

    if(ui->PwdEdit->text() == ""){
        ShowState(tr("密码不能为空"));
        return;
    }

    if(ui->Pwd1Edit->text() == ""){
        ShowState(tr("确认密码不能为空"));
        return;
    }

    if(ui->PwdEdit->text() != ui->Pwd1Edit->text()){
        ShowState(tr("密码和确认密码不匹配"));
        return;
    }

    if(ui->CodeEdit->text() == ""){
        ShowState(tr("验证码不能为空"));
        return;
    }

    //发送http请求注册用户
    QJsonObject registerJson;
    registerJson["user"] = ui->usrNameEdit->text();
    registerJson["email"] = ui->EmailEdit->text();
    registerJson["password"] = ui->PwdEdit->text();
    registerJson["confirm"] = ui->Pwd1Edit->text();
    registerJson["verifycode"] = ui->CodeEdit->text();
    HttpManager::GetInstance()->PostRequest(QUrl(HttpManager::GetPrefix()+"/register"),
                                            registerJson, RequestID::ID_USER_REG);
}


void RegisterDialog::on_showPwd_toggled(bool checked)
{
    if(checked)
        ui->PwdEdit->setEchoMode(QLineEdit::Normal);
    else
        ui->PwdEdit->setEchoMode(QLineEdit::Password);
}


void RegisterDialog::on_showPwd1_toggled(bool checked)
{
    if(checked)
        ui->Pwd1Edit->setEchoMode(QLineEdit::Normal);
    else
        ui->Pwd1Edit->setEchoMode(QLineEdit::Password);
}

