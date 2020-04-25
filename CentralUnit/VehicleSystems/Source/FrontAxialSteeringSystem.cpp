#include "FrontAxialSteeringSystem.hpp"
#include "SteeringWheel.hpp"
#include "CoordinateSystem.hpp"

namespace
{
constexpr auto maxSteeringAngle = 30;
}

FrontAxialSteeringSystem::FrontAxialSteeringSystem(SteeringWheel& steeringWheel)
    : _steeringWheel(steeringWheel)
{}

void FrontAxialSteeringSystem::applyNewConfigurationBasedOnCoordinates(const Commands::CoordinateSystem& coordinates)
{
    auto steeringAngle = calculateSteeringAngle(coordinates);
    auto pwmValue = calculatePwmValue(steeringAngle);

    auto pinsConfiguration = _steeringWheel.getPinsConfiguration();
    auto& [pinNumber, pinValue] = *pinsConfiguration.begin();
    pinValue = pwmValue;

    _steeringWheel.setPinsConfiguration(pinsConfiguration);
}

int FrontAxialSteeringSystem::calculateSteeringAngle(const Commands::CoordinateSystem& coordinates) const
{
    if (coordinates.x_coordinate() == COORDINATE_SYSTEM::RESOLUTION)
        return -maxSteeringAngle;
    else if (coordinates.x_coordinate() == -COORDINATE_SYSTEM::RESOLUTION)
        return maxSteeringAngle;

    return {};
}

int FrontAxialSteeringSystem::calculatePwmValue(const int steeringAngle) const
{
    if (-maxSteeringAngle == steeringAngle)
        return 14;
    else if (maxSteeringAngle == steeringAngle)
       return 23;

    return 19;
}

const PinsConfiguration& FrontAxialSteeringSystem::getPinsConfiguration() const
{
    return _steeringWheel.getPinsConfiguration();
}
