#pragma once

#include <gmock/gmock.h>

#include "PropulsionSystem.hpp"

class PropulsionSystemMock : public PropulsionSystem
{
public:
    MOCK_METHOD1(transferCharacteristicValues, void(const std::pair<int16_t, int16_t>&));
};
