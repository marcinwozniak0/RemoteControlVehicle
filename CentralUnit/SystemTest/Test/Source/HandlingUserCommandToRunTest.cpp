#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Deactivate.pb.h>
#include <UserCommandToRun.pb.h>
#include <Acknowledge.pb.h>

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
constexpr auto firstEngineFirstInput = 1u;
constexpr auto firstEngineSecondInput = 2u;
constexpr auto firstEnginePwm = 3u;
constexpr auto secondEngineFirstInput = 4u;
constexpr auto secondEngineSecondInput = 5u;
constexpr auto secondEnginePwm = 6u;
constexpr auto steeringWheelPwm = 7u;
constexpr auto pwmRange = 255u;
}//namespace

HandlingUserCommandToRunTest::HandlingUserCommandToRunTest()
        : firstEngine(firstEngineFirstInput,
                      firstEngineSecondInput,
                      firstEnginePwm)
        , secondEngine(secondEngineFirstInput,
                       secondEngineSecondInput,
                       secondEnginePwm)
        , engineDriver(pwmRange)
        , propulsionSystem(std::make_unique<DcEngine>(firstEngine),
                           std::make_unique<DcEngine>(secondEngine),
                           std::make_unique<L293DEngineDriver>(engineDriver))
        , steeringWheel(steeringWheelPwm)
        , steeringSystem(std::make_unique<ThirtyDegreesSteeringWheel>(steeringWheel))
        , vehicle(std::make_unique<SingleAxisPropulsionSystem>(std::move(propulsionSystem)),
                  std::make_unique<FrontAxialSteeringSystem>(std::move(steeringSystem)))
        , vehicleFactory(threeWheeledVehicleFactory)
        , vehiclePool(vehicleFactory)
        , vehiclePoolControler(commandReceiverMock, commandSenderMock, vehiclePool)
    {}

TEST_F(HandlingUserCommandToRunTest, ZeroZeroCoordinates)
{
    EXPECT_CALL(commandReceiverMock, takeCommandToProcess()).Times(4)
            .WillOnce(Return(createRegisterVehicleCommand(vehicleId)))
            .WillOnce(Return(createRegisterUserCommand(vehicleId)))
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
