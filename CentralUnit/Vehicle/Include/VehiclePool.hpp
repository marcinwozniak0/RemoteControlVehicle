#pragma once

#include <memory>

#include <RegisterVehicle.pb.h>

#include "Vehicle.hpp"

class VehiclePool
{
public:
    virtual std::optional<std::shared_ptr<Vehicle>> getVehicle(int vehicleId) = 0;
    virtual bool rentVehicle(int vehicleId) = 0;
    virtual bool registerVehicle(Commands::RegisterVehicle&&) = 0;
    
    virtual ~VehiclePool() = default;
};