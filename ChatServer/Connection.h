#pragma once
#include <boost/asio.hpp>
#include <queue>
#include <mutex>
#include "MessageNode.h"

using boost::asio::ip::tcp;
class CServer;
class LogicSystem;

class Connection : public std::enable_shared_from_this<Connection>
{
public:
	Connection(boost::asio::io_context& ioc, CServer *server);
	void start();
	void close();

	tcp::socket& socket();
	std::string& uuid();
	CServer* server();

	void AsyncReadHeader(int len);
	void AsyncReadBody(int len);
	void send(const std::string& msg, unsigned short id);
	void send(const char* msg, int len, unsigned short id);
private:
	void AsyncReadAll(int len, std::function<void(const boost::system::error_code&, size_t)> handler);
	void AsyncRead(size_t HasRead, size_t len, std::function<void(const boost::system::error_code&, size_t)> handler);
	void HandleWrite(const boost::system::error_code& error, std::shared_ptr<Connection> shared_self);

	enum { MAX_LEN = 2048 };
	tcp::socket socket_;
	std::string uuid_;
	char data_[MAX_LEN];
	CServer *server_;
	bool closed_;
	bool ParsedHeadr_;
	std::shared_ptr<MessageNode> HeaderNode_;
	std::shared_ptr<ReceiveNode> ReceiveNode_;
	std::queue<std::shared_ptr<SendNode>> queue_;
	std::mutex mutex_;
};

class LogicNode
{
	friend class LogicSystem;
public:
	LogicNode(std::shared_ptr<Connection> con, std::shared_ptr<ReceiveNode> msg);
private:
	std::shared_ptr<Connection> connection_;
	std::shared_ptr<ReceiveNode> ReceiveNode_;
};