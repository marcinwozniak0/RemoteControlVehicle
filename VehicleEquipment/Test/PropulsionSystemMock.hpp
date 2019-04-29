#pragma once

#include <gmock/gmock.h>

#include "PropulsionSystem.hpp"

class PropulsionSystemMock : public PropulsionSystem
{
public:
    MOCK_METHOD1(transferCharacteristicValues, void(const std::vector<uint8_t>&&));
};
