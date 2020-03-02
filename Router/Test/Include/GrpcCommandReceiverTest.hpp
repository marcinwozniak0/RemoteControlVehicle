#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <thread>

#include <Client.grpc.pb.h>
#include <Client_mock.grpc.pb.h>

#include "GrpcCommandReceiver.hpp"
#include "GrpcCommandSender.hpp"
#include "CommunicationSocketException.hpp"

using namespace ::testing;

namespace
{
    const std::string portAddress = "0.0.0.0:50050";
}

using Client = std::unique_ptr<GrpcCommandSender>;
using Server = std::unique_ptr<GrpcCommandReceiver>;

class GrpcCommandReceiverTest : public Test
{
public:
    GrpcCommandReceiverTest() 
    {
        _serverThread = std::make_unique<std::thread>([this](){initServer();});
        _clientThread = std::make_unique<std::thread>([this](){initClient();});
        waitForConnectionEstablish();
    }

    ~GrpcCommandReceiverTest()
    {    
        _clientThread->join();
        _serverThread->join();
    }

    Client _commandSender;
    Server _sut;

    template <typename Command>
    void sendCommandToSut(const Command&& command)
    {
        google::protobuf::Any commandToSend;
        commandToSend.PackFrom(command);

        _commandSender->sendCommand(std::move(commandToSend));
    }

private:
    std::unique_ptr<std::thread> _serverThread;
    std::unique_ptr<std::thread> _clientThread;

    void initServer()
    {
        _sut = std::make_unique<GrpcCommandReceiver>(portAddress);
    }

    void initClient()
    {
        _commandSender = std::make_unique<GrpcCommandSender>(std::make_shared<Router::Stub>(
            grpc::CreateChannel(portAddress, grpc::InsecureChannelCredentials())));
    }

    void waitForConnectionEstablish()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

};
