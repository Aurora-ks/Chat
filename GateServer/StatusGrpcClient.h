#pragma once
#include "Singleton.ipp"
#include "message.grpc.pb.h"
#include <memory>
#include <grpcpp/grpcpp.h>

using grpc::ClientContext;
using grpc::Channel;
using grpc::Status;
using message::StatusService;
using message::GetChatServerReq;
using message::GetChatServerRes;

class StatusGrpcClient : public Singleton<StatusGrpcClient>
{
	friend class Singleton<StatusGrpcClient>;
public:
	~StatusGrpcClient() = default;
	GetChatServerRes GetChatServer(int uid);
private:
	StatusGrpcClient();
	std::unique_ptr<StatusService::Stub> stub_;
};

