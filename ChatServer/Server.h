#pragma once
#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = boost::beast::http;
using tcp = boost::asio::ip::tcp;

class Server :public std::enable_shared_from_this<Server>
{
public:
	Server(asio::io_context& ioc, unsigned int port);
	void start();
private:
	tcp::acceptor acceptor_;
	tcp::socket socket_;
};

