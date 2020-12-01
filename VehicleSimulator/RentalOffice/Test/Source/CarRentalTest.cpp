#include "CarRentalTest.hpp"

namespace
{
constexpr auto firstId = 0;
} //namespace

TEST_F(CarRentalTest, rentedCarListShouldBeEmptyByDefault)
{
    ASSERT_TRUE(_sut.getAllItems().empty());
}

TEST_F(CarRentalTest, registerNewItemShouldReturnRegisteredItemIdWhenThereIsNoIdColision)
{
    EXPECT_CALL(_idDistributorMock, getFreeId()).WillRepeatedly(Return(firstId));

    ASSERT_EQ(_sut.registerNewItem(), firstId);
}

TEST_F(CarRentalTest, registerNewItemShouldReturnNulloptWhenThereIsIdColision)
{
    EXPECT_CALL(_idDistributorMock, getFreeId()).WillRepeatedly(Return(firstId));

    _sut.registerNewItem();

    ASSERT_EQ(_sut.registerNewItem(), std::nullopt);
}

TEST_F(CarRentalTest, registeredItemShouldBeStored)
{
    EXPECT_CALL(_idDistributorMock, getFreeId()).WillRepeatedly(Return(firstId));

    _sut.registerNewItem();

    ASSERT_EQ(_sut.getAllItems().size(), 1);
}
