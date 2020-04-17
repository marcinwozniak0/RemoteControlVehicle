#include <VehicleType.pb.h>

#include "VehicleFactoryFacade.hpp" 
 
VehicleFactoryFacade::VehicleFactoryFacade(const VehicleFactory& threeWheeledVehicleFactory)
    : _threeWheeledVehicleFactory(threeWheeledVehicleFactory)
{}

std::unique_ptr<Vehicle> VehicleFactoryFacade::create(Commands::RegisterVehicle&& registerVehicleCommand) const
{
    if (Commands::VehicleType::THREE_WHEELED == registerVehicleCommand.vehicle_type())
    {
        return _threeWheeledVehicleFactory.create(std::move(registerVehicleCommand));
    }  

    return {};     
}