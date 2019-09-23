#include "L293DEngineDriver.hpp"
#include "VehicleConfiguration.hpp"

std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
L293DEngineDriver::calculatePinsConfiguration(const std::pair<int32_t, int32_t>& characteristic) const
{
    std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE> pinValuesOfLeftEngine {};
    std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE> pinValuesOfRightEngine {};

    const uint8_t pwmValue = PWM_MAX_RANGE * characteristic.second / EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION;
    constexpr uint8_t directionChangeTreshold = 0;

    if (areCoordinatesInRange(characteristic) and directionChangeTreshold < characteristic.second)
    {
         pinValuesOfLeftEngine = {_drivingForward.at(0).at(0),
                                  _drivingForward.at(0).at(1),
                                  pwmValue};

        pinValuesOfRightEngine = {_drivingForward.at(1).at(0),
                                  _drivingForward.at(1).at(1),
                                  pwmValue};

    }
    else if (areCoordinatesInRange(characteristic) and directionChangeTreshold > characteristic.second)
    {
         pinValuesOfLeftEngine = {_drivingBackward.at(0).at(0),
                                  _drivingBackward.at(0).at(1),
                                  pwmValue};

         pinValuesOfRightEngine = {_drivingBackward.at(1).at(0),
                                   _drivingBackward.at(1).at(1),
                                   pwmValue};
    }
    else if (areCoordinatesInRange(characteristic) and directionChangeTreshold == characteristic.second)
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

bool L293DEngineDriver::areCoordinatesInRange(const std::pair<int32_t, int32_t>& coordinates) const
{
    const auto& [xCoordinate, yCoordinate] = coordinates;

    return xCoordinate <= EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION and
           yCoordinate <= EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION and
           xCoordinate >= -EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION and
           yCoordinate >= -EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION;
}
