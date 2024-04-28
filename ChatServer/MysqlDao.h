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
	bool UserLogin();
private:
	MysqlDao();
	std::unique_ptr<MysqlPool> pool_;
};

