#pragma once

#include <memory>

#include "VehicleFactory.hpp"

class ThreeWheeledVehicleFactory;

class VehicleFactoryFacade : public VehicleFactory
{
public:
    VehicleFactoryFacade(const VehicleFactory& threeWheeledVehicleFactory);

    std::unique_ptr<Vehicle> create(Commands::RegisterVehicle&&) const override;

private:
    const VehicleFactory& _threeWheeledVehicleFactory;
};