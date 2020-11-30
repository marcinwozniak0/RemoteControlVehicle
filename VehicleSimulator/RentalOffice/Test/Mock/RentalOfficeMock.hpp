#pragma once

#include <gmock/gmock.h>

#include "RentalOffice.hpp"

using RentalItem = int;

class RentalOfficeMock : public RentalOffice<RentalItem>
{
public:
    MOCK_METHOD(bool, registerNewItem, (), (override));
    MOCK_METHOD(bool, removeItem, (const uint), (override));
    MOCK_METHOD(std::set<RentalItem>&, getAllItems, (), (override));
};
