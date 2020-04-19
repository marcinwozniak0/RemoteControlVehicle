#include <RegisterVehicle.pb.h>
#include <ThreeWheeledVehicleConfiguration.pb.h>
#include <google/protobuf/any.h>

#include "ThreeWheeledVehicleFactoryTest.hpp"

namespace
{
constexpr auto initialized = 11u;
    
Commands::RegisterVehicle createRegisterVehicleCommandWithInitializedConfiguration()
{   
    ThreeWheeledVehicleConfiguration configuration;
    configuration.set_first_engine_first_output(initialized); 
    configuration.set_first_engine_second_output(initialized);
    configuration.set_first_engine_pwm(initialized);
    configuration.set_second_engine_first_output(initialized);
    configuration.set_second_engine_second_output(initialized);
    configuration.set_second_engine_pwm(initialized);
    configuration.set_steering_wheel_pwm_range(initialized);
    configuration.set_engines_pwm_range(initialized);

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
