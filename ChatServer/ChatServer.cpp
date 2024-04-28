#include <iostream>
#include "CServer.h"

using namespace std;

int main()
{
	try {
		boost::asio::io_context ioc;
		boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
		signals.async_wait([&](boost::system::error_code ec, int signal){
			ioc.stop();
			exit(0);
			});
		CServer server(ioc, 9001);
		server.start();
		ioc.run();
	}
	catch (exception& e)
	{
		cout << "Exception: " << e.what() << endl;
	}
}
