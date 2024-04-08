#pragma once
#include <memory>
#include <map>
#include <functional>
#include <string>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

class Connection;
using HttpHandle = std::function<void(std::shared_ptr<Connection>)>;

class LogicSystem
{
public:
	~LogicSystem() = default;
	static std::shared_ptr<LogicSystem> GetInstance();
	void RegiserGetHandle(std::string url, HttpHandle handle); //注册get对应的处理函数
	void RegiserPostHandle(std::string url, HttpHandle handle); //注册post对应的处理函数
	bool GetHandle(std::string str, std::shared_ptr<Connection> connection); //GET调用对应的处理函数
	bool PostHandle(std::string str, std::shared_ptr<Connection> connection); //POST调用对应的处理函数
private:
	LogicSystem();
	LogicSystem(const LogicSystem&) = delete;
	LogicSystem& operator = (const LogicSystem&) = delete;
	static std::shared_ptr<LogicSystem> instance_;
	std::map<std::string, HttpHandle> GetHandles_; //get请求处理url
	std::map<std::string, HttpHandle> PostHandles_; //post请求处理json
};