#include <memory>

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
    //TODO fold expresion ?
    return vehicleConfiguration.first_engine_first_output() not_eq UNINITIALIZED and
           vehicleConfiguration.first_engine_second_output() not_eq UNINITIALIZED and
           vehicleConfiguration.first_engine_pwm() not_eq UNINITIALIZED and
           vehicleConfiguration.second_engine_first_output() not_eq UNINITIALIZED and
           vehicleConfiguration.second_engine_second_output() not_eq UNINITIALIZED and
           vehicleConfiguration.second_engine_pwm() not_eq UNINITIALIZED and
           vehicleConfiguration.steering_wheel_pwm() not_eq UNINITIALIZED and
           vehicleConfiguration.steering_wheel_pwm_range() not_eq UNINITIALIZED and
           vehicleConfiguration.engines_pwm_range() not_eq UNINITIALIZED;
}    
}//namespace

std::unique_ptr<Vehicle> ThreeWheeledVehicleFactory::create(Commands::RegisterVehicle&& registerVehicleCommand) const
{
    ThreeWheeledVehicleConfiguration vehicleConfiguration;
    registerVehicleCommand.vehicle_configuration().UnpackTo(&vehicleConfiguration);
    
    if (not isAllFieldInitilized(vehicleConfiguration))
    {
        return {};
    }
    auto engineDriver = std::make_unique<L293DEngineDriver>(vehicleConfiguration.engines_pwm_range());
    auto firstEngine = std::make_unique<DcEngine>(vehicleConfiguration.first_engine_first_output(),
                                                  vehicleConfiguration.first_engine_second_output(),
                                                  vehicleConfiguration.first_engine_pwm());
    auto secondEngine = std::make_unique<DcEngine>(vehicleConfiguration.second_engine_first_output(),
                                                   vehicleConfiguration.second_engine_second_output(),
                                                   vehicleConfiguration.second_engine_pwm());
    auto propulsionSystem = std::make_unique<SingleAxisPropulsionSystem>(std::move(firstEngine),
                                                                         std::move(secondEngine),
                                                                         std::move(engineDriver));
    auto steeringWheel = std::make_unique<ThirtyDegreesSteeringWheel>(vehicleConfiguration.steering_wheel_pwm());
    auto steeringSystem = std::make_unique<FrontAxialSteeringSystem>(std::move(steeringWheel));

    return std::make_unique<ThreeWheeledVehicle>(std::move(propulsionSystem), std::move(steeringSystem));
}
