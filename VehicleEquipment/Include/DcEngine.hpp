#pragma once

#include "Engine.hpp"

class PinValueSetter;

class DcEngine : public Engine
{
public:
    DcEngine(const uint8_t, const uint8_t, const uint8_t);

    void setPinsConfiguration(const std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>&) override;

private:
    const uint8_t _firstOutputPinNumber;
    const uint8_t _secondOutputPinNumber;
    const uint8_t _pwmOutputPinNumber;
    uint8_t _firstOutputValue;
    uint8_t _secondOutputValue;
    uint8_t _pwmValue;
};
