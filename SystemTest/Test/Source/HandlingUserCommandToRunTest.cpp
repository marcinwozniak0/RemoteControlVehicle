#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Deactivate.pb.h>
#include <UserCommandToRun.pb.h>

#include "HandlingUserCommandToRunTest.hpp"
#include "ControlerCommandToRunMessageBuilder.hpp"
#include "SerializedCommandsMatchers.hpp"

namespace
{
const std::string createSerializedDeactivateMessage()
{
    Messages::Deactivate deactivateMessage;
    google::protobuf::Any topLevelMessage;
    std::string serializedMessage;

    topLevelMessage.PackFrom(deactivateMessage);
    topLevelMessage.SerializeToString(&serializedMessage);

    return serializedMessage;
}

const std::string createSerializedUserCommandToRun(const int32_t xCoordinate, const int32_t yCoordinate)
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

HandlingUserCommandToRunTest::HandlingUserCommandToRunTest()
        : firstEngine(PIN_NUMBERS::FIRST_ENGINE_FIRST_OUTPUT,
                      PIN_NUMBERS::FIRST_ENGINE_SECOND_OUTPUT,
                      PIN_NUMBERS::FIRST_ENGINE_PWM)
        , secondEngine(PIN_NUMBERS::SECOND_ENGINE_FIRST_OUTPUT,
                       PIN_NUMBERS::SECOND_ENGINE_SECOND_OUTPUT,
                       PIN_NUMBERS::SECOND_ENGINE_PWM)
        , propulsionSystem(firstEngine, secondEngine, engineDriver)
        , steeringWheel(PIN_NUMBERS::STEERING_WHEEL_PWM)
        , steeringSystem(steeringWheel)
        , vehicle(propulsionSystem, steeringSystem)
        , vehicleControler(commandReceiverMock, vehicle)
    {}

TEST_F(HandlingUserCommandToRunTest, ZeroZeroCoordinates)
{
    EXPECT_CALL(commandReceiverMock, takeMessageFromQueue()).Times(2)
            .WillOnce(Return(createSerializedUserCommandToRun(0,0)))
            .WillOnce(Return(createSerializedDeactivateMessage()));

    const PinsConfiguration pinsConfiguration = {{PIN_NUMBERS::FIRST_ENGINE_FIRST_OUTPUT, 1},
                                                 {PIN_NUMBERS::FIRST_ENGINE_SECOND_OUTPUT, 1},
                                                 {PIN_NUMBERS::FIRST_ENGINE_PWM, 0},
                                                 {PIN_NUMBERS::SECOND_ENGINE_FIRST_OUTPUT, 1},
                                                 {PIN_NUMBERS::SECOND_ENGINE_SECOND_OUTPUT, 1},
                                                 {PIN_NUMBERS::SECOND_ENGINE_PWM, 0},
                                                 {PIN_NUMBERS::STEERING_WHEEL_PWM, 19}};

    const auto message = ControlerCommandToRunMessageBuilder{}.pinsConfiguration(pinsConfiguration)
                             .build();
    std::string serializedMessage;
    message.SerializeToString(&serializedMessage);

    EXPECT_CALL(commandReceiverMock, sendCommand(SerializedControlerCommandToRunMatcher(serializedMessage)));

    vehicleControler.controlVehicle();
}
