#pragma once

#include <gmock/gmock.h>

#include "Engine.hpp"

class EngineMock : public Engine
{
public:
    MOCK_METHOD1(setValues, void(const std::initializer_list<uint8_t>&&));
};
