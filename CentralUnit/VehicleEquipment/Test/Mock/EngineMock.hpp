#pragma once

#include <gmock/gmock.h>

#include "Engine.hpp"

class EngineMock : public Engine
{
public:
    MOCK_METHOD(void, setPinsConfiguration, (const PinsConfiguration&), (override));
    MOCK_METHOD(const PinsConfiguration&, getPinsConfiguration, (), (const, override));
};
