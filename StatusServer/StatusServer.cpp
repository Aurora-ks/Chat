#include <iostream>
#include <memory>
#include <thread>
#include <boost/asio.hpp>
#include <grpcpp/grpcpp.h>
#include "StatusServerImpl.h"

int main()
{
	try
	{
		StatusServerImpl service;
		grpc::ServerBuilder builder;
		//TODO use config to load host
		builder.AddListeningPort("127.0.0.1:10087", grpc::InsecureServerCredentials());
		builder.RegisterService(&service);
		std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
		//Debug
		std::cout << "Running on 127.0.0.1:10087\n";

		boost::asio::io_context ioc;
		boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
		signals.async_wait([&server](boost::system::error_code ec, int signal) {
			server->Shutdown();
			});

		std::thread([&ioc] { ioc.run(); }).detach();
		server->Wait();
		ioc.stop();
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
		return -1;
	}
}
