#pragma once

#include "EngineDriver.hpp"

class L293DEngineDriver : public EngineDriver
{
public:
    std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
        calculatePinValues(const std::vector<uint8_t>&) const override;

private:
    const std::array<std::array<uint8_t, NUMBER_OF_ENGINES>, NUMBER_OF_INPUT_PIN_IN_ENGINE>
        _drivingForward {{{PIN_STATE::HIGH, PIN_STATE::LOW},
                          {PIN_STATE::LOW, PIN_STATE::HIGH}}};
    const std::array<std::array<uint8_t, NUMBER_OF_ENGINES>, NUMBER_OF_INPUT_PIN_IN_ENGINE>
        _drivingBackward {{{PIN_STATE::LOW, PIN_STATE::HIGH},
                           {PIN_STATE::HIGH, PIN_STATE::LOW}}};
};
