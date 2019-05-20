#include "L293DEngineDriver.hpp"
#include "VehicleConfiguration.hpp"
#include <iostream>
std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
L293DEngineDriver::calculatePinValues(const std::pair<int16_t, int16_t>& characteristic) const
{
    std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE> pinValuesOfLeftEngine {};
    std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE> pinValuesOfRightEngine {};

    const uint8_t pwmValue = PWM_MAX_RANGE * characteristic.second / EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION;
    constexpr uint8_t directionChangeTreshold = 0;

    if (directionChangeTreshold < characteristic.second)
    {
         pinValuesOfLeftEngine = {_drivingForward.at(0).at(0),
                                  _drivingForward.at(0).at(1),
                                  pwmValue};

        pinValuesOfRightEngine = {_drivingForward.at(1).at(0),
                                  _drivingForward.at(1).at(1),
                                  pwmValue};

    }
    else if (directionChangeTreshold > characteristic.second)
    {
         pinValuesOfLeftEngine = {_drivingBackward.at(0).at(0),
                                  _drivingBackward.at(0).at(1),
                                  pwmValue};

         pinValuesOfRightEngine = {_drivingBackward.at(1).at(0),
                                   _drivingBackward.at(1).at(1),
                                   pwmValue};
    }
    else
    {
        // y == 0
        //TODO else if STOP
    }

    return {pinValuesOfLeftEngine, pinValuesOfRightEngine};
}
