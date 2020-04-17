#include <ThreeWheeledVehicleConfiguration.pb.h>

#include "ThreeWheeledVehicleFactory.hpp"
#include "SingleAxisPropulsionSystem.hpp"
#include "DcEngine.hpp"
#include "L293DEngineDriver.hpp"
#include "ThirtyDegreesSteeringWheel.hpp"
#include "FrontAxialSteeringSystem.hpp"
#include "ThreeWheeledVehicle.hpp"
#include "InternalVehiclePool.hpp"

ThreeWheeledVehicleFactory::ThreeWheeledVehicleFactory(Commands::RegisterVehicle&& registerVehicleCommand)
    : _registerVehicleCommand(std::move(registerVehicleCommand))
{}

std::unique_ptr<Vehicle> ThreeWheeledVehicleFactory::create() const
{

    //TODO check vehicle type
    //fasade - one main facotry
    ThreeWheeledVehicleConfiguration vehicleConfiguration;
    _registerVehicleCommand.vehicle_configuration().UnpackTo(&vehicleConfiguration);


    L293DEngineDriver engineDriver;
    DcEngine firstEngine(vehicleConfiguration.first_engine_first_output(),
                         vehicleConfiguration.first_engine_second_output(),
                         vehicleConfiguration.first_engine_pwm());
    DcEngine secondEngine(vehicleConfiguration.second_engine_first_output(),
                          vehicleConfiguration.second_engine_second_output(),
                          vehicleConfiguration.second_engine_pwm());
    SingleAxisPropulsionSystem propulsionSystem(firstEngine,
                                                secondEngine,
                                                engineDriver);
    ThirtyDegreesSteeringWheel steeringWheel(vehicleConfiguration.steering_wheel_pwm());
    FrontAxialSteeringSystem steeringSystem(steeringWheel);

    return std::make_unique<ThreeWheeledVehicle>(propulsionSystem, steeringSystem);
}