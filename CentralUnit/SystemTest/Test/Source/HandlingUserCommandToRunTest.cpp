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
constexpr auto vehicleId = 2u;
constexpr auto firstEngineFirstInput = 10u;
constexpr auto firstEngineSecondInput = 11u;
constexpr auto firstEnginePwm = 12u;
constexpr auto secondEngineFirstInput = 13u;
constexpr auto secondEngineSecondInput = 14u;
constexpr auto secondEnginePwm = 15u;
constexpr auto steeringWheelPwm = 16u;
constexpr auto pwmRange = 255u;
}//namespace

DISABLED_HandlingUserCommandToRunTest::DISABLED_HandlingUserCommandToRunTest()
        : firstEngine(firstEngineFirstInput,
                      firstEngineSecondInput,
                      firstEnginePwm)
        , secondEngine(secondEngineFirstInput,
                       secondEngineSecondInput,
                       secondEnginePwm)
        , engineDriver(pwmRange)
        , propulsionSystem(firstEngine, secondEngine, engineDriver)
        , steeringWheel(steeringWheelPwm)
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

    const PinsConfiguration expectedNewPinsConfiguration = {{firstEngineFirstInput, 1},
                                                            {firstEngineSecondInput, 1},
                                                            {firstEnginePwm, 0},
                                                            {secondEngineFirstInput, 1},
                                                            {secondEngineSecondInput, 1},
                                                            {secondEnginePwm, 0},
                                                            {steeringWheelPwm, 19}};

    auto expectedMessage = ControlerCommandToRunMessageBuilder{}.pinsConfiguration(expectedNewPinsConfiguration)
                                                                .build();

    EXPECT_CALL(commandSenderMock, sendCommand(std::move(expectedMessage)));

    vehiclePoolControler.controlVehiclePool();
}
