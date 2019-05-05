#include "ArduinoPinValueSetter.hpp"

ArduinoPinValueSetter::ArduinoPinValueSetter(const std::string& uartPortDesignation)
    : _uartPortDesignation(uartPortDesignation)
{
    _uartPort = fopen(_uartPortDesignation.c_str(), "w");
}

ArduinoPinValueSetter::~ArduinoPinValueSetter()
{
    fclose(_uartPort);
}

void ArduinoPinValueSetter::setValue(uint8_t pinNumber, uint8_t pinValue) const
{
    const auto messageToArduino = prepareMessegeToArduino(pinNumber, pinValue);
    sendMessageToArduino(messageToArduino);
}

std::string ArduinoPinValueSetter::prepareMessegeToArduino(uint8_t pinNumber, uint8_t pinValue) const
{
    std::string messageToArduino;

    messageToArduino += std::to_string(pinNumber);
    messageToArduino += "|";
    messageToArduino += std::to_string(pinValue);
    //TODO oznaczyc jakos koniec wiadomosci
    //TODO oznaczyć jakoś rodzaj wiadomosci np. ustaw piny, zrob cos innego

    return messageToArduino;
}

void ArduinoPinValueSetter::sendMessageToArduino(const std::string& messageToArduino) const
{
    fprintf(_uartPort, "%s", messageToArduino.c_str()); //Writing to the file
}
