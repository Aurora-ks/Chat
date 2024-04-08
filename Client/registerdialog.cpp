#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QUrl>
#include <QSettings>

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    connect(HttpManager::GetInstance().get(), &HttpManager::RegFinished, this, &RegisterDialog::DoRegFinished);

}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::ShowState(QString str)
{
    ui->StateLable->setText(str);
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
    // QJsonObject jsonObj = jsonDoc.object();
    // Do Something...
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
        HttpManager::GetInstance()->PostRequest(QUrl(HttpManager::GetPrefix()+"/varify"), jsonObj, RequestID::ID_GET_VARIFY_CODE);
        ShowState("发送成功");
    }
    else
    {
        ShowState("邮箱不正确");
    }
}

