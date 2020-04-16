#include "InternalVehiclePoolTest.hpp"

namespace
{
constexpr auto firstVehicleId = 14;
constexpr auto secondVehicleId = 2;
}

TEST_F(InternalVehiclePoolTest, registerVehicleShouldReturnTrueWhenVehicleIdWasNotFoundInRegisteredVehicles)
{
    ASSERT_TRUE(_sut.registerVehicle(firstVehicleId));
}

TEST_F(InternalVehiclePoolTest, registerVehicleShouldReturnFalseWhenVehicleIdWasFoundInRegisteredVehicles)
{
    registerVehicle(firstVehicleId);

    ASSERT_FALSE(_sut.registerVehicle(firstVehicleId));
}

TEST_F(InternalVehiclePoolTest, rentVehicleShouldReturnTrueWhenVehicleIdWasFoundInRegisteredVehiclesAndWasNotFoundInRentedVehicles)
{
    registerVehicle(firstVehicleId);
    
    ASSERT_TRUE(_sut.rentVehicle(firstVehicleId));
}

TEST_F(InternalVehiclePoolTest, rentVehicleShouldReturnFalseWhenVehicleIdWasFoundInRegisteredVehiclesAndInRentedVehicles)
{
    registerVehicle(firstVehicleId);
    rentVehicle(firstVehicleId);
    
    ASSERT_FALSE(_sut.rentVehicle(firstVehicleId));
}

TEST_F(InternalVehiclePoolTest, rentVehicleShouldReturnFalseWhenVehicleIdWasNotFoundInRegisteredVehicles)
{    
    ASSERT_FALSE(_sut.rentVehicle(firstVehicleId));
}

TEST_F(InternalVehiclePoolTest, getVehicleShouldReturnNulloptWhenVehicleIdWasNotFoundInRentedVehicles)
{   
    registerVehicle(firstVehicleId);

    ASSERT_EQ(std::nullopt, _sut.getVehicle(firstVehicleId));
}

TEST_F(InternalVehiclePoolTest, getVehicleShouldReturnNulloptWhenVehicleIdWasNotFoundInRegisteredVehicles)
{   
    registerVehicle(firstVehicleId);
    rentVehicle(firstVehicleId);

    ASSERT_EQ(std::nullopt, _sut.getVehicle(secondVehicleId));
}

TEST_F(InternalVehiclePoolTest, getVehicleShouldReturnVehicleWhenVehicleIdWasFoundInRentedAndRegisteredVehicles)
{   
    registerVehicle(firstVehicleId);
    rentVehicle(firstVehicleId);

    ASSERT_NE(nullptr, _sut.getVehicle(firstVehicleId).value());
}
