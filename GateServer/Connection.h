#pragma once
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = boost::beast::http;
using tcp = boost::asio::ip::tcp;

class Connection :public std::enable_shared_from_this<Connection>
{
public:
	Connection(asio::io_context &ioc);

	~Connection();
	void start();
	tcp::socket& socket();
	http::request<http::dynamic_body>& request();
	http::response<http::dynamic_body>& response();
private:
	void HandleRequest();
	void CheckTime();
	void SendResponse();
	tcp::socket socket_;
	beast::flat_buffer buffer_{ 4096 };
	http::request<http::dynamic_body> request_;
	http::response<http::dynamic_body> response_;
	asio::steady_timer timer_;
};

