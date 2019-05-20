#pragma once

#include "stdint.h"

static constexpr uint8_t NUMBER_OF_ENGINES = 2;
static constexpr uint8_t NUMBER_OF_INPUT_PIN_IN_ENGINE = 2;
static constexpr uint8_t NUMBER_OF_PINS_PER_ENGINE = 3;
static constexpr auto ARDUINO_PORT_DESIGNATION = "/dev/ttyACM0";
static constexpr uint8_t PWM_MAX_RANGE = 255;

namespace PIN_NUMBERS
{
static constexpr uint8_t FIRST_ENGINE_FIRST_OUTPUT = 2;
static constexpr uint8_t FIRST_ENGINE_SECOND_OUTPUT = 4;
static constexpr uint8_t FIRST_ENGINE_PWM = 3;
static constexpr uint8_t SECOND_ENGINE_FIRST_OUTPUT = 7;
static constexpr uint8_t SECOND_ENGINE_SECOND_OUTPUT = 8;
static constexpr uint8_t SECOND_ENGINE_PWM = 5;
}//PIN_NUMBERS

namespace PIN_STATE
{
static constexpr uint8_t LOW = 0;
static constexpr uint8_t HIGH = 1;
}//PIN_STATE

namespace EXTERNAL_INTERFACES
{
static constexpr uint16_t COORDINATE_SYSTEM_RESOLUTION = 16000;
}//EXTERNAL_INTERFACES
