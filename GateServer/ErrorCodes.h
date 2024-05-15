#pragma once
enum ErrorCodes
{
	SUCCESS = 0,
	JsonErr = 1001, //JSON解析错误
	RPCErr = 1002,	//RPC请求错误
	VerifyExpired = 1003, //验证码过期
	VerifyCodeErr = 1004, //验证码错误
	UserExist = 1005,       //用户已经存在
	UserNotExist = 1006, //用户不存在
	PasswordErr = 1007,    //密码错误
	EmailNotMatch = 1008,  //邮箱不匹配
	PasswordUpFailed = 1009,  //更新密码失败
	PasswordInvalid = 1010,   //密码更新失败
	RPCGetFailed = 1011,  //获取RPC请求失败
	SQLErr = 1012, //SQL错误
};