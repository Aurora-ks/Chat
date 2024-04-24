#include "LogicSystem.h"
#include "Connection.h"
#include "ErrorCodes.h"
#include "message.pb.h"
#include "VarifyClient.h"
#include "RedisManager.h"
#include "MysqlDao.h"

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
	// 获取验证码
	RegiserPostHandle("/varify", [](shared_ptr<Connection> connection)
		{
			string BodyData = beast::buffers_to_string(connection->request().body().data());
			// Debug
			cout << "Data: " << BodyData << endl;

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
	// 注册
	RegiserPostHandle("/register", [](shared_ptr<Connection> connection)
		{
			string data = beast::buffers_to_string(connection->request().body().data());
			//Debug
			cout << "receive " << data << endl;

			connection->request().set(http::field::content_type, "text/json");
			Json::Value response;
			Json::Value request;
			Json::Reader reader;
			if (!reader.parse(data, request))
			{
				response["error"] = ErrorCodes::ERR_JSON;
				beast::ostream(connection->response().body()) << response.toStyledString();
				return;
			}

			string name = request["user"].asString();
			string password = request["password"].asString();
			string email = request["email"].asString();
			string confirm = request["confirm"].asString();

			//验证码过期
			auto VarifyCode = RedisManager::Instance().GetRedis().get(request["email"].asString());
			if (!VarifyCode)
			{
				//Debug
				cout << "Get Varifycode Expired\n";
				response["error"] = ErrorCodes::VarifyExpired;
				beast::ostream(connection->response().body()) << response.toStyledString();
				return;
			}
			//验证码不匹配
			if (*VarifyCode != request["varifycode"].asString())
			{
				//Debug
				cout << "Varifycode Error\n";
				response["error"] = ErrorCodes::VarifyCodeErr;
				beast::ostream(connection->response().body()) << response.toStyledString();
				return;
			}
			//用户名是否存在
			int uid = MysqlDao().UserRegister(name, password, email);
			if (uid == 0 || uid == -1)
			{
				//Debug
				cout << "user or email exist\n";
				response["error"] = ErrorCodes::UserExist;
				beast::ostream(connection->response().body()) << response.toStyledString();
				return;
			}
			response["error"] = ErrorCodes::SUCCESS;
			response["email"] = email;
			response["user"] = name;
			response["password"] = password;
			response["confirm"] = confirm;
			response["varifycode"] = request["varifycode"].asString();
			beast::ostream(connection->response().body()) << response.toStyledString();
		});
	// 登录
	RegiserPostHandle("/login", [](shared_ptr<Connection> connection)
		{
			string data = beast::buffers_to_string(connection->request().body().data());
			//Debug
			cout << "receive " << data << endl;

			connection->response().set(http::field::content_type, "text/json");
			Json::Value response;
			Json::Reader reader;
			Json::Value request;
			if (!reader.parse(data, request))
			{
				response["error"] = ErrorCodes::ERR_JSON;
				beast::ostream(connection->response().body()) << response.toStyledString();
				return;
			}

			string name = request["usr"].asString();
			string password = request["password"].asString();

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
