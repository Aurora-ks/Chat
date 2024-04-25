#include "StatusGrpcClient.h"
#include "ErrorCodes.h"

//TODO 使用连接池

StatusGrpcClient::StatusGrpcClient()
{
	//TODO use config to load host
	std::shared_ptr<Channel> channel = grpc::CreateChannel("127.0.0.1:10087", grpc::InsecureChannelCredentials());
	stub_ = StatusService::NewStub(channel);
}

GetStatusServiceRes StatusGrpcClient::GetChatServer(int uid)
{
	ClientContext context;
	GetStatusServiceReq req;
	GetStatusServiceRes res;
	req.set_uid(uid);
	Status status = stub_->GetChatServer(&context, req, &res);
	if (status.ok()) return res;
	else
	{
		res.set_error(ErrorCodes::RPCErr);
		return res;
	}
	return GetStatusServiceRes();
}
