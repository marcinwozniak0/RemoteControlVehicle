#include <utility>

#include "L293DEngineDriver.hpp"
#include "PinState.hpp"
#include "CoordinateSystem.hpp"
#include "Logger.hpp"

namespace
{
constexpr auto firstEngine = 0u;
constexpr auto secondEngine = 1u;
constexpr auto firstInput = 0u;
constexpr auto secondInput = 1u;
constexpr auto numberOfEngines = 2u;
constexpr auto numberOfInputPinsInEngine = 2u;
constexpr auto stoppedEnginePwm = 0u;
constexpr auto firstEngineFirstInput = 0u;
constexpr auto firstEngineSecondInput = 1u;
constexpr auto firstEnginePwm = 2u;
constexpr auto secondEngineFirstInput = 3u;
constexpr auto secondEngineSecondInput = 4u;
constexpr auto secondEnginePwm = 5u;

using PinStatesConfiguration = std::array<std::array<uint8_t, numberOfEngines>, numberOfInputPinsInEngine>;

const PinStatesConfiguration drivingForward {{{PIN_STATE::HIGH, PIN_STATE::LOW},
                                              {PIN_STATE::LOW, PIN_STATE::HIGH}}};
const PinStatesConfiguration drivingBackward {{{PIN_STATE::LOW, PIN_STATE::HIGH},
                                               {PIN_STATE::HIGH, PIN_STATE::LOW}}};
const PinStatesConfiguration stopEngine {{{PIN_STATE::HIGH, PIN_STATE::HIGH},
                                          {PIN_STATE::HIGH, PIN_STATE::HIGH}}};

void assignPinsValue(const PinStatesConfiguration& pinStatesConfiguration,
                     PinsConfiguration& pinConfiguration,
                     const int calculatedPwmValue)
{
    for (auto position = 0u; position < pinConfiguration.size(); ++position)
    {
        auto it = pinConfiguration.begin();
        std::advance(it, position);
        auto& [pinNumber, pinValue] = *it;

        switch(position)
        {
            case firstEngineFirstInput: pinValue = pinStatesConfiguration.at(firstEngine).at(firstInput); break;
            case firstEngineSecondInput: pinValue = pinStatesConfiguration.at(firstEngine).at(secondInput); break;
            case secondEngineFirstInput: pinValue = pinStatesConfiguration.at(secondEngine).at(firstInput); break;
            case secondEngineSecondInput: pinValue = pinStatesConfiguration.at(secondEngine).at(secondInput); break;
            case secondEnginePwm: pinValue = calculatedPwmValue; break;
            case firstEnginePwm: pinValue = calculatedPwmValue; break;
        }
    }
}

}//namespace

L293DEngineDriver::L293DEngineDriver(const int pwmRange)
    : _pwmRange(pwmRange)
{}

void L293DEngineDriver::fillPinsConfiguration(const Commands::CoordinateSystem& coordinates, PinsConfiguration& pinsConfiguration) const
{
    const auto pwmValue = _pwmRange * std::abs(coordinates.y_coordinate()) / COORDINATE_SYSTEM::RESOLUTION;
    constexpr auto directionChangeTreshold = 0;

    if (areCoordinatesInRange(coordinates) and directionChangeTreshold < coordinates.y_coordinate())
    {
        assignPinsValue(drivingForward, pinsConfiguration, pwmValue);
    }
    else if (areCoordinatesInRange(coordinates) and directionChangeTreshold > coordinates.y_coordinate())
    {
        assignPinsValue(drivingBackward, pinsConfiguration, pwmValue);
    }
    else if (areCoordinatesInRange(coordinates) and directionChangeTreshold == coordinates.y_coordinate())
    {
        assignPinsValue(stopEngine, pinsConfiguration, stoppedEnginePwm);
    }
    else
    {
        WARNING("Stopping engines due to coordinates out of range");
        assignPinsValue(stopEngine, pinsConfiguration, stoppedEnginePwm);
    }
}

bool L293DEngineDriver::areCoordinatesInRange(const Commands::CoordinateSystem& coordinates) const
{
    return coordinates.x_coordinate() <= COORDINATE_SYSTEM::RESOLUTION and
           coordinates.y_coordinate() <= COORDINATE_SYSTEM::RESOLUTION and
           coordinates.x_coordinate() >= -COORDINATE_SYSTEM::RESOLUTION and
           coordinates.y_coordinate() >= -COORDINATE_SYSTEM::RESOLUTION;
}
