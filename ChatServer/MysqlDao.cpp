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

bool MysqlDao::UserLogin()
{

	return false;
}

//int MysqlDao::UserRegister(const std::string& name, const std::string& password, const std::string& email)
//{
//	auto con = pool_->GetConnection();
//	if (!con) return -1;
//	try
//	{
//		PreparedStatementPtr stm(con->prepareStatement("CALL UserRegister(?,?,?,@result)"));
//		stm->setString(1, name);
//		stm->setString(2, password);
//		stm->setString(3, email);
//		stm->execute();
//
//		ResultSetPtr res(con->createStatement()->executeQuery("SELECT @result AS result"));
//		if (res->next())
//		{
//			int result = res->getInt("result");
//			//Debug
//			cout << "result: " << result << endl;
//			pool_->ReturnConnection(con);
//			return result;
//		}
//		pool_->ReturnConnection(con);
//		return -1;
//	}
//	catch (SQLException& e)
//	{
//		pool_->ReturnConnection(con);
//		//TODO use log to print
//		cerr << "SQLException: " << e.what() << " code: " << e.getErrorCode() << endl;
//	}
//	return -1;
//}
//
//bool MysqlDao::UserLogin(const std::string& name, const std::string& password, UserInfo& userInfo)
//{
//	auto con = pool_->GetConnection();
//	if (!con) return false;
//	try
//	{
//		PreparedStatementPtr stm(con->prepareStatement("SELECT * FROM user WHERE user = ?"));
//		stm->setString(1, name);
//
//		ResultSetPtr res(stm->executeQuery());
//		string pwd;
//		if (res->next())
//		{
//			pwd = res->getString("password");
//		}
//		if (pwd != password) return false;
//
//		userInfo.uid = res->getInt("uid");
//		userInfo.name = res->getString("user");
//		userInfo.password = pwd;
//		userInfo.email = res->getString("email");
//		return true;
//	}
//	catch (SQLException& e)
//	{
//		pool_->ReturnConnection(con);
//		//TODO use log to print
//		cerr << "SQLException: " << e.what() << " code: " << e.getErrorCode() << endl;
//		return false;
//	}
//}
