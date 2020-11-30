#pragma once

#include <gtest/gtest.h>

#include "CarRental.hpp"
#include "IdDistributorMock.hpp"

using namespace testing;

struct CarRentalTest : Test
{
    CarRentalTest()
        : _sut(_idDistributorMock)
    {}

    NiceMock<IdDistributorMock> _idDistributorMock;

    CarRental _sut;
};
