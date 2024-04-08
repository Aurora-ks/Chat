#pragma once
#include <memory>
#include <mutex>
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"

using grpc::ClientContext;
using grpc::Channel;
using grpc::Status;
using message::Varify;
using message::VarifyReq;
using message::VarifyRes;

class VarifyClient
{
public:
	~VarifyClient() = default;
	static std::shared_ptr<VarifyClient> GetInstance();
	VarifyRes GetVarifyCode(std::string email);
private:
	VarifyClient();
	VarifyClient(const VarifyClient&) = delete;
	VarifyClient& operator = (const VarifyClient&) = delete;
	static std::shared_ptr<VarifyClient> instance_;
	std::unique_ptr<Varify::Stub> stub_;
};

