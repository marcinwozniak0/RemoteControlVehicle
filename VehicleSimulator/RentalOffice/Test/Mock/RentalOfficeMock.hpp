#pragma once

#include <gmock/gmock.h>

#include "RentalOffice.hpp"

using RentalItem = int;

class RentalOfficeMock : public RentalOffice<RentalItem>
{
public:
    MOCK_METHOD(void, registerNewItem, (), (override));
    MOCK_METHOD(void, removeItem, (const uint), (override));
    MOCK_METHOD(std::vector<RentalItem>&, getAllItems, (), (override));
};
