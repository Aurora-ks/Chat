#include "LogicSystem.h"
#include "Connection.h"
#include "ErrorCodes.h"
#include "message.pb.h"
#include "VarifyClient.h"
#include "StatusGrpcClient.h"
#include "RedisManager.h"
#include "MysqlDao.h"

#include <mutex>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>

using namespace std;


LogicSystem::LogicSystem()
{
	// 获取验证码
	RegiserPostHandle("/varify", [](ConnectionPtr connection)
		{
			string BodyData = beast::buffers_to_string(connection->request().body().data());
			// Debug
			cout << "Receive: " << BodyData << endl;

			connection->response().set(http::field::content_type, "text/json");
			Json::Value response;
			Json::Reader reader;
			Json::Value request;
			if (!reader.parse(BodyData, request) || !request.isMember("email"))
			{
				// Debug
				cout << "Json Parse Failed! " << reader.getFormattedErrorMessages() << endl;
				response["error"] = Json::Value(ErrorCodes::JsonErr);
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
	RegiserPostHandle("/register", [](ConnectionPtr connection)
		{
			string data = beast::buffers_to_string(connection->request().body().data());
			//Debug
			cout << "receive: " << data << endl;

			connection->request().set(http::field::content_type, "text/json");
			Json::Value response;
			Json::Value request;
			Json::Reader reader;
			if (!reader.parse(data, request))
			{
				response["error"] = ErrorCodes::JsonErr;
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
			int uid = MysqlDao::Instance().UserRegister(name, password, email);
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
	RegiserPostHandle("/login", [](ConnectionPtr connection)
		{
			string data = beast::buffers_to_string(connection->request().body().data());
			//Debug
			cout << "receive: " << data << endl;

			connection->response().set(http::field::content_type, "text/json");
			Json::Value response;
			Json::Reader reader;
			Json::Value request;
			if (!reader.parse(data, request))
			{
				response["error"] = ErrorCodes::JsonErr;
				beast::ostream(connection->response().body()) << response.toStyledString();
				return;
			}

			string name = request["user"].asString();
			string password = request["password"].asString();
			UserInfo userInfo;
			//查询数据库
			if (!MysqlDao::Instance().UserLogin(name, password, userInfo))
			{
				response["error"] = ErrorCodes::PasswordErr;
				beast::ostream(connection->response().body()) << response.toStyledString();
				return;
			}
			//获取ChatServer
			auto res = StatusGrpcClient::Instance().GetChatServer(userInfo.uid);
			if (res.error())
			{
				// Debug
				cout << "get chat server failed: " << res.error() << endl;
				response["error"] = ErrorCodes::RPCGetFailed;
				beast::ostream(connection->response().body()) << response.toStyledString();
				return;
			}

			// Debug
			cout << "get get chat server success uid: " << userInfo.uid << endl;

			response["error"] = ErrorCodes::SUCCESS;
			response["uid"] = userInfo.uid;
			response["user"] = name;
			response["host"] = res.host();
			response["port"] = res.port();
			response["token"] = res.token();
			beast::ostream(connection->response().body()) << response.toStyledString();
		});
	//获取好友列表
	//TODO use get request
	RegiserPostHandle("/get-friend", [](ConnectionPtr connection) {
		string data = beast::buffers_to_string(connection->request().body().data());
		//Debug
		cout << "receive: " << data << endl;
		connection->response().set(http::field::content_type, "text/json");
		Json::Value response;
		Json::Reader reader;
		Json::Value request(Json::arrayValue);
		if (!reader.parse(data, request))
		{
			response["error"] = ErrorCodes::JsonErr;
			beast::ostream(connection->response().body()) << response.toStyledString();
			return;
		}

		int user_id = request["uid"].asInt();
		auto res = MysqlDao::Instance().GetFriend(user_id);
		if (res.empty())
		{
			response["error"] = ErrorCodes::UserNotExist;
		}
		else
		{
			response["error"] = ErrorCodes::SUCCESS;
			for (const auto& i : res)
			{
				Json::Value t;
				t["uid"] = i.at("uid");
				t["user_name"] = i.at("user_name");
				response["arr"].append(t);
			}
		}
		beast::ostream(connection->response().body()) << response.toStyledString();
		});
	//添加好友
	RegiserPostHandle("/add-person", [](ConnectionPtr connection) {
		string data = beast::buffers_to_string(connection->request().body().data());
		//Debug
		cout << "receive: " << data << endl;
		connection->response().set(http::field::content_type, "text/json");
		Json::Value response;
		Json::Reader reader;
		Json::Value request;
		if (!reader.parse(data, request))
		{
			response["error"] = ErrorCodes::JsonErr;
			beast::ostream(connection->response().body()) << response.toStyledString();
			return;
		}

		string name = request["user"].asString();
		int uid = request["uid"].asInt();
		int res = MysqlDao::Instance().AddFriend(name, uid);
		if (res == -1 || res == -3) response["error"] = ErrorCodes::SQLErr;
		else if (res == -2) response["error"] = ErrorCodes::UserNotExist;
		else response["error"] = ErrorCodes::SUCCESS;
		response["uid"] = res;
		response["user_name"] = name;
		beast::ostream(connection->response().body()) << response.toStyledString();
		});
	//删除好友
	RegiserPostHandle("/del-friend", [](ConnectionPtr connection) {
		string data = beast::buffers_to_string(connection->request().body().data());
		//Debug
		cout << "receive: " << data << endl;
		connection->response().set(http::field::content_type, "text/json");
		Json::Value response;
		Json::Reader reader;
		Json::Value request;
		if (!reader.parse(data, request))
		{
			response["error"] = ErrorCodes::JsonErr;
			beast::ostream(connection->response().body()) << response.toStyledString();
			return;
		}

		int user_id = request["user_id"].asInt();
		int friend_id = request["friend_id"].asInt();
		if (user_id > friend_id) swap(user_id, friend_id);
		if (MysqlDao::Instance().DelFriend(user_id, friend_id))
			response["error"] = ErrorCodes::SUCCESS;
		else
			response["error"] = ErrorCodes::SQLErr;
		beast::ostream(connection->response().body()) << response.toStyledString();
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

bool LogicSystem::GetHandle(string str, ConnectionPtr connection)
{
	//不存在对应的处理函数
	if (GetHandles_.find(str) == GetHandles_.end()) return false;
	//调用对应的处理函数
	GetHandles_[str](connection);
	return true;
}

bool LogicSystem::PostHandle(string str, ConnectionPtr connection)
{
	//不存在对应的处理函数
	if (PostHandles_.find(str) == PostHandles_.end()) return false;
	//调用对应的处理函数
	PostHandles_[str](connection);
	return true;
}
