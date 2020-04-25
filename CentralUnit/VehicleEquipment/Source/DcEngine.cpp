#include "DcEngine.hpp"

namespace
{

}

DcEngine::DcEngine(const uint8_t firstOutputPinNumber,
                   const uint8_t secondOutputPinNumber,
                   const uint8_t pwmPinNumber)
    : _pinsConfiguration({{firstOutputPinNumber,  PIN_STATE::HIGH},
                          {secondOutputPinNumber, PIN_STATE::HIGH},
                          {pwmPinNumber,          PIN_STATE::INITIAL_PWM}})
{}

void DcEngine::setPinsConfiguration(const PinsConfiguration& pinsConfiguration)
{
     for (const auto& [pinNumber, pinState] : pinsConfiguration)
     {
        if (_pinsConfiguration.end() not_eq _pinsConfiguration.find(pinNumber))
        {
            _pinsConfiguration[pinNumber] = pinState;
        }
     }

    _pinsConfiguration = pinsConfiguration;
}

const PinsConfiguration& DcEngine::getPinsConfiguration() const
{
    return _pinsConfiguration;
}
