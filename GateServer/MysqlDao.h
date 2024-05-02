#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
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
	std::vector<std::unordered_map<std::string, std::string>> GetFriend(int uid);
	int AddFriend(const std::string& name, int uid);
	bool DelFriend(int user_id, int friend_id);
private:
	MysqlDao();
	std::unique_ptr<MysqlPool> pool_;
};

