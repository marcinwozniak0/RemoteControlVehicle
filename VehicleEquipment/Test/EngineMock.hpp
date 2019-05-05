#pragma once

#include <gmock/gmock.h>

#include "Engine.hpp"

class EngineMock : public Engine
{
public:
    MOCK_METHOD1(saveValues, void(const std::vector<uint8_t>&&));
    MOCK_METHOD0(startEngine, void());
};
