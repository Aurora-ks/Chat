#pragma once
#include <memory>
#include <string>
#include "Singleton.ipp"

class MysqlPool;

struct UserInfo
{
	int uid;
	std::string name;
	std::string password;
	std::string email;
};

class MysqlDao : public Singleton<MysqlDao>
{
	friend class Singleton<MysqlDao>;
public:
	~MysqlDao();
	int UserRegister(const std::string &name, const std::string &password, const std::string &email);
	bool UserLogin(const std::string& name, const std::string& password, UserInfo& userInfo);
private:
	MysqlDao();
	std::unique_ptr<MysqlPool> pool_;
};

