#pragma once

#include <RegisterVehicle.pb.h>

#include "VehicleFactory.hpp"

class ThreeWheeledVehicleFactory : public VehicleFactory
{
public:
    ThreeWheeledVehicleFactory(Commands::RegisterVehicle&&);

    std::unique_ptr<Vehicle> create() const override;

private:
    Commands::RegisterVehicle _registerVehicleCommand;
};