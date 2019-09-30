#include "L293DEngineDriver.hpp"
#include "VehicleConfiguration.hpp"

std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
L293DEngineDriver::calculatePinsConfiguration(const Messages::CoordinateSystem& coordinates) const
{
    std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE> pinValuesOfLeftEngine {};
    std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE> pinValuesOfRightEngine {};

    const uint8_t pwmValue = PWM_MAX_RANGE * coordinates.y_coordinate() / EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION;
    constexpr uint8_t directionChangeTreshold = 0;

    if (areCoordinatesInRange(coordinates) and directionChangeTreshold < coordinates.y_coordinate())
    {
         pinValuesOfLeftEngine = {_drivingForward.at(0).at(0),
                                  _drivingForward.at(0).at(1),
                                  pwmValue};

        pinValuesOfRightEngine = {_drivingForward.at(1).at(0),
                                  _drivingForward.at(1).at(1),
                                  pwmValue};

    }
    else if (areCoordinatesInRange(coordinates) and directionChangeTreshold > coordinates.y_coordinate())
    {
         pinValuesOfLeftEngine = {_drivingBackward.at(0).at(0),
                                  _drivingBackward.at(0).at(1),
                                  pwmValue};

         pinValuesOfRightEngine = {_drivingBackward.at(1).at(0),
                                   _drivingBackward.at(1).at(1),
                                   pwmValue};
    }
    else if (areCoordinatesInRange(coordinates) and directionChangeTreshold == coordinates.y_coordinate())
    {
        pinValuesOfLeftEngine = {_stopEngine.at(0).at(0),
                                 _stopEngine.at(0).at(1),
                                 pwmValue};

        pinValuesOfRightEngine = {_stopEngine.at(1).at(0),
                                  _stopEngine.at(1).at(1),
                                  pwmValue};
    }

    return {pinValuesOfLeftEngine, pinValuesOfRightEngine};
}

bool L293DEngineDriver::areCoordinatesInRange(const Messages::CoordinateSystem& coordinates) const
{
    return coordinates.x_coordinate() <= EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION and
           coordinates.y_coordinate() <= EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION and
           coordinates.x_coordinate() >= -EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION and
           coordinates.y_coordinate() >= -EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION;
}
