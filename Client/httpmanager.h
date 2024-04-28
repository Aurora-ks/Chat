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
#include "types.h"

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
    void LoginFinished(RequestID id, QString res, ErrorCodes err);
};

#endif // HTTPMANAGER_H
