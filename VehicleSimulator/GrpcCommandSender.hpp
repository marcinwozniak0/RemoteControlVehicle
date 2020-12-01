#pragma once

#include <grpc++/grpc++.h>
#include <memory>

#include <Client.grpc.pb.h>

class GrpcCommandSender
{
public:
    GrpcCommandSender(std::shared_ptr<Router::StubInterface>);

    std::optional<Commands::Acknowledge> sendCommand(google::protobuf::Any&&);

private:
    std::string connectWithServer() const;
    template <typename Timer> void tryConnectWithServer(Timer&) const;

    std::shared_ptr<Router::StubInterface> _stub;
};
