#include "StatusServerImpl.h"
#include "ErrorCodes.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <string>

using namespace std;

static string CreatUUID()
{
	boost::uuids::uuid uuid = boost::uuids::random_generator()();
	return boost::uuids::to_string(uuid);
}

StatusServerImpl::StatusServerImpl()
	:index_(0)
{
	//For Debug
	servers_.emplace_back(ChatServer{ "127.0.0.1", "9001" });
}

Status StatusServerImpl::GetChatServer(ServerContext* context, const GetStatusServiceReq *req, GetStatusServiceRes* res)
{
	//Debug
	cout << "receive uid: " << req->uid() << endl;
	auto& server = servers_[index_++];
	if (index_ >= servers_.size()) index_ = 0;
	res->set_host(server.host);
	res->set_port(server.port);
	res->set_error(ErrorCodes::SUCCESS);
	res->set_token(CreatUUID());
	return Status::OK;
}
