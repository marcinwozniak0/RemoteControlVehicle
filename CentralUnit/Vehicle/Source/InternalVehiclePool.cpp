#include <algorithm>

#include "InternalVehiclePool.hpp"

Vehicle& InternalVehiclePool::getVehicle(int vehicleId)
{
    //findIndexById
    return *_vehiclePool.at(vehicleId);
}

void InternalVehiclePool::addVehicle(int vehicleId)
{
    _registeredVehicles.push_back(vehicleId);
}

bool InternalVehiclePool::isVehicleReqistered(int vehicleId) const
{
    return std::any_of(_registeredVehicles.begin(),
                        _registeredVehicles.end(),
                        [vehicleId](const auto elem){return elem == vehicleId;});
}

bool InternalVehiclePool::isVehicleInUse(int vehicleId) const
{
    return std::any_of(_vehiclesInUse.begin(),
                        _vehiclesInUse.end(),
                        [vehicleId](const auto elem){return elem == vehicleId;});
}