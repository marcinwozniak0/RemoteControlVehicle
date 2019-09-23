#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>
#include <chrono>

#include <Deactivate.pb.h>
#include <UserCommandToStop.pb.h>
#include <UserCommandToStart.pb.h>
#include <UserCommandToRun.pb.h>

#include "VehicleControler.hpp"
#include "CommandReceiverMock.hpp"
#include "EngineMock.hpp"
#include "PropulsionSystemMock.hpp"
#include "SteeringSystemMock.hpp"

using namespace ::testing;

namespace
{
constexpr int16_t xCoordinate = 700;
constexpr int16_t yCoordinate = 5500;

const std::string createSerializedDeactivateMessage()
{
    Messages::Deactivate deactivateMessage;
    google::protobuf::Any topLevelMessage;
    std::string serializedMessage;

    topLevelMessage.PackFrom(deactivateMessage);
    topLevelMessage.SerializeToString(&serializedMessage);

    return serializedMessage;
}

const std::string createSerializedUserCommandToStart()
{
    Messages::UserCommandToStart userCommandToStart;
    google::protobuf::Any topLevelMessage;
    std::string serializedMessage;

    topLevelMessage.PackFrom(userCommandToStart);
    topLevelMessage.SerializeToString(&serializedMessage);

    return serializedMessage;
}

const std::string createSerializedUserCommandToStop()
{
    Messages::UserCommandToStop userCommandToStop;
    google::protobuf::Any topLevelMessage;
    std::string serializedMessage;

    topLevelMessage.PackFrom(userCommandToStop);
    topLevelMessage.SerializeToString(&serializedMessage);

    return serializedMessage;
}

const std::string createSerializedUserCommandToRun()
{
    Messages::UserCommandToRun userCommandToRun;
    google::protobuf::Any topLevelMessage;
    std::string serializedMessage;

    userCommandToRun.mutable_coordinate_system()->set_x_coordinate(xCoordinate);
    userCommandToRun.mutable_coordinate_system()->set_y_coordinate(yCoordinate);

    topLevelMessage.PackFrom(userCommandToRun);
    topLevelMessage.SerializeToString(&serializedMessage);

    return serializedMessage;
}
}//namespace

class VehicleControlerTest : public Test
{
public:
    VehicleControlerTest()
        : _commandQueue(std::make_shared<CommandsQueue>())
        ,_vehicle(_propulsionSystemMock, _steeringSystemMock)
    {
        EXPECT_CALL(_commandReceiverMock, shareCommandsQueue()).WillOnce(Return(_commandQueue));
        _sut = std::make_unique<VehicleControler>(_commandReceiverMock, _vehicle);
    }

    std::unique_ptr<VehicleControler> _sut;
    NiceMock<PropulsionSystemMock> _propulsionSystemMock;
    NiceMock<CommandReceiverMock> _commandReceiverMock;
    NiceMock<SteeringSystemMock> _steeringSystemMock;
    std::shared_ptr<CommandsQueue> _commandQueue;
    Vehicle _vehicle;
};

