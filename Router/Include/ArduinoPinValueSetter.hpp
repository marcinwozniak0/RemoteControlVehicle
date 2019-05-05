#pragma once

#include <string>

#include "PinValueSetter.hpp"

class ArduinoPinValueSetter : public PinValueSetter
{
public:
    ArduinoPinValueSetter(const std::string&);

    void setValue(uint8_t, uint8_t) const override;

private:
    const std::string _portDesignation;
};
