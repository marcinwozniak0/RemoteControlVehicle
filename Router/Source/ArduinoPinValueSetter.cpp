#include "ArduinoPinValueSetter.hpp"
#include "VehicleConfiguration.hpp"

ArduinoPinValueSetter::ArduinoPinValueSetter(const std::string& uartPortDesignation)
    : _uartPortDesignation(uartPortDesignation)
{}

void ArduinoPinValueSetter::setValue(uint8_t pinNumber, uint8_t pinValue) const
{
    const auto messageToArduino = prepareMessegeToArduino(pinNumber, pinValue);
    sendMessageToArduino(messageToArduino);
}

namespace
{
bool isPwmPin(const uint8_t pinNumber)
{
    return PIN_NUMBERS::FIRST_ENGINE_PWM == pinNumber
            or PIN_NUMBERS::SECOND_ENGINE_PWM == pinNumber;
}

const std::string getPinType(const uint8_t pinNumber)
{
    return isPwmPin(pinNumber) ? "A" : "D";
}
}//namespace

std::string ArduinoPinValueSetter::prepareMessegeToArduino(const uint8_t pinNumber, const uint8_t pinValue) const
{
    //np 1|1|D| -> pin nr 1 cyforwy ma zostac ustawiony na high
    std::string messageToArduino;
    //messageToArduino += "PIN|";
    messageToArduino += std::to_string(pinNumber);
    messageToArduino += "|";
    messageToArduino += std::to_string(pinValue);
    messageToArduino += "|";
    messageToArduino += getPinType(pinNumber);
    messageToArduino += "=";
    //TODO oznaczyc jakos koniec wiadomosci
    //TODO oznaczyć jakoś rodzaj wiadomosci np. ustaw piny, zrob cos innego

    return messageToArduino;
}

#include <thread>
#include <chrono>

void ArduinoPinValueSetter::sendMessageToArduino(const std::string& messageToArduino) const
{
    FILE* uartPort = fopen(_uartPortDesignation.c_str(), "w");

    for (auto x : messageToArduino)
    {
        fprintf(uartPort, "%c", x); //Writing to the file
    }

    fclose(uartPort);

    //std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
