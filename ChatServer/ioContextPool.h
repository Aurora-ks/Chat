#pragma once
#include <boost/asio.hpp>
#include <vector>
#include <memory>
#include <thread>
#include "Singleton.ipp"

class ioContextPool : public Singlenton<ioContextPool>
{
public:
	using ioContext = boost::asio::io_context;
	using Work = boost::asio::io_context::work;
	using WorkPtr = std::unique_ptr<Work>;

	~ioContextPool();

	ioContext& NextContext();
private:
	ioContextPool(int num);
	void stop();

	std::vector<ioContext> ioContexts_;
	std::vector<WorkPtr> works_;
	std::vector<std::thread> threads_;
	int NextIO_;
};

