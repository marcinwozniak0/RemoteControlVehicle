#pragma once

#include <gmock/gmock.h>

#include "EngineDriver.hpp"

class EngineDriverMock : public EngineDriver
{
public:
    MOCK_METHOD(void, fillPinsConfiguration, (const Commands::CoordinateSystem&, PinsConfiguration&), (const, override));
};

