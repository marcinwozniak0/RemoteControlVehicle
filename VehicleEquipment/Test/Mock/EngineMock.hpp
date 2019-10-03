#pragma once

#include <gmock/gmock.h>

#include "Engine.hpp"

class EngineMock : public Engine
{
public:
    MOCK_METHOD1(setConfiguration, void(const std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>&));
    MOCK_METHOD0(activateConfiguration, void());
};
