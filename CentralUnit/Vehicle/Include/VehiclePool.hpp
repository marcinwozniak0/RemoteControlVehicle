#pragma once

#include <Vehicle.hpp>

class VehiclePool
{
public:
    virtual Vehicle& getVehicle(int vehicleId) = 0;
    virtual void addVehicle(int vehicleId) = 0;
    virtual bool isVehicleReqistered(int vehicleId) const = 0;
    virtual bool isVehicleInUse(int vehicleId) const = 0;

    virtual ~VehiclePool() = default;
};