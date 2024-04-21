#include "LogicSystem.h"
#include "Connection.h"
#include "ErrorCodes.h"
#include "message.pb.h"
#include "VarifyClient.h"
#include "RedisManager.h"

#include <mutex>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>

using namespace std;

LogicSystem::LogicSystem()
{
	// For Test
	RegiserGetHandle("/test", [](shared_ptr<Connection> connection)
		{
			beast::ostream(connection->response().body()) << "receive get\r\n";
		});

	RegiserPostHandle("/varify", [](shared_ptr<Connection> connection)
		{
			string BodyData = beast::buffers_to_string(connection->request().body().data());
			cout << "Receive From:" << connection->socket().remote_endpoint().address().to_string() << "\nData: " << BodyData << endl;
			connection->response().set(http::field::content_type, "text/json");
			Json::Value response;
			Json::Reader reader;
			Json::Value request;
			if (!reader.parse(BodyData, request) || !request.isMember("email"))
			{
				cout << "Json Parse Failed! " << reader.getFormattedErrorMessages() << endl;
				response["error"] = Json::Value(ErrorCodes::ERR_JSON);
			}
			else
			{
				string email = request["email"].asString();
				message::VarifyRes res = VarifyClient::GetInstance()->GetVarifyCode(email);
				response["error"] = Json::Value(res.error());
				response["email"] = Json::Value(res.email());
			}
			string jsonstr = response.toStyledString();
			beast::ostream(connection->response().body()) << jsonstr;
		});

	RegiserPostHandle("/register", [](shared_ptr<Connection> connection)
		{
			auto data = beast::buffers_to_string(connection->request().body().data());
			cout << "receive " << data << endl;
			connection->request().set(http::field::content_type, "text/json");

			Json::Value root;
			Json::Value parsed;
			Json::Reader reader;
			if (!reader.parse(data, parsed))
			{
				root["error"] = ErrorCodes::ERR_JSON;
				beast::ostream(connection->response().body()) << root.toStyledString();
				return;
			}
			auto VarifyCode = RedisManager::Instance().GetRedis().get(parsed["email"].asString());
			if (!VarifyCode)
			{
				cout << "Get Varifycode Expired\n";
				root["error"] = ErrorCodes::VarifyExpired;
				beast::ostream(connection->response().body()) << root.toStyledString();
				return;
			}
			if (*VarifyCode != parsed["varifycode"].asString())
			{
				cout << "Varifycode Error\n";
				root["error"] = ErrorCodes::VarifyCodeErr;
				beast::ostream(connection->response().body()) << root.toStyledString();
				return;
			}
			root["error"] = ErrorCodes::SUCCESS;
			root["email"] = parsed["email"];
			root["user"] = parsed["user"].asString();
			root["password"] = parsed["password"].asString();
			root["confirm"] = parsed["confirm"].asString();
			root["varifycode"] = parsed["varifycode"].asString();
			beast::ostream(connection->response().body()) << root.toStyledString();
		});
}

void LogicSystem::RegiserGetHandle(string url, HttpHandle handle)
{
	GetHandles_.insert({ url, handle });
}

void LogicSystem::RegiserPostHandle(string url, HttpHandle handle)
{
	PostHandles_.insert({ url, handle });
}

bool LogicSystem::GetHandle(string str, shared_ptr<Connection> connection)
{
	//不存在对应的处理函数
	if (GetHandles_.find(str) == GetHandles_.end()) return false;
	//调用对应的处理函数
	GetHandles_[str](connection);
	return true;
}

bool LogicSystem::PostHandle(string str, shared_ptr<Connection> connection)
{
	//不存在对应的处理函数
	if (PostHandles_.find(str) == PostHandles_.end()) return false;
	//调用对应的处理函数
	PostHandles_[str](connection);
	return true;
}
