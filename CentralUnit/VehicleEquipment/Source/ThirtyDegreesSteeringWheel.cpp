#include <algorithm>

#include "ThirtyDegreesSteeringWheel.hpp"
#include "PinState.hpp"

ThirtyDegreesSteeringWheel::ThirtyDegreesSteeringWheel(const uint8_t pwmPinNumber)
    : _pinConfiguration({std::make_pair(pwmPinNumber, PIN_STATE::INITIAL_PWM)})
{}

namespace
{
bool isNewPinsConfigurationIsCorrect(const PinsConfiguration& currentConfiguration, const PinsConfiguration& newConfiguration)
{
    return currentConfiguration.size() == newConfiguration.size()
           && std::equal(currentConfiguration.begin(),
                         currentConfiguration.end(),
                         newConfiguration.begin(),
                         [](const auto a, const auto b){return a.first == b.first;});

}//namespace

}
bool ThirtyDegreesSteeringWheel::setPinsConfiguration(const PinsConfiguration& newPinsConfiguration)
{
    bool isNewConfigurationHasBeenApplied = false;

    if(isNewPinsConfigurationIsCorrect(_pinConfiguration, newPinsConfiguration))
    {
        _pinConfiguration = newPinsConfiguration;
        isNewConfigurationHasBeenApplied = true;
    }

    return isNewConfigurationHasBeenApplied;
}

const PinsConfiguration& ThirtyDegreesSteeringWheel::getPinsConfiguration() const
{
    return _pinConfiguration;
}
