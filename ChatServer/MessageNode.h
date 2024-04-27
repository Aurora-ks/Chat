#pragma once
class LogicSystem;
class Connection;

class MessageNode
{
	friend class Connection;
public:
	MessageNode(int len);
	~MessageNode();
	void clear();
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