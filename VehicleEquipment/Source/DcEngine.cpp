#include "DcEngine.hpp"

namespace
{
constexpr uint8_t firstOutputPin = 0u;
constexpr uint8_t secondOutputPin = 1u;
constexpr uint8_t pwmPin = 2u;
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
     for (auto& configuration : pinsConfiguration)
     {
        if (_pinsConfiguration.end() not_eq _pinsConfiguration.find(configuration.first))
        {
            _pinsConfiguration[configuration.first] = configuration.second;
        }
     }

    _pinsConfiguration = pinsConfiguration;
}

const PinsConfiguration& DcEngine::getPinsConfiguration() const
{
    return _pinsConfiguration;
}
