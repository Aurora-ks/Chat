#include "VerifyClient.h"
#include "ErrorCodes.h"

std::shared_ptr<VerifyClient> VerifyClient::instance_ = nullptr;

//TODO
//增加多线程支持

VerifyClient::VerifyClient()
{
    std::shared_ptr<Channel> channel = grpc::CreateChannel("127.0.0.1:10086", grpc::InsecureChannelCredentials());
    stub_ = Verify::NewStub(channel);
}

std::shared_ptr<VerifyClient> VerifyClient::GetInstance()
{
    static std::once_flag flag;
    std::call_once(flag, [&]() {
        instance_ = std::shared_ptr<VerifyClient>(new VerifyClient);
        });
    return instance_;
}

VerifyRes VerifyClient::GetVerifyCode(std::string email)
{
    ClientContext context;
    VerifyReq request;
    VerifyRes response;
    request.set_email(email);
    Status status = stub_->GetVerifyCode(&context, request, &response);
    if (status.ok()) {
        response.set_error(ErrorCodes::SUCCESS);
    }
    else {
        response.set_error(ErrorCodes::RPCErr);
    }
    return response;
}
