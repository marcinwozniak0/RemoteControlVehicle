#pragma once

#include "Engine.hpp"

class DcEngine : public Engine
{
public:
    void setValues(const std::vector<uint8_t>&&) override;
private:
    int out1;//TODO to do ctora, piny beda ustawione na poczatku
    int out2;
    int pwm;
    int out1Val;
    int out2Val;
    int pwmVal;
};
