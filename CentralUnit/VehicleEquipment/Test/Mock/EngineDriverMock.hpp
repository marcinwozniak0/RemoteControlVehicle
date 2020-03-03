#pragma once

#include <gmock/gmock.h>

#include "EngineDriver.hpp"

class EngineDriverMock : public EngineDriver
{
public:
    MOCK_CONST_METHOD1(calculatePinsConfiguration, const PinsConfiguration(const Messages::CoordinateSystem&));
};

