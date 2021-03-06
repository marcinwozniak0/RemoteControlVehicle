#pragma once

#include <vector>
#include <optional>

#include "VehiclePool.hpp"

class VehicleFactory;

class InternalVehiclePool : public VehiclePool
{
public:
    InternalVehiclePool(const VehicleFactory&);

    std::optional<std::shared_ptr<Vehicle>> getVehicle(int vehicleId) override;
    bool rentVehicle(int vehicleId) override;
    bool registerVehicle(Commands::RegisterVehicle&&) override;
    const std::vector<int>& getRentedVehicleIds() const override;
    
private:
    bool isVehicleReqistered(int vehicleId) const;
    bool isVehicleRented(int vehicleId) const;
    bool isPossibleToRentNewVehicle(int vehicleId) const;
    std::optional<int> getVehicleIndex(const int vehicleId) const;

    std::vector<std::shared_ptr<Vehicle>> _vehiclePool;
    std::vector<int> _registeredVehicles;
    std::vector<int> _rentedVehicles;
    const VehicleFactory& _vehicleFactory;
};