#pragma once
#include <memory>
#include <map>
#include <functional>
#include <string>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include "Singleton.ipp"

class Connection;


class LogicSystem : public Singleton<LogicSystem>
{
	friend class Singleton<LogicSystem>;
public:
	using ConnectionPtr = std::shared_ptr<Connection>;
	using HttpHandle = std::function<void(ConnectionPtr)>;
	LogicSystem();
	~LogicSystem() = default;
	void RegiserGetHandle(std::string url, HttpHandle handle); //ע��get��Ӧ�Ĵ�����
	void RegiserPostHandle(std::string url, HttpHandle handle); //ע��post��Ӧ�Ĵ�����
	bool GetHandle(std::string str, ConnectionPtr connection); //GET���ö�Ӧ�Ĵ�����
	bool PostHandle(std::string str, ConnectionPtr connection); //POST���ö�Ӧ�Ĵ�����
private:
	std::map<std::string, HttpHandle> GetHandles_; //get������url
	std::map<std::string, HttpHandle> PostHandles_; //post������json
};