#include "L293DEngineDriver.hpp"
#include "VehicleConfiguration.hpp"
#include <iostream>
std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
L293DEngineDriver::calculatePinValues(const std::vector<uint8_t>& characteristic) const
{
    constexpr uint8_t directionField = 0;
    constexpr uint8_t speedField = 1;
    constexpr uint8_t forwardDirection = 1;
    constexpr uint8_t backwardDirection = 0;

    const uint8_t pwmValue = PWM_MAX_RANGE * characteristic.at(speedField)/100;
    std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE> pinValuesOfLeftEngine {};
    std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE> pinValuesOfRightEngine {};

    if (forwardDirection == characteristic.at(directionField))
    {
         pinValuesOfLeftEngine = {_drivingForward.at(0).at(0),
                                  _drivingForward.at(0).at(1),
                                  pwmValue};

        pinValuesOfRightEngine = {_drivingForward.at(1).at(0),
                                  _drivingForward.at(1).at(1),
                                  pwmValue};

    }
    else if (backwardDirection == characteristic.at(directionField))
    {
         pinValuesOfLeftEngine = {_drivingBackward.at(0).at(0),
                                  _drivingBackward.at(0).at(1),
                                  pwmValue};

         pinValuesOfRightEngine = {_drivingBackward.at(1).at(0),
                                   _drivingBackward.at(1).at(1),
                                   pwmValue};
    }

    return {pinValuesOfLeftEngine, pinValuesOfRightEngine};
}
