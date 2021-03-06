#include <algorithm>

#include "InternalVehiclePool.hpp"
#include "VehicleFactory.hpp"
#include "Logger.hpp"

InternalVehiclePool::InternalVehiclePool(const VehicleFactory& vehicleFactory)
    : _vehicleFactory(vehicleFactory)
{}

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
    if (isPossibleToRentNewVehicle(vehicleId))
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

bool InternalVehiclePool::registerVehicle(Commands::RegisterVehicle&& registerVehicleCommand)
{
    if (const auto vehicleId = registerVehicleCommand.vehicle_id(); not isVehicleReqistered(vehicleId))
    {
        if (auto vehicle = _vehicleFactory.create(std::move(registerVehicleCommand)))
        {
            _vehiclePool.push_back(std::move(vehicle));
            _registeredVehicles.push_back(vehicleId);
            return true;
        }
        else
        {
            WARNING("Fail during creation of vehicle with id = " + std::to_string(vehicleId));
            return false;
        }
    }
    else
    {
        WARNING("Cannot register vehicle with id = " + std::to_string(vehicleId));
        return false;
    }
}

bool InternalVehiclePool::isPossibleToRentNewVehicle(int vehicleId) const
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

const std::vector<int>& InternalVehiclePool::getRentedVehicleIds() const
{
    return _rentedVehicles;
}
