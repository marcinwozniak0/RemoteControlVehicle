#include "DcEngine.hpp"
#include "PinValueSetter.hpp"

namespace
{
constexpr uint8_t firstOutputPin = 0u;
constexpr uint8_t secondOutputPin = 1u;
constexpr uint8_t pwmPin = 2u;
}

DcEngine::DcEngine(const uint8_t firstOutputPinNumber,
                   const uint8_t secondOutputPinNumber,
                   const uint8_t pwmPinNumber)
    : _firstOutputPinNumber(firstOutputPinNumber)
    , _secondOutputPinNumber(secondOutputPinNumber)
    , _pwmOutputPinNumber (pwmPinNumber)
{}

void DcEngine::setPinsConfiguration(const std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>& valueList)
{
    _firstOutputValue = valueList.at(firstOutputPin);
    _secondOutputValue = valueList.at(secondOutputPin);
    _pwmValue = valueList.at(pwmPin);
}
