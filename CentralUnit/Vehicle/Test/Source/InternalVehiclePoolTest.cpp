#include "InternalVehiclePoolTest.hpp"

namespace
{
constexpr auto firstVehicleId = 14;
constexpr auto secondVehicleId = 2;

Commands::RegisterVehicle createRegisterVehicleCommand(const int vehicleId = firstVehicleId)
{
    Commands::RegisterVehicle registerVehicleCommand;

    registerVehicleCommand.set_vehicle_id(vehicleId);

    return registerVehicleCommand;
}
}

void InternalVehiclePoolTest::registerVehicle(Commands::RegisterVehicle&& registerVehicleCommand)
{
    _sut.registerVehicle(std::move(registerVehicleCommand));
}

void InternalVehiclePoolTest::rentVehicle(const int vehicleId)
{
    _sut.rentVehicle(vehicleId);    
}

TEST_F(InternalVehiclePoolTest, registerVehicleShouldReturnTrueWhenVehicleIdWasNotFoundInRegisteredVehicles)
{
    ASSERT_TRUE(_sut.registerVehicle(createRegisterVehicleCommand()));
}

TEST_F(InternalVehiclePoolTest, registerVehicleShouldReturnFalseWhenVehicleIdWasFoundInRegisteredVehicles)
{
    registerVehicle(createRegisterVehicleCommand());

    ASSERT_FALSE(_sut.registerVehicle(createRegisterVehicleCommand()));
}

TEST_F(InternalVehiclePoolTest, registerVehicleShouldReturnFalseWhenVehicleObjectWasNotCreated)
{
    EXPECT_CALL(_vehicleFactoryMock, create(_)).WillRepeatedly(Return(ByMove(nullptr)));

    ASSERT_FALSE(_sut.registerVehicle(createRegisterVehicleCommand()));
}

TEST_F(InternalVehiclePoolTest, registerVehicleShouldReturnTrueIfPreviousRegisterAttemptWasFailedDueToIncorrectVehicleObjectCreation)
{
    EXPECT_CALL(_vehicleFactoryMock, create(_)).WillOnce(Return(ByMove(nullptr)));

    ASSERT_FALSE(_sut.registerVehicle(createRegisterVehicleCommand()));

    EXPECT_CALL(_vehicleFactoryMock, create(_)).WillOnce(Return(ByMove(std::make_unique<ThreeWheeledVehicle>(_propulsionSystemMock, _steeringSystemMock))));

    ASSERT_TRUE(_sut.registerVehicle(createRegisterVehicleCommand()));
}

TEST_F(InternalVehiclePoolTest, rentVehicleShouldReturnTrueWhenVehicleIdWasFoundInRegisteredVehiclesAndWasNotFoundInRentedVehicles)
{
    registerVehicle(createRegisterVehicleCommand());
    
    ASSERT_TRUE(_sut.rentVehicle(firstVehicleId));
}

TEST_F(InternalVehiclePoolTest, rentVehicleShouldReturnFalseWhenVehicleIdWasFoundInRegisteredVehiclesAndInRentedVehicles)
{
    registerVehicle(createRegisterVehicleCommand());
    rentVehicle(firstVehicleId);
    
    ASSERT_FALSE(_sut.rentVehicle(firstVehicleId));
}

TEST_F(InternalVehiclePoolTest, rentVehicleShouldReturnFalseWhenVehicleIdWasNotFoundInRegisteredVehicles)
{    
    ASSERT_FALSE(_sut.rentVehicle(firstVehicleId));
}

TEST_F(InternalVehiclePoolTest, getVehicleShouldReturnNulloptWhenVehicleIdWasNotFoundInRentedVehicles)
{   
    registerVehicle(createRegisterVehicleCommand());

    ASSERT_EQ(std::nullopt, _sut.getVehicle(firstVehicleId));
}

TEST_F(InternalVehiclePoolTest, getVehicleShouldReturnNulloptWhenVehicleIdWasNotFoundInRegisteredVehicles)
{   
    registerVehicle(createRegisterVehicleCommand());
    rentVehicle(firstVehicleId);

    ASSERT_EQ(std::nullopt, _sut.getVehicle(secondVehicleId));
}

TEST_F(InternalVehiclePoolTest, getVehicleShouldReturnVehicleWhenVehicleIdWasFoundInRentedAndRegisteredVehicles)
{   
    registerVehicle(createRegisterVehicleCommand());
    rentVehicle(firstVehicleId);

    ASSERT_NE(nullptr, _sut.getVehicle(firstVehicleId).value());
}
