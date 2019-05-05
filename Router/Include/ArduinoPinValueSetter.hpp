#pragma once

#include <string>

#include "PinValueSetter.hpp"

class ArduinoPinValueSetter : public PinValueSetter
{
public:
    ArduinoPinValueSetter(const std::string&);
    ~ArduinoPinValueSetter();

    void setValue(uint8_t, uint8_t) const override;

private:
    std::string prepareMessegeToArduino(uint8_t, uint8_t) const;
    void sendMessageToArduino(const std::string&) const;

    const std::string _uartPortDesignation;
    FILE* _uartPort;
};
