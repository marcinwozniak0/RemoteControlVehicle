#pragma once

#include "EngineDriver.hpp"

class L293DEngineDriver : public EngineDriver
{
public:
    const PinsConfiguration calculatePinsConfiguration(const Messages::CoordinateSystem&) const override;

private:
    using PinStatesConfiguration = std::array<std::array<uint8_t, NUMBER_OF_ENGINES>, NUMBER_OF_INPUT_PIN_IN_ENGINE>;

    bool areCoordinatesInRange(const Messages::CoordinateSystem&) const;
    const PinsConfiguration createPinsConfiguration(const PinStatesConfiguration&, const int) const;

    const PinStatesConfiguration _drivingForward {{{PIN_STATE::HIGH, PIN_STATE::LOW},
                                                  {PIN_STATE::LOW, PIN_STATE::HIGH}}};
    const PinStatesConfiguration _drivingBackward {{{PIN_STATE::LOW, PIN_STATE::HIGH},
                                                   {PIN_STATE::HIGH, PIN_STATE::LOW}}};
    const PinStatesConfiguration _stopEngine {{{PIN_STATE::HIGH, PIN_STATE::HIGH},
                                              {PIN_STATE::HIGH, PIN_STATE::HIGH}}};
};
