#include "httpmanager.h"
#include <mutex>
#include <QSettings>
std::shared_ptr<HttpManager> HttpManager::instance_ = nullptr;
QString HttpManager::urlPrefix = "";

std::shared_ptr<HttpManager> HttpManager::GetInstance()
{
    static std::once_flag flag;
    std::call_once(flag, [&](){ instance_ = std::shared_ptr<HttpManager>(new HttpManager);});
    return instance_;
}

QString HttpManager::GetPrefix()
{
    return urlPrefix;
}

HttpManager::HttpManager()
{
    QSettings settings(":/config.ini", QSettings::IniFormat);
    QString host = settings.value("server/host").toString();
    QString port = settings.value("server/port").toString();
    urlPrefix = "http://" + host + ":" + port;
}

void HttpManager::PostRequest(QUrl url, QJsonObject &json, RequestID reqID)
{
    //创建一个HTTP POST请求，并设置请求头和请求体
    QByteArray data = QJsonDocument(json).toJson();
    //通过url构建请求
    QNetworkRequest request(url);
    //设置头部信息
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));
    //发送请求
    auto self = shared_from_this();
    QNetworkReply* reply = NetManager_.post(request, data);
    connect(reply, &QNetworkReply::finished, this, [reply, reqID, self](){
        //处理错误
        if(reply->error() != QNetworkReply::NoError)
        {
            qDebug() << reply->errorString();
            self->SendFinished(reqID, "", ErrorCodes::ERR_NETWORK);
            reply->deleteLater();
            return;
        }
        //读出请求
        QString res = reply->readAll();
        self->SendFinished(reqID, res, ErrorCodes::SUCCESS);
        reply->deleteLater();
    });
}

void HttpManager::SendFinished(RequestID id, QString res, ErrorCodes err)
{
    if(id == RequestID::ID_USER_REG | id == RequestID::ID_GET_VARIFY_CODE)
    {
        emit RegFinished(id, res, err);
    }
}
