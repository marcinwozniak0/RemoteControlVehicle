#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "VehicleControler.hpp"
#include "CommunicationSocketMock.hpp"
#include "PropulsionSystemMock.hpp"
#include "SteeringSystemMock.hpp"
#include "PinValueSetterMock.hpp"
#include "VehicleMock.hpp"

using namespace ::testing;

class VehicleControlerTest : public Test
{
public:
    VehicleControlerTest()
        : _sut(_communicationSocketMock, _vehicleMock)
    {}

    VehicleControler _sut;

    NiceMock<CommunicationSocketMock> _communicationSocketMock;
    NiceMock<VehicleMock> _vehicleMock;
    NiceMock<PropulsionSystemMock> _propulsionSystemMock;
    NiceMock<SteeringSystemMock> _steeringSystemMock;
};

