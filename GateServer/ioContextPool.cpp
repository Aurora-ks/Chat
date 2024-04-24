#include "ioContextPool.h"
#include <iostream>
ioContextPool::ioContextPool(int num)
	:ioContexts_(num),
	works_(num),
	NextIO_(0),
	running_(true)
{
	for (int i = 0; i < num; ++i)
	{
		works_.emplace_back(WorkPtr(new Work(ioContexts_.at(i))));
	}
	for (int i = 0; i < num; ++i)
	{
		threads_.emplace_back([this, i]() {
			ioContexts_.at(i).run();
			});
	}
}

ioContextPool::~ioContextPool()
{
	stop();
}

boost::asio::io_context& ioContextPool::NextContext()
{
	auto& context = ioContexts_[NextIO_++];
	if (NextIO_ == ioContexts_.size()) NextIO_ = 0;
	return context;
}

void ioContextPool::stop()
{
	if (running_)
	{
		running_ = false;
		for (auto& work : works_)
		{
			work->get_io_context().stop();
			work.reset();
		}
		for (auto& t : threads_)
		{
			t.join();
		}
	}
}