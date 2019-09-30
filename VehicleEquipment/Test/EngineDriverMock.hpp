#pragma once

#include <gmock/gmock.h>

#include "EngineDriver.hpp"

class EngineDriverMock : public EngineDriver
{
public:
    MOCK_CONST_METHOD1(calculatePinsConfiguration,
                       std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>(const Messages::CoordinateSystem&));
};

