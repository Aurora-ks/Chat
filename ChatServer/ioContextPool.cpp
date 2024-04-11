#include "ioContextPool.h"

ioContextPool::ioContextPool(int num)
	:ioContexts_(num),
	works_(num),
	NextIO_(0)
{
	for (int i = 0; i < num; ++i)
	{
		works_[i] = std::unique_ptr<Work>(new Work(ioContexts_[i]));
	}

	for (int i = 0; i < num; ++i)
	{
		threads_.emplace_back([&]() {
			ioContexts_[i].run();
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
	if(NextIO_ == ioContexts_.size()) NextIO_ = 0;
	return context;
}

void ioContextPool::stop()
{
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