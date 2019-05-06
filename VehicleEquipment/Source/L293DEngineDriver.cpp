#include "L293DEngineDriver.hpp"

std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
L293DEngineDriver::calculatePinValues(const std::vector<uint8_t>&&) const
{
    std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE> x = {1,1,255};
    std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE> y = {1,1,255};
    return {x,y};
}
