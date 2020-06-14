#include <RegisterVehicle.pb.h>
#include <ThreeWheeledVehicleConfiguration.pb.h>
#include <google/protobuf/any.h>

#include "ThreeWheeledVehicleFactoryTest.hpp"
#include "UtCommandsBuilders.hpp"

namespace
{
constexpr auto initialized = 11u;
    
Commands::RegisterVehicle createRegisterVehicleCommandWithInitializedConfiguration()
{   
    auto configuration = UTHelpers::createThreeWheeledVehicleConfiguration();

    google::protobuf::Any packedConfiguration;
    packedConfiguration.PackFrom(configuration);
    
    Commands::RegisterVehicle registerVehicleCommand;
    *registerVehicleCommand.mutable_vehicle_configuration() = packedConfiguration;

    return registerVehicleCommand;
}
}

TEST_F(ThreeWheeledVehicleFactoryTest, createShouldReturnNullptrWhenOneOfConfigurationFieldIsNotInitialized)
{
    Commands::RegisterVehicle configurationWithUninitializedFields{};

    ASSERT_EQ(_sut.create(std::move(configurationWithUninitializedFields)), nullptr);
}

TEST_F(ThreeWheeledVehicleFactoryTest, shouldCreateVehicleIfAllConfigurationFieldsAreInitialized)
{
    auto initializedConfiguration = createRegisterVehicleCommandWithInitializedConfiguration();

    ASSERT_NE(_sut.create(std::move(initializedConfiguration)), nullptr);
}
