#pragma once
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"

using grpc::Server;
using grpc::ServerContext;
using grpc::Status;
using message::StatusService;
using message::GetStatusServiceReq;
using message::GetStatusServiceRes;

struct ChatServer
{
	std::string host;
	std::string port;
};

class StatusServerImpl : public StatusService::Service
{
public:
	StatusServerImpl();
	Status GetChatServer(ServerContext* context, const GetStatusServiceReq *req, GetStatusServiceRes* res) override;
private:
	std::vector<ChatServer> servers_;
	int index_;
};

