#pragma once

#include "Engine.hpp"

class PinValueSetter;

class DcEngine : public Engine
{
public:
    DcEngine(const uint8_t, const uint8_t, const uint8_t, const PinValueSetter&);

    void saveValues(const std::vector<uint8_t>&&) override;
    void startEngine() override;

private:
    const uint8_t _firstOutputPinNumber;
    const uint8_t _secondOutputPinNumber;
    const uint8_t _pwmOutputPinNumber;
    uint8_t _firstOutputValue;
    uint8_t _secondOutputValue;
    uint8_t _pwmValue;
    const PinValueSetter& _pinValueSetter;
};
