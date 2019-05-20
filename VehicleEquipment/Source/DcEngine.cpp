#include "DcEngine.hpp"
#include "PinValueSetter.hpp"

DcEngine::DcEngine(const uint8_t firstOutputPinNumber,
                   const uint8_t secondOutputPinNumber,
                   const uint8_t pwmPinNumber,
                   const PinValueSetter& pinValueSetter)
    : _firstOutputPinNumber(firstOutputPinNumber)
    , _secondOutputPinNumber(secondOutputPinNumber)
    , _pwmOutputPinNumber (pwmPinNumber)
    , _pinValueSetter(pinValueSetter)
{}

void DcEngine::saveValues(const std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>& valueList)
{
    _firstOutputValue = valueList.at(0);
    _secondOutputValue = valueList.at(1);
    _pwmValue = valueList.at(2);
}

void DcEngine::startEngine()
{
    _pinValueSetter.setValue(_firstOutputPinNumber, _firstOutputValue);
    _pinValueSetter.setValue(_secondOutputPinNumber, _secondOutputValue);
    _pinValueSetter.setValue(_pwmOutputPinNumber, _pwmValue);
}
