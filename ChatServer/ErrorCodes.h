#pragma once
enum ErrorCodes
{
	SUCCESS = 0,
	JsonErr = 1001, //JSON��������
	RPCErr = 1002,	//RPC�������
	VarifyExpired = 1003, //��֤�����
	VarifyCodeErr = 1004, //��֤�����
	UserExist = 1005,       //�û��Ѿ�����
	PasswordErr = 1006,    //�������
	EmailNotMatch = 1007,  //���䲻ƥ��
	PasswordUpFailed = 1008,  //��������ʧ��
	PasswordInvalid = 1009,   //�������ʧ��
	RPCGetFailed = 1010,  //��ȡRPC����ʧ��
};