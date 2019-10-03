#pragma once

#include <gmock/gmock.h>

#include "Engine.hpp"

class EngineMock : public Engine
{
public:
    MOCK_METHOD1(setPinsConfiguration, void(const std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>&));
    MOCK_CONST_METHOD0(getPinsConfiguration, const PinsConfiguration&());
};
