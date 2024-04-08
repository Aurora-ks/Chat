#include "Server.h"
#include <iostream>
#include "Connection.h"

Server::Server(asio::io_context& ioc, unsigned int port) :acceptor_(ioc, tcp::endpoint(tcp::v4(), port)), socket_(ioc)
{
	std::cout << "Runing in " << acceptor_.local_endpoint() << std::endl;
}

void Server::start()
{
	auto self = shared_from_this();
	acceptor_.async_accept(socket_, [self](const boost::system::error_code &ec) {
		try {
			//如果出错，则放弃此连接
			if (ec) {
				std::cout << "Accept " << ec.message() << std::endl;
				self->start();
				return;
			}
			std::cout << "Accept " << self->socket_.remote_endpoint().address().to_string() << std::endl;
			std::make_shared<Connection>(std::move(self->socket_))->start();
			self->start();
		}
		catch (std::exception& e) {
			std::cout << "Accept Exception: " << e.what() << std::endl;
		}
		});
}