#ifndef TYPES_H
#define TYPES_H
#include <QString>

enum RequestID{
    ID_GET_VARIFY_CODE = 1001, //获取验证码
    ID_USER_REG = 1002, //用户注册
    ID_USER_LOGIN = 1003, //用户登录
};

enum ErrorCodes{
    SUCCESS = 0,
    ERR_JSON = 1, //Json解析失败
    ERR_NETWORK = 2, //网络错误
};

struct ServerInfo
{
    QString host;
    QString port;
    QString token;
    int uid;
};

#endif // TYPES_H
