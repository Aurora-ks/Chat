#pragma once
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = boost::beast::http;
using tcp = boost::asio::ip::tcp;

class LogicSystem;
class Connection :public std::enable_shared_from_this<Connection>
{
	friend class LogicSystem;
public:
	Connection(tcp::socket socket);
	~Connection();
	void start();
private:
	void HandleRequest();
	void CheckTime();
	void SendResponse();
	tcp::socket socket_;
	beast::flat_buffer buffer_{ 4096 };
	http::request<http::dynamic_body> request_;
	http::response<http::dynamic_body> response_;
	asio::steady_timer timer_{ socket_.get_executor(), std::chrono::seconds(30) };
};
