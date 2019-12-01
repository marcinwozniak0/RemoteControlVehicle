#pragma once

static constexpr auto NUMBER_OF_ENGINES = 2u;
static constexpr auto NUMBER_OF_INPUT_PIN_IN_ENGINE = 2u;
static constexpr auto NUMBER_OF_PINS_PER_ENGINE = 3u;
static constexpr auto NUMBER_OF_PINS_PER_STEERING_WHEEL = 1u;
static constexpr auto PWM_MAX_RANGE = 255u;
static constexpr auto PORT = 8080u;
static constexpr auto IP_ADDRESS = "127.0.0.1";
static constexpr auto END_OF_COMMAND_CHARACTER = '\0';

namespace PIN_NUMBERS
{
static constexpr auto FIRST_ENGINE_FIRST_OUTPUT = 2u;
static constexpr auto FIRST_ENGINE_SECOND_OUTPUT = 4u;
static constexpr auto FIRST_ENGINE_PWM = 3u;
static constexpr auto SECOND_ENGINE_FIRST_OUTPUT = 7u;
static constexpr auto SECOND_ENGINE_SECOND_OUTPUT = 8u;
static constexpr auto SECOND_ENGINE_PWM = 5u;
static constexpr auto STEERING_WHEEL_PWM = 44u;
}//PIN_NUMBERS

namespace PIN_STATE
{
static constexpr auto LOW = 0u;
static constexpr auto HIGH = 1u;
static constexpr auto INITIAL_PWM = 0u;
}//PIN_STATE

namespace EXTERNAL_INTERFACES
{
static constexpr auto COORDINATE_SYSTEM_RESOLUTION = 16000;
}//EXTERNAL_INTERFACES
