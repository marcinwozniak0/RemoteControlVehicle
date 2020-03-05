#include "L293DEngineDriver.hpp"
#include "VehicleConfiguration.hpp"

namespace
{
constexpr auto firstEngine = 0u;
constexpr auto secondEngine = 1u;
constexpr auto firstInput = 0u;
constexpr auto secondInput = 1u;
}

const PinsConfiguration L293DEngineDriver::calculatePinsConfiguration(const Commands::CoordinateSystem& coordinates) const
{
    const auto pwmValue = PWM_MAX_RANGE * coordinates.y_coordinate() / EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION;
    constexpr auto directionChangeTreshold = 0;

    if (areCoordinatesInRange(coordinates) and directionChangeTreshold < coordinates.y_coordinate())
    {
        return createPinsConfiguration(_drivingForward, pwmValue);
    }
    else if (areCoordinatesInRange(coordinates) and directionChangeTreshold > coordinates.y_coordinate())
    {
        return createPinsConfiguration(_drivingBackward, pwmValue);
    }
    else if (areCoordinatesInRange(coordinates) and directionChangeTreshold == coordinates.y_coordinate())
    {
        return createPinsConfiguration(_stopEngine, pwmValue);
    }

    return {};
}

bool L293DEngineDriver::areCoordinatesInRange(const Commands::CoordinateSystem& coordinates) const
{
    return coordinates.x_coordinate() <= EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION and
           coordinates.y_coordinate() <= EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION and
           coordinates.x_coordinate() >= -EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION and
           coordinates.y_coordinate() >= -EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION;
}

const PinsConfiguration L293DEngineDriver::createPinsConfiguration(const PinStatesConfiguration& pinStatesConfiguration,
                                                                   const int pwmValue) const
{
    PinsConfiguration pinsConfiguration {};

    pinsConfiguration.try_emplace(PIN_NUMBERS::FIRST_ENGINE_FIRST_OUTPUT,  pinStatesConfiguration.at(firstEngine).at(firstInput));
    pinsConfiguration.try_emplace(PIN_NUMBERS::FIRST_ENGINE_SECOND_OUTPUT, pinStatesConfiguration.at(firstEngine).at(secondInput));
    pinsConfiguration.try_emplace(PIN_NUMBERS::SECOND_ENGINE_FIRST_OUTPUT, pinStatesConfiguration.at(secondEngine).at(firstInput));
    pinsConfiguration.try_emplace(PIN_NUMBERS::SECOND_ENGINE_SECOND_OUTPUT,pinStatesConfiguration.at(secondEngine).at(secondInput));
    pinsConfiguration.try_emplace(PIN_NUMBERS::FIRST_ENGINE_PWM,           pwmValue);
    pinsConfiguration.try_emplace(PIN_NUMBERS::SECOND_ENGINE_PWM,          pwmValue);

    return pinsConfiguration;
}
