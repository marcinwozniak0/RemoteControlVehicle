#include "ThirtyDegreesSteeringWheel.hpp"
#include "VehicleConfiguration.hpp"

ThirtyDegreesSteeringWheel::ThirtyDegreesSteeringWheel(const uint8_t pwmPinNumber)
    : _pinConfiguration({std::make_pair(pwmPinNumber, PIN_STATE::INITIAL_PWM)})
{}

void ThirtyDegreesSteeringWheel::setConfiguration(const std::array<uint8_t, NUMBER_OF_PINS_PER_STEERING_WHEEL>&)
{

}

const PinConfiguration& ThirtyDegreesSteeringWheel::getConfiguration() const
{
    return _pinConfiguration;
}
