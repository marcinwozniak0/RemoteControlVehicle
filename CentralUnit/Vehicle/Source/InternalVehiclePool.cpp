#include <algorithm>

#include "InternalVehiclePool.hpp"
#include "Logger.hpp"

std::optional<std::shared_ptr<Vehicle>> InternalVehiclePool::getVehicle(int vehicleId)
{
    if (const auto vehicleIndex = getVehicleIndex(vehicleId); vehicleIndex.has_value() and isVehicleRented(vehicleId))
    {
        return _vehiclePool.at(vehicleIndex.value());
    }
    else
    {
         return {};
    }
}

std::optional<int> InternalVehiclePool::getVehicleIndex(const int vehicleId) const
{
    const auto it = std::find(_registeredVehicles.begin(),
                              _registeredVehicles.end(),
                              vehicleId);

    if (_registeredVehicles.end() == it)
    {
        WARNING("Cannot find vehicle with id = " + std::to_string(vehicleId)); 
        return {};  
    }
    else
    {
        return std::distance(_registeredVehicles.begin(), it);           
    }                           
}

bool InternalVehiclePool::rentVehicle(int vehicleId)
{
    if (isPossibleToAddNewVehicle(vehicleId))
    {
        _rentedVehicles.push_back(vehicleId);
        return true;
    }
    else
    {
        WARNING("Cannot rent vehicle with id = " + std::to_string(vehicleId));
        return false;
    }
}

bool InternalVehiclePool::registerVehicle(int vehicleId)
{
    if (not isVehicleReqistered(vehicleId))
    {
        _registeredVehicles.push_back(vehicleId);
        //TODO _vehiclePool.push_back(Vehicle)
        return true;
    }
    else
    {
        WARNING("Cannot register vehicle with id = " + std::to_string(vehicleId));
        return false;
    }
}

bool InternalVehiclePool::isPossibleToAddNewVehicle(int vehicleId) const
{
    return isVehicleReqistered(vehicleId) and not isVehicleRented(vehicleId);
}

bool InternalVehiclePool::isVehicleReqistered(int vehicleId) const
{
    return std::any_of(_registeredVehicles.begin(),
                        _registeredVehicles.end(),
                        [vehicleId](const auto elem){return elem == vehicleId;});
}

bool InternalVehiclePool::isVehicleRented(int vehicleId) const
{
    return std::any_of(_rentedVehicles.begin(),
                        _rentedVehicles.end(),
                        [vehicleId](const auto elem){return elem == vehicleId;});
}