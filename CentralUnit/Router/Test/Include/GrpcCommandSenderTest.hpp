#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Client.grpc.pb.h>
#include <Client_mock.grpc.pb.h>

#include "GrpcCommandSender.hpp"
#include "CommunicationSocketException.hpp"

using namespace ::testing;

namespace
{
const grpc::Status notOkStatus {grpc::StatusCode::CANCELLED, grpc::string{}};
const grpc::Status okStatus {grpc::StatusCode::OK, grpc::string{}};

InitCommands::HelloRequest buildHelloRequest()
{
    InitCommands::HelloRequest helloRequest;
    helloRequest.set_name("CONTROLER");
    return helloRequest;
}
InitCommands::HelloRequest helloRequest = buildHelloRequest();
}

class GrpcCommandSenderTest : public Test
{
public:
    GrpcCommandSenderTest()
    {   
        EXPECT_CALL(*_stubMock, SayHello(_, helloRequest, _)).WillOnce(Return(okStatus));

        _sut = std::make_unique<GrpcCommandSender>(_stubMock);
    }

    std::unique_ptr<GrpcCommandSender> _sut;
    std::shared_ptr<StrictMock<MockRouterStub>> _stubMock = std::make_shared<StrictMock<MockRouterStub>>();
};
