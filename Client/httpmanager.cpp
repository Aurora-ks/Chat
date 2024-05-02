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
    QNetworkAccessManager *NetManager = new QNetworkAccessManager();
    QNetworkReply* reply = NetManager->post(request, data);
    connect(reply, &QNetworkReply::finished, this, [NetManager, reply, reqID, self](){
        //处理错误
        if(reply->error() != QNetworkReply::NoError)
        {
            self->SendFinished(reqID, "", ErrorCodes::ERR_NETWORK);
            reply->deleteLater();
            NetManager->deleteLater();
            return;
        }
        //读出请求
        QString res = reply->readAll();
        self->SendFinished(reqID, res, ErrorCodes::SUCCESS);
        reply->deleteLater();
        NetManager->deleteLater();
    });
}

void HttpManager::GetRequest(QUrl url, RequestID reqID)
{
    QNetworkRequest request(url);
    auto self = shared_from_this();
    QNetworkAccessManager *NetManager = new QNetworkAccessManager();
    QNetworkReply* reply = NetManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [NetManager, reply, reqID, self](){
        //处理错误
        if(reply->error() != QNetworkReply::NoError)
        {
            self->SendFinished(reqID, "", ErrorCodes::ERR_NETWORK);
            reply->deleteLater();
            NetManager->deleteLater();
            return;
        }
        //读出请求
        QString res = reply->readAll();
        self->SendFinished(reqID, res, ErrorCodes::SUCCESS);
        reply->deleteLater();
        NetManager->deleteLater();
    });
}

void HttpManager::SendFinished(RequestID id, QString res, ErrorCodes err)
{
    switch (id) {
    case ID_USER_REG:
    case ID_GET_VARIFY_CODE:
        emit RegFinished(id, res, err);
        break;
    case ID_USER_LOGIN:
        emit LoginFinished(id, res, err);
        break;
    case ID_USER_GET_PERSON_LIST:
    case ID_ADD_PERSON:
    case ID_DEL_PERSON:
        emit ChatSendFinished(id, res, err);
        break;
    default:
        break;
    }
}
