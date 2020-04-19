#pragma once

#include "VehicleFactory.hpp"

class ThreeWheeledVehicleFactory : public VehicleFactory
{
public:
    std::unique_ptr<Vehicle> create(Commands::RegisterVehicle&&) const override;
};