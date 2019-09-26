#include <algorithm>

#include "ThirtyDegreesSteeringWheel.hpp"
#include "VehicleConfiguration.hpp"

ThirtyDegreesSteeringWheel::ThirtyDegreesSteeringWheel(const uint8_t pwmPinNumber)
    : _pinConfiguration({std::make_pair(pwmPinNumber, PIN_STATE::INITIAL_PWM)})
{}

namespace
{
bool isPinsConfigurationsAreEqual(const PinsConfiguration& lhs, const PinsConfiguration& rhs)
{
    return lhs.size() == rhs.size()
           && std::equal(lhs.begin(),
                         lhs.end(),
                         rhs.begin(),
                         [](const auto a, const auto b){return a.first == b.first;});

}//namespace

}
void ThirtyDegreesSteeringWheel::setConfiguration(const PinsConfiguration& pinConfiguration)
{
    if(isPinsConfigurationsAreEqual(_pinConfiguration, pinConfiguration))
    {
        _pinConfiguration = pinConfiguration;
    }
    else
    {

    }
}

const PinsConfiguration& ThirtyDegreesSteeringWheel::getConfiguration() const
{
    return _pinConfiguration;
}
