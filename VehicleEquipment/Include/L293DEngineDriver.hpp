#pragma once

#include "EngineDriver.hpp"

class L293DEngineDriver : public EngineDriver
{
public:
    std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
        calculatePinValues(const std::pair<int16_t, int16_t>&) const override;

private:
    bool areCoordinatesInRange(const std::pair<int16_t, int16_t>&) const;

    const std::array<std::array<uint8_t, NUMBER_OF_ENGINES>, NUMBER_OF_INPUT_PIN_IN_ENGINE>
        _drivingForward {{{PIN_STATE::HIGH, PIN_STATE::LOW},
                          {PIN_STATE::LOW, PIN_STATE::HIGH}}};
    const std::array<std::array<uint8_t, NUMBER_OF_ENGINES>, NUMBER_OF_INPUT_PIN_IN_ENGINE>
        _drivingBackward {{{PIN_STATE::LOW, PIN_STATE::HIGH},
                           {PIN_STATE::HIGH, PIN_STATE::LOW}}};
};
