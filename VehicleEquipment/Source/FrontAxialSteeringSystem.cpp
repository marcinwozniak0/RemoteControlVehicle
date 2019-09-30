#include "FrontAxialSteeringSystem.hpp"
#include "SteeringWheel.hpp"

FrontAxialSteeringSystem::FrontAxialSteeringSystem(SteeringWheel&  steeringWheel)
    : _steeringWheel(steeringWheel)
{}

void FrontAxialSteeringSystem::applyNewConfigurationBasedOnCoordinates(const std::pair<int32_t, int32_t>& coordinates)
{
    auto steeringAngle = calculateSteeringAngle(coordinates);
    auto pwmValue = calculatePwmValue(steeringAngle);

    _steeringWheel.setPinsConfiguration(PinsConfiguration{std::make_pair(PIN_NUMBERS::STEERING_WHEEL_PWM, pwmValue)});
}

int FrontAxialSteeringSystem::calculateSteeringAngle(const std::pair<int32_t, int32_t>& coordinates) const
{
    return 0;
}

int FrontAxialSteeringSystem::calculatePwmValue(const int steeringAngle) const
{
    return 0;
}

const PinsConfiguration& FrontAxialSteeringSystem::getPinsConfiguration() const
{
    return _steeringWheel.getPinsConfiguration();
}
