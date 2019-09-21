#include <utility>
#include <cstdint>

#pragma once

struct USER_COMMAND_TO_DRIVE
{
    USER_COMMAND_TO_DRIVE(const int16_t xCoordinate, const int16_t yCoordinate)
        : _coordinateSystem(std::make_pair(xCoordinate, yCoordinate))
    {}

    std::pair<int16_t, int16_t> _coordinateSystem;
};
