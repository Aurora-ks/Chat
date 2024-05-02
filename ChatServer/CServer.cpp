#include <iostream>
#include "CServer.h"
#include "ioContextPool.h"
#include "Connection.h"

using namespace std;

CServer::CServer(boost::asio::io_context& ioc, unsigned int port)
	:ioc_(ioc),
	acceptor_(ioc, tcp::endpoint(tcp::v4(), port))
{
	cout << "Runing on " << acceptor_.local_endpoint() << endl;
}

void CServer::start()
{
	auto& ioc = ioContextPool::Instance().NextContext();
	shared_ptr<Connection> con(make_shared<Connection>(ioc, this));
	acceptor_.async_accept(con->socket(), bind(&CServer::HandleAccept, this, con, placeholders::_1));
}

void CServer::AddConnectionId(int id, std::string uuid)
{
	lock_guard<mutex> lock(mutex_);
	connectionsId_.emplace(id, uuid);
}

void CServer::RemoveConnetion(int id, std::string uuid)
{
	lock_guard<mutex> lock(mutex_);
	connections_.erase(uuid);
	connectionsId_.erase(id);
}

void CServer::HandleAccept(shared_ptr<Connection> con, const boost::system::error_code& error)
{
	if (error)
	{
		cout << "Connection Accept Error: " << error.what() << endl;
	}
	else
	{
		con->start();
		lock_guard<mutex> lock(mutex_);
		connections_.emplace(con->uuid(), con);
	}
	start();
}
