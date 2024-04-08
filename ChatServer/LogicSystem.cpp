#include "LogicSystem.h"
#include "Connection.h"
#include <mutex>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "ErrorCodes.h"
#include "message.pb.h"
#include "VarifyClient.h"

std::shared_ptr<LogicSystem> LogicSystem::instance_ = nullptr;

LogicSystem::LogicSystem()
{
	RegiserGetHandle("/test", [](std::shared_ptr<Connection> connection) {
		beast::ostream(connection->response_.body()) << "receive get\r\n";
		});
	RegiserPostHandle("/varify", [](std::shared_ptr<Connection> connection) {
		std::string BodyData = beast::buffers_to_string(connection->request_.body().data());
		std::cout << "Receive From:" << connection->socket_.remote_endpoint().address().to_string() << "\nData: " << BodyData << std::endl;
		connection->response_.set(http::field::content_type, "text/json");
		Json::Value response;
		Json::Reader reader;
		Json::Value request;
		if (!reader.parse(BodyData, request) || !request.isMember("email")) {
			std::cout << "Json Parse Failed! " << reader.getFormattedErrorMessages() << std::endl;
			response["error"] = Json::Value(ErrorCodes::ERR_JSON);
		}
		else
		{
			std::string email = request["email"].asString();
			message::VarifyRes res = VarifyClient::GetInstance()->GetVarifyCode(email);
			response["error"] = Json::Value(res.error());
			response["email"] = Json::Value(res.email());
		}
		std::string jsonstr = response.toStyledString();
		beast::ostream(connection->response_.body()) << jsonstr;
		return true;
		});
}

std::shared_ptr<LogicSystem> LogicSystem::GetInstance()
{
	static std::once_flag flag;
	std::call_once(flag, [&]() {
		instance_ = std::shared_ptr<LogicSystem>(new LogicSystem);
		});
	return instance_;
}

void LogicSystem::RegiserGetHandle(std::string url, HttpHandle handle)
{
	GetHandles_.insert({ url, handle });
}

void LogicSystem::RegiserPostHandle(std::string url, HttpHandle handle)
{
	PostHandles_.insert({ url, handle });
}

bool LogicSystem::GetHandle(std::string str, std::shared_ptr<Connection> connection)
{
	//不存在对应的处理函数
	if (GetHandles_.find(str) == GetHandles_.end()) return false;
	//调用对应的处理函数
	GetHandles_[str](connection);
	return true;
}

bool LogicSystem::PostHandle(std::string str, std::shared_ptr<Connection> connection)
{
	//不存在对应的处理函数
	if (PostHandles_.find(str) == PostHandles_.end()) return false;
	//调用对应的处理函数
	PostHandles_[str](connection);
	return true;
}
