#include "Server.h"
#include <iostream>
#include "Connection.h"
#include "ioContextPool.h"

Server::Server(asio::io_context& ioc, unsigned int port)
	:ioc_(ioc),
	acceptor_(ioc, tcp::endpoint(tcp::v4(), port))
{
	std::cout << "Runing in " << acceptor_.local_endpoint() << std::endl;
}

void Server::start()
{
	auto self = shared_from_this();
	asio::io_context &NextContext = ioContextPool::Instance().NextContext();
	std::shared_ptr<Connection> NewConnection = std::make_shared<Connection>(NextContext);
	acceptor_.async_accept(NewConnection->socket(), [self, NewConnection](const boost::system::error_code& ec) {
		try {
			//如果出错，则放弃此连接
			if (ec) {
				std::cout << "Accept Error: " << ec.message() << std::endl;
				self->start();
				return;
			}
			std::cout << "Accept " << NewConnection->socket().remote_endpoint().address().to_string() << ":" << NewConnection->socket().remote_endpoint().port() << std::endl;
			NewConnection->start();
			self->start();
		}
		catch (std::exception& e) {
			std::cout << "Accept Exception: " << e.what() << std::endl;
		}
		});
}