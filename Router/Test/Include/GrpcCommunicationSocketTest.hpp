#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Client.grpc.pb.h>
#include <Client_mock.grpc.pb.h>

#include "GrpcCommunicationSocket.hpp"
#include "CommunicationSocketException.hpp"

using namespace ::testing;

namespace
{
const grpc::Status notOkStatus {grpc::StatusCode::CANCELLED, grpc::string{}};
const grpc::Status okStatus {grpc::StatusCode::OK, grpc::string{}};

HelloRequest buildHelloRequest()
{
    HelloRequest helloRequest;
    helloRequest.set_name("CONTROLER");
    return helloRequest;
}
HelloRequest helloRequest = buildHelloRequest();
}

class GrpcCommunicationSocketTest : public Test
{
public:
    GrpcCommunicationSocketTest()
    {   
        EXPECT_CALL(*_stubMock, SayHello(_, helloRequest, _)).WillOnce(Return(okStatus));

        _sut = std::make_unique<GrpcCommunicationSocket>(_stubMock);
    }

    std::unique_ptr<GrpcCommunicationSocket> _sut;
    std::shared_ptr<StrictMock<MockRouterStub>> _stubMock = std::make_shared<StrictMock<MockRouterStub>>();
};
