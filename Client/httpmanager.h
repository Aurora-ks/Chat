#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <memory>

enum RequestID{
    ID_GET_VARIFY_CODE = 1001, //获取验证码
    ID_USER_REG = 1002, //用户注册
};

enum ErrorCodes{
    SUCCESS = 0,
    ERR_JSON = 1, //Json解析失败
    ERR_NETWORK = 2, //网络错误
};

class HttpManager : public QObject, public std::enable_shared_from_this<HttpManager>
{
    Q_OBJECT
public:
    void PostRequest(QUrl url, QJsonObject& json, RequestID reqID);
    HttpManager(const HttpManager&) = delete;
    HttpManager& operator =(const HttpManager&) = delete;
    ~HttpManager() = default;
    static std::shared_ptr<HttpManager> GetInstance();
    static QString GetPrefix();
private:
    HttpManager();
    void SendFinished(RequestID id, QString res, ErrorCodes err);
    QNetworkAccessManager NetManager_;
    static std::shared_ptr<HttpManager> instance_;
    static QString urlPrefix;
signals:
    void RegFinished(RequestID id, QString res, ErrorCodes err);
};

#endif // HTTPMANAGER_H
