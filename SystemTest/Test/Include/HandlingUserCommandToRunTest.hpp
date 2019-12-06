#pragma once

#include <gmock/gmock.h>

#include "VehicleControler.hpp"
#include "SingleAxisPropulsionSystem.hpp"
#include "DcEngine.hpp"
#include "VehicleConfiguration.hpp"
#include "L293DEngineDriver.hpp"
#include "ThirtyDegreesSteeringWheel.hpp"
#include "FrontAxialSteeringSystem.hpp"
#include "ThreeWheeledVehicle.hpp"
#include "CommunicationSocketMock.hpp"

using namespace ::testing;

class HandlingUserCommandToRunTest : public Test
{
public:
    HandlingUserCommandToRunTest();

    NiceMock<CommunicationSocketMock> commandReceiverMock;

private:
    L293DEngineDriver engineDriver;
    DcEngine firstEngine;
    DcEngine secondEngine;
    SingleAxisPropulsionSystem propulsionSystem;
    ThirtyDegreesSteeringWheel steeringWheel;
    FrontAxialSteeringSystem steeringSystem;
    ThreeWheeledVehicle vehicle;

public:
    VehicleControler vehicleControler;
};
