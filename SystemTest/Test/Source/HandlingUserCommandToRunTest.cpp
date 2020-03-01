#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Deactivate.pb.h>
#include <UserCommandToRun.pb.h>

#include "HandlingUserCommandToRunTest.hpp"
#include "ControlerCommandToRunMessageBuilder.hpp"
#include "SerializedCommandsBuilders.hpp"
#include "ProtobufStructuresComparators.hpp"

using namespace UTHelpers;

namespace
{
constexpr int32_t zeroXCoordinate = 0;
constexpr int32_t zeroYCoordinate = 0;
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
            .WillOnce(Return(createSerializedUserCommandToRun(zeroXCoordinate, zeroYCoordinate)))
            .WillOnce(Return(createSerializedDeactivateMessage()));

    const PinsConfiguration expectedNewPinsConfiguration = {{PIN_NUMBERS::FIRST_ENGINE_FIRST_OUTPUT, 1},
                                                            {PIN_NUMBERS::FIRST_ENGINE_SECOND_OUTPUT, 1},
                                                            {PIN_NUMBERS::FIRST_ENGINE_PWM, 0},
                                                            {PIN_NUMBERS::SECOND_ENGINE_FIRST_OUTPUT, 1},
                                                            {PIN_NUMBERS::SECOND_ENGINE_SECOND_OUTPUT, 1},
                                                            {PIN_NUMBERS::SECOND_ENGINE_PWM, 0},
                                                            {PIN_NUMBERS::STEERING_WHEEL_PWM, 19}};

    auto expectedMessage = ControlerCommandToRunMessageBuilder{}.pinsConfiguration(expectedNewPinsConfiguration)
                                                                .build();

    EXPECT_CALL(commandReceiverMock, sendCommand(std::move(expectedMessage)));

    vehicleControler.controlVehicle();
}
