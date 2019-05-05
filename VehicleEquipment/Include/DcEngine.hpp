#pragma once

#include "Engine.hpp"

class PinValueSetter;

class DcEngine : public Engine
{
public:
    DcEngine(const PinValueSetter&);

    void saveValues(const std::vector<uint8_t>&&) override;
    void startEngine() override;

private:
    uint8_t out1;//TODO to do ctora, piny beda ustawione na poczatku
    uint8_t out2;
    uint8_t pwm;
    uint8_t out1Val;
    uint8_t out2Val;
    uint8_t pwmVal;
    const PinValueSetter& _pinValueSetter;
};
