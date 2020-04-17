#include <Deactivate.pb.h>
#include <UserCommandToStop.pb.h>
#include <UserCommandToStart.pb.h>
#include <UserCommandToRun.pb.h>
#include <ControlerCommandToRun.pb.h>
#include <RegisterUserCommand.pb.h>

#include "VehiclePoolControlerTest.hpp"
#include "ControlerCommandToRunMessageBuilder.hpp"
#include "ProtobufStructuresComparators.hpp"
#include "UtCommandsBuilders.hpp"

using namespace Comparators;
using namespace UTHelpers;

namespace
{
constexpr int32_t xCoordinate = 700;
constexpr int32_t yCoordinate = 5500;
constexpr auto vehicleId = 14u;
const PinsConfiguration configuration = {{1, 1}, {2, 11}};
const PinsConfiguration zeroedConfiguration = {{1, 0}, {2, 0}};
}

TEST_F(VehicleControlerTest, shouldStartVehicleAfterReceiveStartsCommand)
{
    EXPECT_CALL(*_vehicleMock, startVehicle());
    EXPECT_CALL(_commandReceiverMock, takeMessageFromQueue()).Times(2)
            .WillOnce(Return(createUserCommandToStart(vehicleId)))
            .WillOnce(Return(createDeactivateCommand()));

    _sut.controlVehiclePool();
}

TEST_F(VehicleControlerTest, shouldStopVehicleAfterReceiveStopsCommand)
{
    EXPECT_CALL(*_vehicleMock, stopVehicle());
    EXPECT_CALL(_commandReceiverMock, takeMessageFromQueue()).Times(3)
            .WillOnce(Return(createUserCommandToStart(vehicleId)))
            .WillOnce(Return(createUserCommandToStop(vehicleId)))
            .WillOnce(Return(createDeactivateCommand()));

    _sut.controlVehiclePool();
}

TEST_F(VehicleControlerTest, afterReceiveUserCommandToRunShouldApplyAndSendNewVehicleConfiguration)
{
    EXPECT_CALL(_commandReceiverMock, takeMessageFromQueue()).Times(2)
            .WillOnce(Return(createUserCommandToRun(xCoordinate, yCoordinate, vehicleId)))
            .WillOnce(Return(createDeactivateCommand()));

    Commands::CoordinateSystem coordinates;
    coordinates.set_x_coordinate(xCoordinate);
    coordinates.set_y_coordinate(yCoordinate);

    auto messageToSend = ControlerCommandToRunMessageBuilder{}.pinsConfiguration(configuration)
                                                              .build();

    EXPECT_CALL(*_vehicleMock, applyNewConfiguration(coordinates));
    EXPECT_CALL(*_vehicleMock, getCurrentPinsConfiguration()).WillOnce(Return(configuration));
    EXPECT_CALL(_commandSenderMock, sendCommand(std::move(messageToSend)));

    _sut.controlVehiclePool();
}

TEST_F(VehicleControlerTest, onEmergencyStopShouldSendCommandToRunWithZeroedPinsConfiguration)
{
    auto messageToSend = ControlerCommandToRunMessageBuilder{}.pinsConfiguration(zeroedConfiguration)
                                                              .build();
    EXPECT_CALL(*_vehicleMock, getCurrentPinsConfiguration()).WillOnce(Return(configuration));

    EXPECT_CALL(_commandSenderMock, sendCommand(std::move(messageToSend)));

    _sut.vehicleEmergencyStop();
}

TEST_F(VehicleControlerTest, unknownCommandShouldBeIngored)
{
    EXPECT_CALL(_commandReceiverMock, takeMessageFromQueue()).Times(2)
            .WillOnce(Return(createUnknownCommand()))
            .WillOnce(Return(createDeactivateCommand()));

    _sut.controlVehiclePool();
}

TEST_F(VehicleControlerTest, registerVehicleCommandShouldTriggerVehicleRegistrationInVehiclePoolControler)
{
    Commands::RegisterVehicle registerVehicleCommand;
    const auto packedRegisterVehicleCommand = createRegisterVehicleCommand(vehicleId);
    packedRegisterVehicleCommand.UnpackTo(&registerVehicleCommand);

    EXPECT_CALL(_commandReceiverMock, takeMessageFromQueue()).Times(2)
            .WillOnce(Return(packedRegisterVehicleCommand))
            .WillOnce(Return(createDeactivateCommand()));

    EXPECT_CALL(_vehiclePoolMock, registerVehicle(std::move(registerVehicleCommand)));


    _sut.controlVehiclePool();
}

TEST_F(VehicleControlerTest, registerUserCommandShouldTriggerVehicleRentProcedureInVehiclePoolControler)
{
    Commands::RegisterUserCommand registerUserCommand;
    const auto packedRegisterUserCommand = createRegisterUserCommand(vehicleId);
    packedRegisterUserCommand.UnpackTo(&registerUserCommand);

    EXPECT_CALL(_commandReceiverMock, takeMessageFromQueue()).Times(2)
            .WillOnce(Return(packedRegisterUserCommand))
            .WillOnce(Return(createDeactivateCommand()));

    EXPECT_CALL(_vehiclePoolMock, rentVehicle(vehicleId));

    _sut.controlVehiclePool();
}