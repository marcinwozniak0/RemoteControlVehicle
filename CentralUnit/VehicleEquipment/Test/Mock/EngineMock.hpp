#pragma once

#include <gmock/gmock.h>

#include "Engine.hpp"

class EngineMock : public Engine
{
public:
    MOCK_METHOD1(setPinsConfiguration, void(const PinsConfiguration&));
    MOCK_CONST_METHOD0(getPinsConfiguration, const PinsConfiguration&());
};
