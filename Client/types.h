#ifndef TYPES_H
#define TYPES_H
#include <QString>

enum RequestID{
    ID_GET_VARIFY_CODE = 1001, //获取验证码
    ID_USER_REG = 1002, //用户注册
    ID_USER_RESETPWD = 1003, //重置密码
    ID_USER_LOGIN = 1004, //用户登录
    ID_USER_GET_PERSON_LIST = 1005, //获取好友列表
    ID_ADD_PERSON = 1006, //添加好友
    ID_DEL_PERSON = 1007, //删除好友
    ID_CHAT = 2000 //消息通信
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
