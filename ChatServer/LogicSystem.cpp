#include "LogicSystem.h"
#include "Connection.h"
#include "CServer.h"
#include "ErrorCodes.h"
#include <json/json.h>
#include <json/reader.h>
#include <json/value.h>

using namespace std;

LogicSystem::LogicSystem()
	:running_(true),
	thread_(&LogicSystem::ConsumeMessage, this)
{
	RegisterHandle();
}

void LogicSystem::RegisterHandle()
{
	handlers_.emplace(LOGIN_CHAT, [this](shared_ptr<Connection> con, const std::string& data) {
		Json::Value request;
		Json::Value response;
		Json::Reader reader;
		if (!reader.parse(data, request))
		{
			response["error"] = ErrorCodes::JsonErr;
			return;
		}
		else
		{
			int uid = request["uid"].asInt();
			con->server()->AddConnectionId(uid, con->uuid());
			response["error"] = ErrorCodes::SUCCESS;
		}
		con->send(response.toStyledString(), LOGIN_CHAT);
		});
}

LogicSystem::~LogicSystem()
{
	running_ = false;
	cond_.notify_one();
	thread_.join();
}

void LogicSystem::post(std::shared_ptr<LogicNode> LogicNode)
{
	unique_lock<mutex> lock(mutex_);
	queue_.emplace(LogicNode);
	if (queue_.size() == 1)
	{
		lock.unlock();
		cond_.notify_one();
	}
}

void LogicSystem::ConsumeMessage()
{
	while (1)
	{
		unique_lock<mutex> lock(mutex_);
		cond_.wait(lock, [this] {return !queue_.empty() || !running_; });
		auto msg = queue_.front();
		queue_.pop();
		if (handlers_.find(msg->ReceiveNode_->id_) == handlers_.end())
		{
			continue;
		}
		handlers_[msg->ReceiveNode_->id_](msg->connection_, msg->ReceiveNode_->DataToString());

		if (!running_)
		{
			while (!queue_.empty())
			{
				auto msg = queue_.front();
				queue_.pop();
				if (handlers_.find(msg->ReceiveNode_->id_) == handlers_.end())
				{
					continue;
				}
				handlers_[msg->ReceiveNode_->id_](msg->connection_, msg->ReceiveNode_->DataToString());
			}
			break;
		}
	}
}
