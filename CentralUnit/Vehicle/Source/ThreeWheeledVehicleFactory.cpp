#include <ThreeWheeledVehicleConfiguration.pb.h>

#include "ThreeWheeledVehicleFactory.hpp"
#include "SingleAxisPropulsionSystem.hpp"
#include "DcEngine.hpp"
#include "L293DEngineDriver.hpp"
#include "ThirtyDegreesSteeringWheel.hpp"
#include "FrontAxialSteeringSystem.hpp"
#include "ThreeWheeledVehicle.hpp"
#include "InternalVehiclePool.hpp"

namespace
{
constexpr auto UNINITIALIZED = 0u;

bool isAllFieldInitilized(const ThreeWheeledVehicleConfiguration& vehicleConfiguration)
{
    return vehicleConfiguration.first_engine_first_output() not_eq UNINITIALIZED and
           vehicleConfiguration.first_engine_second_output() not_eq UNINITIALIZED and
           vehicleConfiguration.first_engine_pwm() not_eq UNINITIALIZED and
           vehicleConfiguration.second_engine_first_output() not_eq UNINITIALIZED and
           vehicleConfiguration.second_engine_second_output() not_eq UNINITIALIZED and
           vehicleConfiguration.second_engine_pwm() not_eq UNINITIALIZED and
           vehicleConfiguration.steering_wheel_pwm_range() not_eq UNINITIALIZED and
           vehicleConfiguration.engines_pwm_range() not_eq UNINITIALIZED;
}    
}
std::unique_ptr<Vehicle> ThreeWheeledVehicleFactory::create(Commands::RegisterVehicle&& registerVehicleCommand) const
{
    ThreeWheeledVehicleConfiguration vehicleConfiguration;
    registerVehicleCommand.vehicle_configuration().UnpackTo(&vehicleConfiguration);
    
    if (not isAllFieldInitilized(vehicleConfiguration))
    {
        return {};
    }

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