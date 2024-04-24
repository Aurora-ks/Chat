#include "MysqlDao.h"
#include "MysqlPool.h"

using namespace std;
using namespace sql;

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
		unique_ptr<PreparedStatement> stm(con->prepareStatement("CALL UserRegister(?,?,?,@result)"));
		stm->setString(1, name);
		stm->setString(2, password);
		stm->setString(3, email);
		stm->execute();

		unique_ptr<ResultSet> res(con->createStatement()->executeQuery("SELECT @result AS result"));
		if (res->next())
		{
			int result = res->getInt("result");
			//Debug
			cout << "result: " << result << endl;
			pool_->ReturnConnection(con);
			return result;
		}
		pool_->ReturnConnection(con);
		return -1;
	}
	catch (SQLException& e)
	{
		pool_->ReturnConnection(con);
		//TODO use log to print
		cerr << "SQLException: " << e.what() << " code: " << e.getErrorCode() << endl;
	}
	return -1;
}
