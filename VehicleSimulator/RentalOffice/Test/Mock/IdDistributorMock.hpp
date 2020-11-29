#pragma once

#include <gmock/gmock.h>

#include "IdDistributor.hpp"

class IdDistributorMock : public IdDistributor
{
public:
    MOCK_METHOD(unsigned, getFreeId, (), (override));
};
