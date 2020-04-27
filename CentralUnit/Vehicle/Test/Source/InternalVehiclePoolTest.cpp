#include "RegisterVehicle.pb.h"

#include "InternalVehiclePoolTest.hpp"
#include "ThreeWheeledVehicleFactory.hpp"
#include "UtCommandsBuilders.hpp"

namespace
{
constexpr auto firstVehicleId = 14u;
constexpr auto secondVehicleId = 2u;

Commands::RegisterVehicle createRegisterVehicleCommand(const int vehicleId = firstVehicleId)
{
    auto packedCommand = UTHelpers::createRegisterVehicleCommand(vehicleId);

    Commands::RegisterVehicle registerVehicleCommand;
    packedCommand.UnpackTo(&registerVehicleCommand);

    return registerVehicleCommand;
}

auto createThreeWheeledVehicle(int vehicleId = firstVehicleId)
{
    ThreeWheeledVehicleFactory factory;
    return factory.create(createRegisterVehicleCommand(vehicleId));
}
}//namespace

InternalVehiclePoolTest::InternalVehiclePoolTest()
    : _sut(_vehicleFactoryMock)
{
    ON_CALL(_vehicleFactoryMock, create(_)).WillByDefault(Return(ByMove(createThreeWheeledVehicle())));
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

    EXPECT_CALL(_vehicleFactoryMock, create(_)).WillOnce(Return(ByMove(createThreeWheeledVehicle(secondVehicleId))));

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
