#pragma once
enum ErrorCodes
{
	SUCCESS = 0,
	JsonErr = 1001, //JSON解析错误
	RPCErr = 1002,	//RPC请求错误
	VarifyExpired = 1003, //验证码过期
	VarifyCodeErr = 1004, //验证码错误
	UserExist = 1005,       //用户已经存在
	PasswordErr = 1006,    //密码错误
	EmailNotMatch = 1007,  //邮箱不匹配
	PasswordUpFailed = 1008,  //更新密码失败
	PasswordInvalid = 1009,   //密码更新失败
	RPCGetFailed = 1010,  //获取RPC请求失败
};