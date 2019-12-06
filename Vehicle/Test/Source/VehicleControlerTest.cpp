#include <Deactivate.pb.h>
#include <UserCommandToStop.pb.h>
#include <UserCommandToStart.pb.h>
#include <UserCommandToRun.pb.h>
#include <ControlerCommandToRun.pb.h>

#include "VehicleControlerTest.hpp"
#include "ControlerCommandToRunMessageBuilder.hpp"
#include "SerializedCommandsMatchers.hpp"
#include "ProtobufStructuresComparators.hpp"
#include "SerializedCommandsBuilders.hpp"

using namespace Comparators;
using namespace UTHelpers;

namespace
{
constexpr int32_t xCoordinate = 700;
constexpr int32_t yCoordinate = 5500;
}

TEST_F(VehicleControlerTest, shouldStartVehicleAfterReceiveStartsCommand)
{
    EXPECT_CALL(_vehicleMock, startVehicle());
    EXPECT_CALL(_communicationSocketMock, takeMessageFromQueue()).Times(2)
            .WillOnce(Return(createSerializedUserCommandToStart()))
            .WillOnce(Return(createSerializedDeactivateMessage()));

    _sut.controlVehicle();
}

TEST_F(VehicleControlerTest, shouldStopVehicleAfterReceiveStopsCommand)
{
    EXPECT_CALL(_vehicleMock, stopVehicle());
    EXPECT_CALL(_communicationSocketMock, takeMessageFromQueue()).Times(3)
            .WillOnce(Return(createSerializedUserCommandToStart()))
            .WillOnce(Return(createSerializedUserCommandToStop()))
            .WillOnce(Return(createSerializedDeactivateMessage()));

    _sut.controlVehicle();
}

TEST_F(VehicleControlerTest, afterReceiveUserCommandToRunShouldApplyAndSendNewVehicleConfiguration)
{
    EXPECT_CALL(_communicationSocketMock, takeMessageFromQueue()).Times(2)
            .WillOnce(Return(createSerializedUserCommandToRun(xCoordinate, yCoordinate)))
            .WillOnce(Return(createSerializedDeactivateMessage()));

    Messages::CoordinateSystem coordinates;
    coordinates.set_x_coordinate(xCoordinate);
    coordinates.set_y_coordinate(yCoordinate);

    PinsConfiguration configuration = {{1, 1}, {2, 0}};
    auto messageToSend = ControlerCommandToRunMessageBuilder{}.pinsConfiguration(configuration)
                                                              .build();
    std::string serializedMessage;
    messageToSend.SerializeToString(&serializedMessage);

    EXPECT_CALL(_vehicleMock, applyNewConfiguration(coordinates));
    EXPECT_CALL(_vehicleMock, getCurrentPinsConfiguration()).WillOnce(Return(configuration));
    EXPECT_CALL(_communicationSocketMock, sendCommand(SerializedControlerCommandToRunMatcher(serializedMessage)));

    _sut.controlVehicle();

}
