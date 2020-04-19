#pragma once

#include <gtest/gtest.h>
#include <memory>

#include "VehicleFactoryFacade.hpp"
#include "VehicleFactoryMock.hpp"


using namespace ::testing;

class VehicleFactoryFacadeTest : public Test
{
public:
    VehicleFactoryFacadeTest() 
        : _sut(_threeWheeledVehicleFactory)
    {}

    VehicleFactoryFacade _sut;

    NiceMock<VehicleFactoryMock> _threeWheeledVehicleFactory;
};