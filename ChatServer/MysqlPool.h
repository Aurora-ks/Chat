#pragma once
#include <string>
#include <deque>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <mysql/jdbc.h>

class MysqlPool
{
public:
	using connection = std::unique_ptr<sql::Connection>;

	MysqlPool(const std::string& url, const std::string& usr, const std::string& password, int size);
	~MysqlPool();

	connection GetConnection();
	void ReturnConnection(connection &con);
	void close();
private:
	int size_;
	std::deque<std::unique_ptr<sql::Connection>> pool_;
	std::mutex mutex_;
	std::condition_variable cond_;
	std::atomic_bool running_;
};

