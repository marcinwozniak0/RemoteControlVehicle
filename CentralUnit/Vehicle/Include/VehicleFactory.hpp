#pragma once

#include <memory>

#include <RegisterVehicle.pb.h>

#include "Vehicle.hpp" 

class VehicleFactory
{
public:
    virtual std::unique_ptr<Vehicle> create(Commands::RegisterVehicle&&) const = 0;

    virtual ~VehicleFactory() = default;
};