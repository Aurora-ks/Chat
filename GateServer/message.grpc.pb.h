// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: message.proto
#ifndef GRPC_message_2eproto__INCLUDED
#define GRPC_message_2eproto__INCLUDED

#include "message.pb.h"

#include <functional>
#include <grpc/impl/codegen/port_platform.h>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace message {

class Verify final {
 public:
  static constexpr char const* service_full_name() {
    return "message.Verify";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status GetVerifyCode(::grpc::ClientContext* context, const ::message::VerifyReq& request, ::message::VerifyRes* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::message::VerifyRes>> AsyncGetVerifyCode(::grpc::ClientContext* context, const ::message::VerifyReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::message::VerifyRes>>(AsyncGetVerifyCodeRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::message::VerifyRes>> PrepareAsyncGetVerifyCode(::grpc::ClientContext* context, const ::message::VerifyReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::message::VerifyRes>>(PrepareAsyncGetVerifyCodeRaw(context, request, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      virtual void GetVerifyCode(::grpc::ClientContext* context, const ::message::VerifyReq* request, ::message::VerifyRes* response, std::function<void(::grpc::Status)>) = 0;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void GetVerifyCode(::grpc::ClientContext* context, const ::message::VerifyReq* request, ::message::VerifyRes* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      #else
      virtual void GetVerifyCode(::grpc::ClientContext* context, const ::message::VerifyReq* request, ::message::VerifyRes* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      #endif
    };
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    typedef class experimental_async_interface async_interface;
    #endif
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    async_interface* async() { return experimental_async(); }
    #endif
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::message::VerifyRes>* AsyncGetVerifyCodeRaw(::grpc::ClientContext* context, const ::message::VerifyReq& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::message::VerifyRes>* PrepareAsyncGetVerifyCodeRaw(::grpc::ClientContext* context, const ::message::VerifyReq& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status GetVerifyCode(::grpc::ClientContext* context, const ::message::VerifyReq& request, ::message::VerifyRes* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::message::VerifyRes>> AsyncGetVerifyCode(::grpc::ClientContext* context, const ::message::VerifyReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::message::VerifyRes>>(AsyncGetVerifyCodeRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::message::VerifyRes>> PrepareAsyncGetVerifyCode(::grpc::ClientContext* context, const ::message::VerifyReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::message::VerifyRes>>(PrepareAsyncGetVerifyCodeRaw(context, request, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      void GetVerifyCode(::grpc::ClientContext* context, const ::message::VerifyReq* request, ::message::VerifyRes* response, std::function<void(::grpc::Status)>) override;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void GetVerifyCode(::grpc::ClientContext* context, const ::message::VerifyReq* request, ::message::VerifyRes* response, ::grpc::ClientUnaryReactor* reactor) override;
      #else
      void GetVerifyCode(::grpc::ClientContext* context, const ::message::VerifyReq* request, ::message::VerifyRes* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      #endif
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::message::VerifyRes>* AsyncGetVerifyCodeRaw(::grpc::ClientContext* context, const ::message::VerifyReq& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::message::VerifyRes>* PrepareAsyncGetVerifyCodeRaw(::grpc::ClientContext* context, const ::message::VerifyReq& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_GetVerifyCode_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status GetVerifyCode(::grpc::ServerContext* context, const ::message::VerifyReq* request, ::message::VerifyRes* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_GetVerifyCode : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_GetVerifyCode() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_GetVerifyCode() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetVerifyCode(::grpc::ServerContext* /*context*/, const ::message::VerifyReq* /*request*/, ::message::VerifyRes* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetVerifyCode(::grpc::ServerContext* context, ::message::VerifyReq* request, ::grpc::ServerAsyncResponseWriter< ::message::VerifyRes>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_GetVerifyCode<Service > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_GetVerifyCode : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithCallbackMethod_GetVerifyCode() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::message::VerifyReq, ::message::VerifyRes>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::message::VerifyReq* request, ::message::VerifyRes* response) { return this->GetVerifyCode(context, request, response); }));}
    void SetMessageAllocatorFor_GetVerifyCode(
        ::grpc::experimental::MessageAllocator< ::message::VerifyReq, ::message::VerifyRes>* allocator) {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
    #else
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::experimental().GetHandler(0);
    #endif
      static_cast<::grpc::internal::CallbackUnaryHandler< ::message::VerifyReq, ::message::VerifyRes>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~ExperimentalWithCallbackMethod_GetVerifyCode() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetVerifyCode(::grpc::ServerContext* /*context*/, const ::message::VerifyReq* /*request*/, ::message::VerifyRes* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* GetVerifyCode(
      ::grpc::CallbackServerContext* /*context*/, const ::message::VerifyReq* /*request*/, ::message::VerifyRes* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* GetVerifyCode(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::message::VerifyReq* /*request*/, ::message::VerifyRes* /*response*/)
    #endif
      { return nullptr; }
  };
  #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
  typedef ExperimentalWithCallbackMethod_GetVerifyCode<Service > CallbackService;
  #endif

  typedef ExperimentalWithCallbackMethod_GetVerifyCode<Service > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_GetVerifyCode : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_GetVerifyCode() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_GetVerifyCode() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetVerifyCode(::grpc::ServerContext* /*context*/, const ::message::VerifyReq* /*request*/, ::message::VerifyRes* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_GetVerifyCode : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_GetVerifyCode() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_GetVerifyCode() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetVerifyCode(::grpc::ServerContext* /*context*/, const ::message::VerifyReq* /*request*/, ::message::VerifyRes* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetVerifyCode(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_GetVerifyCode : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithRawCallbackMethod_GetVerifyCode() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->GetVerifyCode(context, request, response); }));
    }
    ~ExperimentalWithRawCallbackMethod_GetVerifyCode() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetVerifyCode(::grpc::ServerContext* /*context*/, const ::message::VerifyReq* /*request*/, ::message::VerifyRes* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* GetVerifyCode(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* GetVerifyCode(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #endif
      { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_GetVerifyCode : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_GetVerifyCode() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::message::VerifyReq, ::message::VerifyRes>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::message::VerifyReq, ::message::VerifyRes>* streamer) {
                       return this->StreamedGetVerifyCode(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_GetVerifyCode() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status GetVerifyCode(::grpc::ServerContext* /*context*/, const ::message::VerifyReq* /*request*/, ::message::VerifyRes* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedGetVerifyCode(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::message::VerifyReq,::message::VerifyRes>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_GetVerifyCode<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_GetVerifyCode<Service > StreamedService;
};

class StatusService final {
 public:
  static constexpr char const* service_full_name() {
    return "message.StatusService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status GetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerReq& request, ::message::GetChatServerRes* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::message::GetChatServerRes>> AsyncGetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::message::GetChatServerRes>>(AsyncGetChatServerRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::message::GetChatServerRes>> PrepareAsyncGetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::message::GetChatServerRes>>(PrepareAsyncGetChatServerRaw(context, request, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      virtual void GetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerReq* request, ::message::GetChatServerRes* response, std::function<void(::grpc::Status)>) = 0;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void GetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerReq* request, ::message::GetChatServerRes* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      #else
      virtual void GetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerReq* request, ::message::GetChatServerRes* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      #endif
    };
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    typedef class experimental_async_interface async_interface;
    #endif
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    async_interface* async() { return experimental_async(); }
    #endif
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::message::GetChatServerRes>* AsyncGetChatServerRaw(::grpc::ClientContext* context, const ::message::GetChatServerReq& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::message::GetChatServerRes>* PrepareAsyncGetChatServerRaw(::grpc::ClientContext* context, const ::message::GetChatServerReq& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status GetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerReq& request, ::message::GetChatServerRes* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::message::GetChatServerRes>> AsyncGetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::message::GetChatServerRes>>(AsyncGetChatServerRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::message::GetChatServerRes>> PrepareAsyncGetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::message::GetChatServerRes>>(PrepareAsyncGetChatServerRaw(context, request, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      void GetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerReq* request, ::message::GetChatServerRes* response, std::function<void(::grpc::Status)>) override;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void GetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerReq* request, ::message::GetChatServerRes* response, ::grpc::ClientUnaryReactor* reactor) override;
      #else
      void GetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerReq* request, ::message::GetChatServerRes* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      #endif
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::message::GetChatServerRes>* AsyncGetChatServerRaw(::grpc::ClientContext* context, const ::message::GetChatServerReq& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::message::GetChatServerRes>* PrepareAsyncGetChatServerRaw(::grpc::ClientContext* context, const ::message::GetChatServerReq& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_GetChatServer_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status GetChatServer(::grpc::ServerContext* context, const ::message::GetChatServerReq* request, ::message::GetChatServerRes* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_GetChatServer : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_GetChatServer() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_GetChatServer() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetChatServer(::grpc::ServerContext* /*context*/, const ::message::GetChatServerReq* /*request*/, ::message::GetChatServerRes* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetChatServer(::grpc::ServerContext* context, ::message::GetChatServerReq* request, ::grpc::ServerAsyncResponseWriter< ::message::GetChatServerRes>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_GetChatServer<Service > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_GetChatServer : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithCallbackMethod_GetChatServer() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::message::GetChatServerReq, ::message::GetChatServerRes>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::message::GetChatServerReq* request, ::message::GetChatServerRes* response) { return this->GetChatServer(context, request, response); }));}
    void SetMessageAllocatorFor_GetChatServer(
        ::grpc::experimental::MessageAllocator< ::message::GetChatServerReq, ::message::GetChatServerRes>* allocator) {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
    #else
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::experimental().GetHandler(0);
    #endif
      static_cast<::grpc::internal::CallbackUnaryHandler< ::message::GetChatServerReq, ::message::GetChatServerRes>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~ExperimentalWithCallbackMethod_GetChatServer() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetChatServer(::grpc::ServerContext* /*context*/, const ::message::GetChatServerReq* /*request*/, ::message::GetChatServerRes* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* GetChatServer(
      ::grpc::CallbackServerContext* /*context*/, const ::message::GetChatServerReq* /*request*/, ::message::GetChatServerRes* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* GetChatServer(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::message::GetChatServerReq* /*request*/, ::message::GetChatServerRes* /*response*/)
    #endif
      { return nullptr; }
  };
  #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
  typedef ExperimentalWithCallbackMethod_GetChatServer<Service > CallbackService;
  #endif

  typedef ExperimentalWithCallbackMethod_GetChatServer<Service > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_GetChatServer : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_GetChatServer() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_GetChatServer() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetChatServer(::grpc::ServerContext* /*context*/, const ::message::GetChatServerReq* /*request*/, ::message::GetChatServerRes* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_GetChatServer : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_GetChatServer() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_GetChatServer() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetChatServer(::grpc::ServerContext* /*context*/, const ::message::GetChatServerReq* /*request*/, ::message::GetChatServerRes* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetChatServer(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_GetChatServer : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithRawCallbackMethod_GetChatServer() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->GetChatServer(context, request, response); }));
    }
    ~ExperimentalWithRawCallbackMethod_GetChatServer() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetChatServer(::grpc::ServerContext* /*context*/, const ::message::GetChatServerReq* /*request*/, ::message::GetChatServerRes* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* GetChatServer(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* GetChatServer(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #endif
      { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_GetChatServer : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_GetChatServer() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::message::GetChatServerReq, ::message::GetChatServerRes>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::message::GetChatServerReq, ::message::GetChatServerRes>* streamer) {
                       return this->StreamedGetChatServer(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_GetChatServer() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status GetChatServer(::grpc::ServerContext* /*context*/, const ::message::GetChatServerReq* /*request*/, ::message::GetChatServerRes* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedGetChatServer(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::message::GetChatServerReq,::message::GetChatServerRes>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_GetChatServer<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_GetChatServer<Service > StreamedService;
};

}  // namespace message


#endif  // GRPC_message_2eproto__INCLUDED
