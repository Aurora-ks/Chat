#pragma once
#include <memory>
#include <string>

class MysqlPool;

class MysqlDao
{
public:
	MysqlDao();
	~MysqlDao();
	int UserRegister(const std::string &name, const std::string &password, const std::string &email);
private:
	std::unique_ptr<MysqlPool> pool_;
};

