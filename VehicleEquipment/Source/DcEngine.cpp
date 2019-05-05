#include "DcEngine.hpp"
#include "PinValueSetter.hpp"

DcEngine::DcEngine(const PinValueSetter& pinValueSetter)
    : _pinValueSetter(pinValueSetter)
{}

void DcEngine::saveValues(const std::vector<uint8_t>&& valueList)//array?
{
    //TODO if!=3 to throw ze sraka
    out1Val = *valueList.begin();
    out2Val = *(valueList.begin() + 1);
    pwmVal = *(valueList.begin() + 2);
}

void DcEngine::startEngine()
{
    _pinValueSetter.setValue(out1, out1Val);
    _pinValueSetter.setValue(out2, out2Val);
    _pinValueSetter.setValue(pwm, pwmVal);
}
