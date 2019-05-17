#pragma once

#include "stdint.h"

constexpr uint8_t NUMBER_OF_ENGINES = 2;
constexpr uint8_t NUMBER_OF_INPUT_PIN_IN_ENGINE = 2;
constexpr uint8_t NUMBER_OF_PINS_PER_ENGINE = 3;
constexpr auto ARDUINO_PORT_DESIGNATION = "/dev/ttyACM0";
constexpr uint8_t PWM_MAX_RANGE = 255;

namespace PIN_NUMBERS
{
constexpr uint8_t FIRST_ENGINE_FIRST_OUTPUT = 2;
constexpr uint8_t FIRST_ENGINE_SECOND_OUTPUT = 4;
constexpr uint8_t FIRST_ENGINE_PWM = 3;
constexpr uint8_t SECOND_ENGINE_FIRST_OUTPUT = 7;
constexpr uint8_t SECOND_ENGINE_SECOND_OUTPUT = 8;
constexpr uint8_t SECOND_ENGINE_PWM = 5;
}//PIN_NUMBERS

namespace PIN_STATE
{
constexpr uint8_t LOW = 0;
constexpr uint8_t HIGH = 1;
}//PIN_STATE
