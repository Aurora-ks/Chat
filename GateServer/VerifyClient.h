#pragma once
#include <memory>
#include <mutex>
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"

using grpc::ClientContext;
using grpc::Channel;
using grpc::Status;
using message::Verify;
using message::VerifyReq;
using message::VerifyRes;

class VerifyClient
{
public:
	~VerifyClient() = default;
	static std::shared_ptr<VerifyClient> GetInstance();
	VerifyRes GetVerifyCode(std::string email);
private:
	VerifyClient();
	VerifyClient(const VerifyClient&) = delete;
	VerifyClient& operator = (const VerifyClient&) = delete;
	static std::shared_ptr<VerifyClient> instance_;
	std::unique_ptr<Verify::Stub> stub_;
};

