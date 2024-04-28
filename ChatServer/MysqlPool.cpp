#include "MysqlPool.h"

using namespace std;
using namespace sql;

MysqlPool::MysqlPool(const std::string& url, const std::string& usr, const std::string& password, int size)
	:size_(size),
	running_(true)
{
	Driver* drive = get_driver_instance();
	try
	{
		for (int i = 0; i < size; ++i)
		{
			connection con(drive->connect(url, usr, password));
			if (!con->isValid())
			{
				//TODO use log to print
				cerr << "MysqlPool Create Failed\n";
				exit(0);
			}
			pool_.push_back(move(con));
		}
	}
	//TODO use log to print
	catch (SQLException& e)
	{
		cerr << "MysqlPool Create Exception\n";
	}
}

MysqlPool::~MysqlPool()
{
	lock_guard<mutex> lock(mutex_);
	pool_.clear();
}

MysqlPool::connection MysqlPool::GetConnection()
{
	unique_lock<mutex> lock(mutex_);
	cond_.wait(lock, [this] {
		return !pool_.empty() || !running_;
		});
	if (!running_) return nullptr;
	connection con(move(pool_.front()));
	pool_.pop_front();
	return con;
}

void MysqlPool::ReturnConnection(connection& con)
{
	unique_lock<mutex> lock(mutex_);
	if (!running_) return;
	pool_.push_back(move(con));
	cond_.notify_one();
}

void MysqlPool::close()
{
	running_ = false;
	cond_.notify_all();
}
