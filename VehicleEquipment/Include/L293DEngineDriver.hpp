#pragma once

#include "EngineDriver.hpp"

class L293DEngineDriver : public EngineDriver
{
public:
    std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
        calculatePinValues(const std::vector<uint8_t>&) const override;

private:
    const std::array<std::array<uint8_t, 2>, 2> _drivingForward {{{1, 0}, {0, 1}}};
    const std::array<std::array<uint8_t, 2>, 2> _drivingBackward {{{0, 1}, {1, 0}}};
};
