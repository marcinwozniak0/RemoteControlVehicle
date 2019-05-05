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

void DcEngine::saveValues(const std::vector<uint8_t>&& valueList)//array?
{
    //TODO if!=3 to throw ze sraka
    _firstOutputValue = *valueList.begin();
    _secondOutputValue = *(valueList.begin() + 1);
    _pwmValue = *(valueList.begin() + 2);
}

void DcEngine::startEngine()
{
    _pinValueSetter.setValue(_firstOutputPinNumber, _firstOutputValue);
    _pinValueSetter.setValue(_secondOutputPinNumber, _secondOutputValue);
    _pinValueSetter.setValue(_pwmOutputPinNumber, _pwmValue);
}
