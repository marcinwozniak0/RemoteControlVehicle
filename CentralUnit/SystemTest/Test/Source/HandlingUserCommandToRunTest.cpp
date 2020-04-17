#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Deactivate.pb.h>
#include <UserCommandToRun.pb.h>

#include "HandlingUserCommandToRunTest.hpp"
#include "ControlerCommandToRunMessageBuilder.hpp"
#include "UtCommandsBuilders.hpp"
#include "ProtobufStructuresComparators.hpp"

using namespace UTHelpers;

namespace
{
constexpr int32_t zeroXCoordinate = 0;
constexpr int32_t zeroYCoordinate = 0;
constexpr auto vehicleId = 2;
}//namespace

DISABLED_HandlingUserCommandToRunTest::DISABLED_HandlingUserCommandToRunTest()
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
        , vehicleFactory(threeWheeledVehicleFactory)
        , vehiclePool(vehicleFactory)
        , vehiclePoolControler(commandReceiverMock, commandSenderMock, vehiclePool)
    {}

TEST_F(DISABLED_HandlingUserCommandToRunTest, ZeroZeroCoordinates)
{
    EXPECT_CALL(commandReceiverMock, takeMessageFromQueue()).Times(2)
            .WillOnce(Return(createUserCommandToRun(zeroXCoordinate, zeroYCoordinate, vehicleId)))
            .WillOnce(Return(createDeactivateCommand()));

    const PinsConfiguration expectedNewPinsConfiguration = {{PIN_NUMBERS::FIRST_ENGINE_FIRST_OUTPUT, 1},
                                                            {PIN_NUMBERS::FIRST_ENGINE_SECOND_OUTPUT, 1},
                                                            {PIN_NUMBERS::FIRST_ENGINE_PWM, 0},
                                                            {PIN_NUMBERS::SECOND_ENGINE_FIRST_OUTPUT, 1},
                                                            {PIN_NUMBERS::SECOND_ENGINE_SECOND_OUTPUT, 1},
                                                            {PIN_NUMBERS::SECOND_ENGINE_PWM, 0},
                                                            {PIN_NUMBERS::STEERING_WHEEL_PWM, 19}};

    auto expectedMessage = ControlerCommandToRunMessageBuilder{}.pinsConfiguration(expectedNewPinsConfiguration)
                                                                .build();

    EXPECT_CALL(commandSenderMock, sendCommand(std::move(expectedMessage)));

    vehiclePoolControler.controlVehiclePool();
}
