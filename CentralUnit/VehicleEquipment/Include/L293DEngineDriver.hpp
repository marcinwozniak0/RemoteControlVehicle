#pragma once

#include "EngineDriver.hpp"

class L293DEngineDriver : public EngineDriver
{
public:
    L293DEngineDriver(int);

    void fillPinsConfiguration(const Commands::CoordinateSystem&, PinsConfiguration&) const override;

private:
    bool areCoordinatesInRange(const Commands::CoordinateSystem&) const;

    const int _pwmRange;
};
