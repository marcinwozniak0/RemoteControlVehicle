#pragma once

#include <UserCommandToRun.pb.h>

class PropulsionSystem
{
public:
    virtual void applyNewConfigurationBasedOnCoordinates(const Messages::CoordinateSystem&) = 0;

    virtual ~PropulsionSystem() = default;
};
