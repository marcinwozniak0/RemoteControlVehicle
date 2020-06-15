#include <google/protobuf/any.pb.h>

#include <Deactivate.pb.h>
#include <UserCommandToStop.pb.h>
#include <UserCommandToStart.pb.h>
#include <UserCommandToRun.pb.h>
#include <ControlerCommandToRun.pb.h>
#include <RegisterUserCommand.pb.h>
#include <Acknowledge.pb.h>

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
constexpr auto secondVehicleId = 2u;
constexpr auto unknownVehicleId = 22u;
const PinsConfiguration configuration = {{1, 1}, {2, 11}};
const PinsConfiguration zeroedConfiguration = {{1, 0}, {2, 0}};
}

TEST_F(VehiclePoolControlerTest, shouldStartVehicleAfterReceiveStartsCommand)
{
    EXPECT_CALL(*_vehicleMock, startVehicle());
    EXPECT_CALL(_commandReceiverMock, takeCommandToProcess()).Times(2)
            .WillOnce(Return(createUserCommandToStart(vehicleId)))
            .WillOnce(Return(createDeactivateCommand()));

    _sut.controlVehiclePool();
}

TEST_F(VehiclePoolControlerTest, shouldStopVehicleAfterReceiveStopsCommand)
{
    EXPECT_CALL(*_vehicleMock, stopVehicle());
    EXPECT_CALL(_commandReceiverMock, takeCommandToProcess()).Times(3)
            .WillOnce(Return(createUserCommandToStart(vehicleId)))
            .WillOnce(Return(createUserCommandToStop(vehicleId)))
            .WillOnce(Return(createDeactivateCommand()));

    _sut.controlVehiclePool();
}

TEST_F(VehiclePoolControlerTest, afterReceiveUserCommandToRunShouldApplyAndSendNewVehicleConfiguration)
{
    EXPECT_CALL(_commandReceiverMock, takeCommandToProcess()).Times(2)
            .WillOnce(Return(createUserCommandToRun(xCoordinate, yCoordinate, vehicleId)))
            .WillOnce(Return(createDeactivateCommand()));

    Commands::CoordinateSystem coordinates;
    coordinates.set_x_coordinate(xCoordinate);
    coordinates.set_y_coordinate(yCoordinate);

    auto messageToSend = ControlerCommandToRunMessageBuilder{}.pinsConfiguration(configuration)
                                                              .vehicleId(vehicleId)
                                                              .build();

    EXPECT_CALL(*_vehicleMock, applyNewConfiguration(coordinates));
    EXPECT_CALL(*_vehicleMock, getCurrentPinsConfiguration()).WillOnce(Return(configuration));
    EXPECT_CALL(_commandSenderMock, sendCommand(std::move(messageToSend)));

    _sut.controlVehiclePool();
}

TEST_F(VehiclePoolControlerTest, onEmergencyStopShouldSendCommandToRunWithZeroedPinsConfigurationForAllRentedVehicle)
{
    auto firstMessageToSend = ControlerCommandToRunMessageBuilder{}.pinsConfiguration(zeroedConfiguration)
                                                                   .vehicleId(vehicleId)
                                                                   .build();

    auto secondMessageToSend = ControlerCommandToRunMessageBuilder{}.pinsConfiguration(zeroedConfiguration)
                                                                    .vehicleId(secondVehicleId)
                                                                    .build();
    const std::vector<int> vehicleIds {vehicleId, secondVehicleId};  
    
    EXPECT_CALL(_vehiclePoolMock, getRentedVehicleIds()).WillOnce(ReturnRef(vehicleIds));

    EXPECT_CALL(_vehiclePoolMock, getVehicle(vehicleId)).WillOnce(Return(_vehicleMock));
    EXPECT_CALL(_vehiclePoolMock, getVehicle(secondVehicleId)).WillOnce(Return(_secondVehicleMock));

    EXPECT_CALL(*_vehicleMock, getCurrentPinsConfiguration()).WillOnce(Return(configuration));
    EXPECT_CALL(*_secondVehicleMock, getCurrentPinsConfiguration()).WillOnce(Return(configuration));

    Sequence s1;

    EXPECT_CALL(_commandSenderMock, sendCommand(std::move(firstMessageToSend))).InSequence(s1);
    EXPECT_CALL(_commandSenderMock, sendCommand(std::move(secondMessageToSend))).InSequence(s1);

    _sut.vehiclePoolEmergencyStop();
}

TEST_F(VehiclePoolControlerTest, onEmergencyStopShouldNotSendCommandToRunWhenVehicleWithGivenIdWasNotFound)
{ 
    const std::vector<int> vehicleIds {unknownVehicleId};  
    
    EXPECT_CALL(_vehiclePoolMock, getRentedVehicleIds()).WillOnce(ReturnRef(vehicleIds));
    EXPECT_CALL(_vehiclePoolMock, getVehicle(unknownVehicleId)).WillOnce(Return(std::nullopt));
    EXPECT_CALL(_commandSenderMock, sendCommand(_)).Times(0);

    _sut.vehiclePoolEmergencyStop();
}

TEST_F(VehiclePoolControlerTest, unknownCommandShouldBeIngored)
{
    EXPECT_CALL(_commandReceiverMock, takeCommandToProcess()).Times(2)
            .WillOnce(Return(createUnknownCommand()))
            .WillOnce(Return(createDeactivateCommand()));

    _sut.controlVehiclePool();
}

TEST_F(VehiclePoolControlerTest, registerVehicleCommandShouldTriggerVehicleRegistrationInVehiclePoolControler)
{
    Commands::RegisterVehicle registerVehicleCommand;
    const auto packedRegisterVehicleCommand = createRegisterVehicleCommand(vehicleId);
    packedRegisterVehicleCommand.UnpackTo(&registerVehicleCommand);

    EXPECT_CALL(_commandReceiverMock, takeCommandToProcess()).Times(2)
            .WillOnce(Return(packedRegisterVehicleCommand))
            .WillOnce(Return(createDeactivateCommand()));

    EXPECT_CALL(_vehiclePoolMock, registerVehicle(std::move(registerVehicleCommand)));


    _sut.controlVehiclePool();
}

TEST_F(VehiclePoolControlerTest, registerUserCommandShouldTriggerVehicleRentProcedureInVehiclePoolControler)
{
    Commands::RegisterUserCommand registerUserCommand;
    const auto packedRegisterUserCommand = createRegisterUserCommand(vehicleId);
    packedRegisterUserCommand.UnpackTo(&registerUserCommand);

    EXPECT_CALL(_commandReceiverMock, takeCommandToProcess()).Times(2)
            .WillOnce(Return(packedRegisterUserCommand))
            .WillOnce(Return(createDeactivateCommand()));

    EXPECT_CALL(_vehiclePoolMock, rentVehicle(vehicleId));

    _sut.controlVehiclePool();
}
