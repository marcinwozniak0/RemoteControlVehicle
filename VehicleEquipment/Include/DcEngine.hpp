#pragma once

#include "Engine.hpp"

class DcEngine : public Engine
{
public:
    void setValues(const std::vector<uint8_t>&&) override;
private:
    uint8_t out1;//TODO to do ctora, piny beda ustawione na poczatku
    uint8_t out2;
    uint8_t pwm;
    uint8_t out1Val;
    uint8_t out2Val;
    uint8_t pwmVal;
};
