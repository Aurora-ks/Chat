#include "Server.h"
#include <iostream>
#include "message.pb.h"

int main()
{
	try {
		unsigned short port = 9000;
		asio::io_context ioc;
		asio::signal_set signals(ioc, SIGINT, SIGTERM);
		signals.async_wait([&ioc](boost::system::error_code ec, int signal) {
			ioc.stop();
			});
		std::make_shared<Server>(ioc, port)->start();
		ioc.run();
	}
	catch (std::exception& e) {
		std::cout << "Main Exception:" << e.what() << std::endl;
	}
}
