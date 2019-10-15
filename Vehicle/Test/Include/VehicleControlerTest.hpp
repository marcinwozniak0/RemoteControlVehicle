#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "VehicleControler.hpp"
#include "MessageReceiverMock.hpp"
#include "PropulsionSystemMock.hpp"
#include "SteeringSystemMock.hpp"
#include "PinValueSetterMock.hpp"
#include "VehicleMock.hpp"

using namespace ::testing;

class VehicleControlerTest : public Test
{
public:
    VehicleControlerTest()
        : _sut(_messageReceiverMock, _vehicleMock, _pinValueSetterMock)
    {}

    VehicleControler _sut;

    NiceMock<MessageReceiverMock> _messageReceiverMock;
    NiceMock<VehicleMock> _vehicleMock;
    NiceMock<PropulsionSystemMock> _propulsionSystemMock;
    NiceMock<SteeringSystemMock> _steeringSystemMock;
    NiceMock<PinValueSetterMock> _pinValueSetterMock;
};

