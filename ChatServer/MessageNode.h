#pragma once
#include <string>

class LogicSystem;
class Connection;

class MessageNode
{
	friend class Connection;
	friend class LogicSystem;
public:
	MessageNode(int len);
	virtual ~MessageNode();
	void clear();
	std::string DataToString() const;
protected:
	char* data_;
	int CurentIndex_;
	int length_;
};

class ReceiveNode : public MessageNode
{
	friend class LogicSystem;
public:
	ReceiveNode(int len, int id);
private:
	int id_;
};

class SendNode : public MessageNode
{
	friend class LogicSystem;
public:
	SendNode(const char* data, int len, int id);
private:
	int id_;
};

enum MessageID
{
	LOGIN_CHAT = 1004,
	CHAT = 2000
};