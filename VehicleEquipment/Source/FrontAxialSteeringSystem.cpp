#include "FrontAxialSteeringSystem.hpp"
#include "SteeringWheel.hpp"

FrontAxialSteeringSystem::FrontAxialSteeringSystem(SteeringWheel&  steeringWheel)
    : _steeringWheel(steeringWheel)
{}

void FrontAxialSteeringSystem::applyNewConfigurationBasedOnCoordinates(const std::pair<int32_t, int32_t>& coordinates)
{
}
