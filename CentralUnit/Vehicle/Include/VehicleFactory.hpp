#pragma once

#include <memory>

#include "Vehicle.hpp" 

class VehicleFactory
{
public:
    virtual std::unique_ptr<Vehicle> create() const = 0;

    virtual ~VehicleFactory() = default;
};