#pragma once

#include "stdint.h"

constexpr auto ARDUINO_PORT_DESIGNATION = "/dev/ttyACM0";

namespace PIN_NUMBERS
{
constexpr uint8_t FIRST_ENGINE_FIRST_OUTPUT = 2;
constexpr uint8_t FIRST_ENGINE_SECOND_OUTPUT = 4;
constexpr uint8_t FIRST_ENGINE_PWM = 3;
constexpr uint8_t SECOND_ENGINE_FIRST_OUTPUT = 7;
constexpr uint8_t SECOND_ENGINE_SECOND_OUTPUT = 8;
constexpr uint8_t SECOND_ENGINE_PWM = 5;
}//PIN_NUMBERS
