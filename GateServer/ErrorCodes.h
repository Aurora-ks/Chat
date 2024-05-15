#pragma once
enum ErrorCodes
{
	SUCCESS = 0,
	JsonErr = 1001, //JSON��������
	RPCErr = 1002,	//RPC�������
	VerifyExpired = 1003, //��֤�����
	VerifyCodeErr = 1004, //��֤�����
	UserExist = 1005,       //�û��Ѿ�����
	UserNotExist = 1006, //�û�������
	PasswordErr = 1007,    //�������
	EmailNotMatch = 1008,  //���䲻ƥ��
	PasswordUpFailed = 1009,  //��������ʧ��
	PasswordInvalid = 1010,   //�������ʧ��
	RPCGetFailed = 1011,  //��ȡRPC����ʧ��
	SQLErr = 1012, //SQL����
};