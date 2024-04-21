#include "Connection.h"
#include "LogicSystem.h"

Connection::Connection(asio::io_context &ioc) :socket_(ioc)
{}

Connection::~Connection()
{
	std::cout << socket_.remote_endpoint().address().to_string() << " Close\n";
}

void Connection::start()
{
	auto self = shared_from_this();
	http::async_read(socket_, buffer_, request_, [self](beast::error_code ec, std::size_t bytes) {
		try {
			if (ec) {
				std::cout << self->socket_.remote_endpoint().address() << "Read: " << ec.message();
				return;
			}
			self->HandleRequest();
			self->CheckTime();
		}
		catch (std::exception& e) {
			std::cout << self->socket_.remote_endpoint().address() << "Read: " << e.what() << std::endl;
		}
		});
}

tcp::socket& Connection::socket()
{
	return socket_;
}

http::request<http::dynamic_body>& Connection::request()
{
	return request_;
}

http::response<http::dynamic_body>& Connection::response()
{
	return response_;
}

void Connection::HandleRequest()
{
	//���û�Ӧ�汾
	response_.version(request_.version());
	//����Ϊ������
	response_.set(http::field::connection, "close");
	//��������
	if (request_.method() == http::verb::get)
	{
		bool success = LogicSystem::Instance().GetHandle(request_.target(), shared_from_this());
		response_.set(http::field::server, "MyServer");
		if (!success)
		{
			response_.result(http::status::not_found);
			response_.set(http::field::content_type, "text/plain");
			beast::ostream(response_.body()) << "Resouce Not Found\r\n";
		}
		else
		{
			response_.result(http::status::ok);
		}
		SendResponse();
	}
	else if (request_.method() == http::verb::post)
	{
		bool success = LogicSystem::Instance().PostHandle(request_.target(), shared_from_this());
		response_.set(http::field::server, "MyServer");
		if (!success)
		{
			response_.result(http::status::not_found);
			response_.set(http::field::content_type, "text/plain");
			beast::ostream(response_.body()) << "Resouce Not Found\r\n";
		}
		else
		{
			response_.result(http::status::ok);
		}
		SendResponse();
	}
}

void Connection::CheckTime()
{
	auto self = shared_from_this();
	timer_.async_wait([self](boost::system::error_code ec) {
		if (!ec) {
			//�������ݳ�ʱ�������������ر�
			//�������������������رջ����closewait
			self->socket_.close(ec);
		}
		});
}

void Connection::SendResponse()
{
	auto self = shared_from_this();
	response_.content_length(response_.body().size());
	http::async_write(socket_, response_, [self](beast::error_code ec, std::size_t bytes) {
		self->socket_.shutdown(tcp::socket::shutdown_send, ec);
		self->timer_.cancel();
		});
}
