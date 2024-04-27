#pragma once
#include "Singleton.ipp"
#include <queue>
#include <map>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>

class LogicNode;
class Connection;

class LogicSystem : public Singleton<LogicSystem>
{
	friend class Singleton<LogicSystem>;
public:
	void PostMessage(std::shared_ptr<LogicNode> LogicNode);
private:
	using callback = std::function<void(std::shared_ptr<Connection>, const unsigned short id, const string& data)>;

	LogicSystem();
	void RegisterHandle(callback);
	bool running_;
	std::thread thread_;
	std::queue<std::shared_ptr<LogicNode>> queue_;
	std::mutex mutex_;
	std::condition_variable cond_;
	std::map<unsigned short, callback> handlers_;
};

