#pragma once

#include <vector>
#include <memory>

#include "VehiclePool.hpp"

class InternalVehiclePool : public VehiclePool
{
public:
    Vehicle& getVehicle(int vehicleId) override;
    void addVehicle(int vehicleId) override;
    bool isVehicleReqistered(int vehicleId) const override;
    bool isVehicleInUse(int vehicleId) const override;

private:
    std::vector<std::unique_ptr<Vehicle>> _vehiclePool;
    std::vector<int> _registeredVehicles;
    std::vector<int> _vehiclesInUse;
};