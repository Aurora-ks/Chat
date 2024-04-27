#include "MessageNode.h"
#include <string.h>
#include <boost/asio.hpp>

MessageNode::MessageNode(int len)
	:data_(new char[len+1]),
	CurentIndex_(0),
	length_(len)
{
	data_[len] = '\0';
}

MessageNode::~MessageNode()
{
	delete[] data_;
}

void MessageNode::clear()
{
	CurentIndex_ = 0;
	memset(data_, 0, sizeof(data_));
}

ReceiveNode::ReceiveNode(int len, int id)
	:MessageNode(len),
	id_(id)
{
}

SendNode::SendNode(const char* data, int len, int id)
	:MessageNode(len),
	id_(id)
{
	//TODO replace magic number
	unsigned short HostOrderId = boost::asio::detail::socket_ops::host_to_network_short(id);
	memcpy(data_, &HostOrderId, 2);
	unsigned short HostOrderLen = boost::asio::detail::socket_ops::host_to_network_short(len);
	memcpy(data_ + 2, &HostOrderLen, 2);
	memcpy(data_ + 4, data, len);
}
