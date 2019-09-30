#include "FrontAxialSteeringSystemTest.hpp"

TEST_F(FrontAxialSteeringSystemTest, GetPinsConfigurationShouldCallSameMethodFromSteeringWheel)
{
    PinsConfiguration pinsConfiguration {};
    EXPECT_CALL(_steeringWheelMock, getPinsConfiguration()).WillOnce(ReturnRef(pinsConfiguration));

    ASSERT_NO_THROW(_sut.getPinsConfiguration());
}
