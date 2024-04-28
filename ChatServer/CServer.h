#pragma once
#include <boost/asio.hpp>
#include <map>
#include <mutex>
#include <memory>

using boost::asio::ip::tcp;
class Connection;

class CServer : public std::enable_shared_from_this<CServer>
{
public:
	CServer(boost::asio::io_context& ioc, unsigned int port);
	void start();
	void AddConnectionId(int id, std::string uuid);
	void RemoveConnetion(std::string uuid);
private:
	void HandleAccept(std::shared_ptr<Connection> con, const boost::system::error_code& error);
	boost::asio::io_context& ioc_;
	tcp::acceptor acceptor_;
	std::mutex mutex_;
	std::map<std::string, std::shared_ptr<Connection>> connections_;
	std::map<int, std::string> connectionsId_;
};

