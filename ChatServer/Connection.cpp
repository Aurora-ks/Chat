#include "Connection.h"
#include "CServer.h"
#include "LogicSystem.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <string.h>
#include <iostream>

using namespace std;
const int HEAD_LEN = 4;
const int HEAD_ID_LEN = 2;
const int HEAD_DATA_LEN = 2;

Connection::Connection(boost::asio::io_context& ioc, CServer* server)
	:socket_(ioc),
	UserId_(-1),
	data_{ 0 },
	server_(server),
	closed_(false),
	ParsedHeadr_(false),
	HeaderNode_(make_shared<MessageNode>(HEAD_LEN))
{
	boost::uuids::uuid uuid = boost::uuids::random_generator()();
	uuid_ = boost::uuids::to_string(uuid);
}

Connection::~Connection()
{
	cout << "Closed\n";
}

void Connection::start()
{
	boost::asio::async_read(socket_, boost::asio::buffer(data_, HEAD_LEN),
		bind(&Connection::HandlerReadHeader, this, placeholders::_1, placeholders::_2, shared_from_this()));
}

void Connection::close()
{
	socket_.close();
	closed_ = true;
}

tcp::socket& Connection::socket()
{
	return socket_;
}

string& Connection::uuid()
{
	return uuid_;
}

CServer* Connection::server()
{
	return server_;
}

void Connection::SetUserId(int id)
{
	UserId_ = id;
}

void Connection::send(const string& msg, unsigned short id)
{
	send(msg.c_str(), msg.size(), id);
}

void Connection::send(const char* msg, int len, unsigned short id)
{
	lock_guard<mutex> lock(mutex_);
	int size = queue_.size();
	queue_.emplace(make_shared<SendNode>(msg, len, id));
	if (size > 0) return;
	auto node = queue_.front();
	boost::asio::async_write(socket_, boost::asio::buffer(node->data_, node->length_),
		bind(&Connection::HandleWrite, this, placeholders::_1, shared_from_this()));

}

void Connection::HandleWrite(const boost::system::error_code& error, shared_ptr<Connection> shared_self)
{
	try
	{
		if (error)
		{
			cout << "Connection Write Error: " << error.what() << endl;
			close();
			server_->RemoveConnetion(UserId_, uuid_);
		}
		else
		{
			lock_guard<mutex> lock(mutex_);
			queue_.pop();
			if (!queue_.empty())
			{
				auto node = queue_.front();
				boost::asio::async_write(socket_, boost::asio::buffer(node->data_, node->length_),
					bind(&Connection::HandleWrite, this, placeholders::_1, shared_from_this()));
			}
		}
	}
	catch (exception& e)
	{
		cout << "Connection Write Exception: " << e.what() << endl;
	}
}

void Connection::HandlerReadBody(const boost::system::error_code& error, size_t bytes_transferred, shared_ptr<Connection> shared_self)
{
	if (error)
	{
		cout << "Connection ReadBody Error: " << error.what() << endl;
		close();
		server_->RemoveConnetion(UserId_, uuid_);
		return;
	}
	//ReceiveNode_->data_[ReceiveNode_->length_] = '\0';
	//cout << "Receive Body:" << endl;
	LogicSystem::Instance().post(make_shared<LogicNode>(shared_self, ReceiveNode_));
	boost::asio::async_read(socket_, boost::asio::buffer(data_, HEAD_LEN),
		bind(&Connection::HandlerReadHeader, this, placeholders::_1, placeholders::_2, shared_self));
}

void Connection::HandlerReadHeader(const boost::system::error_code& error, size_t  bytes_transferred, shared_ptr<Connection> shared_self)
{
	if (error)
	{
		cout << "Connection ReadHeader Error: " << error.what() << endl;
		close();
		server_->RemoveConnetion(UserId_, uuid_);
		return;
	}
	short id;
	short len;
	memcpy(&id, data_, HEAD_ID_LEN);
	memcpy(&len, data_+HEAD_ID_LEN, HEAD_DATA_LEN);
	id = boost::asio::detail::socket_ops::network_to_host_short(id);
	len = boost::asio::detail::socket_ops::network_to_host_short(len);
	cout << "Receive ID: " << id << " Len: " << len << endl;

	ReceiveNode_ = make_shared<ReceiveNode>(len, id);
	boost::asio::async_read(socket_, boost::asio::buffer(ReceiveNode_->data_, len),
		bind(&Connection::HandlerReadBody, this, placeholders::_1, placeholders::_2, shared_self));
}

LogicNode::LogicNode(shared_ptr<Connection> con, shared_ptr<ReceiveNode> msg)
	:connection_(con),
	ReceiveNode_(msg)
{
}
