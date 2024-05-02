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
	void RegiserGetHandle(std::string url, HttpHandle handle); //注册get对应的处理函数
	void RegiserPostHandle(std::string url, HttpHandle handle); //注册post对应的处理函数
	bool GetHandle(std::string str, ConnectionPtr connection); //GET调用对应的处理函数
	bool PostHandle(std::string str, ConnectionPtr connection); //POST调用对应的处理函数
private:
	std::map<std::string, HttpHandle> GetHandles_; //get请求处理url
	std::map<std::string, HttpHandle> PostHandles_; //post请求处理json
};