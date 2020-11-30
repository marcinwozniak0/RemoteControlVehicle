#include "CarRentalTest.hpp"

namespace
{
constexpr auto firstId = 0;
} //namespace

TEST_F(CarRentalTest, rentedCarListShouldBeEmptyByDefault)
{
    ASSERT_TRUE(_sut.getAllItems().empty());
}

TEST_F(CarRentalTest, registerNewItemShouldReturnTrueWhenThereIsNoIdColision)
{
    EXPECT_CALL(_idDistributorMock, getFreeId()).WillRepeatedly(Return(firstId));

    ASSERT_TRUE(_sut.registerNewItem());
}

TEST_F(CarRentalTest, registerNewItemShouldReturnFalseWhenThereIsIdColision)
{
    EXPECT_CALL(_idDistributorMock, getFreeId()).WillRepeatedly(Return(firstId));

    _sut.registerNewItem();

    ASSERT_FALSE(_sut.registerNewItem());
}

TEST_F(CarRentalTest, registeredItemShouldBeStored)
{
    EXPECT_CALL(_idDistributorMock, getFreeId()).WillRepeatedly(Return(firstId));

    _sut.registerNewItem();

    ASSERT_EQ(_sut.getAllItems().size(), 1);
}
