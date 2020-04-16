#pragma once

#include <gmock/gmock.h>

#include "VehiclePoolControler.hpp"
#include "SingleAxisPropulsionSystem.hpp"
#include "DcEngine.hpp"
#include "VehicleConfiguration.hpp"
#include "L293DEngineDriver.hpp"
#include "ThirtyDegreesSteeringWheel.hpp"
#include "FrontAxialSteeringSystem.hpp"
#include "ThreeWheeledVehicle.hpp"
#include "InternalVehiclePool.hpp"
#include "CommandSenderMock.hpp"
#include "CommandReceiverMock.hpp"

using namespace ::testing;

class DISABLED_HandlingUserCommandToRunTest : public Test
{
public:
    DISABLED_HandlingUserCommandToRunTest();

    NiceMock<CommandSenderMock> commandSenderMock;
    NiceMock<CommandReceiverMock> commandReceiverMock;

private:
    L293DEngineDriver engineDriver;
    DcEngine firstEngine;
    DcEngine secondEngine;
    SingleAxisPropulsionSystem propulsionSystem;
    ThirtyDegreesSteeringWheel steeringWheel;
    FrontAxialSteeringSystem steeringSystem;
    ThreeWheeledVehicle vehicle;
    InternalVehiclePool vehiclePool;

public:
    VehiclePoolControler vehiclePoolControler;
};
