#include "MysqlDao.h"
#include "MysqlPool.h"

using namespace std;
using namespace sql;
using PreparedStatementPtr = unique_ptr<PreparedStatement>;
using ResultSetPtr = unique_ptr<ResultSet>;

MysqlDao::MysqlDao()
{
	//TODO use configuration files to read settings
	pool_.reset(new MysqlPool("tcp://127.0.0.1/chat", "root", "123456", 3));
}

MysqlDao::~MysqlDao()
{
	pool_->close();
}

int MysqlDao::UserRegister(const std::string& name, const std::string& password, const std::string& email)
{
	auto con = pool_->GetConnection();
	if (!con) return -1;
	try
	{
		PreparedStatementPtr stm(con->prepareStatement("CALL UserRegister(?,?,?,@result)"));
		stm->setString(1, name);
		stm->setString(2, password);
		stm->setString(3, email);
		stm->execute();
		ResultSetPtr res(con->createStatement()->executeQuery("SELECT @result AS result"));
		if (res->next())
		{
			int result = res->getInt("result");
			//Debug
			cout << "result: " << result << endl;
			pool_->ReturnConnection(con);
			while (stm->getMoreResults()) {}
			stm->close();
			res->close();
			return result;
		}
		while (stm->getMoreResults()) {}
		stm->close();
		res->close();
		pool_->ReturnConnection(con);
		return -1;
	}
	catch (SQLException& e)
	{
		pool_->ReturnConnection(con);
		//TODO use logger to print
		cerr << "UserRegister SQLException: " << e.what() << " code: " << e.getErrorCode() << endl;
	}
	return -1;
}

bool MysqlDao::UserLogin(const std::string& name, const std::string& password, UserInfo& userInfo)
{
	auto con = pool_->GetConnection();
	if (!con) return false;
	try
	{
		PreparedStatementPtr stm(con->prepareStatement("SELECT * FROM user WHERE user_name = ?"));
		stm->setString(1, name);
		ResultSetPtr res(stm->executeQuery());
		string pwd;
		if (res->next())
		{
			pwd = res->getString("password");
		}
		if (pwd != password)
		{
			pool_->ReturnConnection(con);
			while (stm->getMoreResults()) {}
			stm->close();
			res->close();
			return false;
		}
		userInfo.uid = res->getInt("uid");
		userInfo.name = res->getString("user_name");
		userInfo.password = pwd;
		userInfo.email = res->getString("email");
		while (stm->getMoreResults()) {}
		stm->close();
		res->close();
		pool_->ReturnConnection(con);
		return true;
	}
	catch (SQLException& e)
	{
		pool_->ReturnConnection(con);
		//TODO use logger to print
		cerr << "UserLogin SQLException: " << e.what() << " code: " << e.getErrorCode() << endl;
		return false;
	}
}

vector<unordered_map<string, string>> MysqlDao::GetFriend(int uid)
{
	auto con = pool_->GetConnection();
	if (!con) return {};
	try
	{
		PreparedStatementPtr stm(con->prepareStatement("CALL GetFriend(?)"));
		stm->setInt(1, uid);
		shared_ptr<ResultSet> result(stm->executeQuery());
		vector<unordered_map<string, string>> res;
		while (result->next())
		{
			unordered_map<string, string> map;
			map.emplace("uid", result->getString("uid").asStdString());
			map.emplace("user_name", result->getString("user_name").asStdString());
			res.emplace_back(map);
		}
		while (stm->getMoreResults()){}
		stm->close();
		result->close();
		pool_->ReturnConnection(con);
		return res;
	}
	catch (SQLException& e)
	{
		pool_->ReturnConnection(con);
		//TODO use logger to print
		cerr << "GetFriend SQLException: " << e.what() << " code: " << e.getErrorCode() << endl;
		return {};
	}
}

int MysqlDao::AddFriend(const std::string& name, int uid)
{
	auto con = pool_->GetConnection();
	if (!con) return -1;
	try
	{
		PreparedStatementPtr stm(con->prepareStatement("CALL AddFriend(?,?,@result)"));
		stm->setString(1, name);
		stm->setInt(2, uid);
		stm->execute();
		ResultSetPtr res(con->createStatement()->executeQuery("SELECT @result AS result"));
		if (res->next())
		{
			int result = res->getInt("result");
			pool_->ReturnConnection(con);
			while (stm->getMoreResults()) {}
			stm->close();
			res->close();
			return result;
		}
		while (stm->getMoreResults()) {}
		stm->close();
		res->close();
		pool_->ReturnConnection(con);
		return -1;
	}
	catch (SQLException& e)
	{
		pool_->ReturnConnection(con);
		//TODO use logger to print
		cerr << "AddFriend SQLException: " << e.what() << " code: " << e.getErrorCode() << endl;
		return -1;
	}
}

bool MysqlDao::DelFriend(int user_id, int friend_id)
{
	auto con = pool_->GetConnection();
	if (!con) return false;
	try
	{
		PreparedStatementPtr stm(con->prepareStatement("DELETE FROM friend WHERE user_id = ? AND friend_id = ?"));
		stm->setInt(1, user_id);
		stm->setInt(2, friend_id);
		stm->executeUpdate();
		while (stm->getMoreResults()) {}
		stm->close();
		pool_->ReturnConnection(con);
		return true;
	}
	catch (SQLException& e)
	{
		pool_->ReturnConnection(con);
		//TODO use logger to print
		cerr << "DelFriend SQLException: " << e.what() << " code: " << e.getErrorCode() << endl;
		return false;
	}
}
