#include "VarifyClient.h"
#include "ErrorCodes.h"

std::shared_ptr<VarifyClient> VarifyClient::instance_ = nullptr;

VarifyClient::VarifyClient()
{
    std::shared_ptr<Channel> channel = grpc::CreateChannel("127.0.0.1:10086", grpc::InsecureChannelCredentials());
    stub_ = Varify::NewStub(channel);
}

std::shared_ptr<VarifyClient> VarifyClient::GetInstance()
{
    std::once_flag flag;
    std::call_once(flag, [&]() {
        instance_ = std::shared_ptr<VarifyClient>(new VarifyClient);
        });
    return instance_;
    /*if (instance_ == nullptr) {
        instance_ = std::shared_ptr<VarifyClient>(new VarifyClient);
    }
    return instance_;*/
}

VarifyRes VarifyClient::GetVarifyCode(std::string email)
{
    ClientContext context;
    VarifyReq request;
    VarifyRes response;
    request.set_email(email);
    Status status = stub_->GetVarifyCode(&context, request, &response);
    if (status.ok()) {
        response.set_error(ErrorCodes::SUCCESS);
    }
    else {
        response.set_error(ErrorCodes::ERR_RPC);
    }
    return response;
}
