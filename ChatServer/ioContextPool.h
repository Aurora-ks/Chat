#pragma once
#include <boost/asio.hpp>
#include <vector>
#include <memory>
#include <thread>
#include "Singleton.ipp"

class ioContextPool : public Singleton<ioContextPool>
{
	friend class Singleton<ioContextPool>;
public:
	using ioContext = boost::asio::io_context;
	using Work = boost::asio::io_context::work;
	using WorkPtr = std::unique_ptr<Work>;

	//ioContextPool(int num = std::thread::hardware_concurrency());
	ioContextPool(int num = 2);
	~ioContextPool();

	ioContext& NextContext();

private:
	void stop();

	bool running_;
	std::vector<ioContext> ioContexts_;
	std::vector<WorkPtr> works_;
	std::vector<std::thread> threads_;
	int NextIO_;
};

