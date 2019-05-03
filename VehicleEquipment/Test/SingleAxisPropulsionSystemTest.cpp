#include "SingleAxisPropulsionSystemTest.hpp"

TEST_F(SingleAxisPropulsionSystemTest, eachEngineShouldHasTheSameValue)
{
    EXPECT_CALL(_leftEngineMock, setValues(std::vector<uint8_t>{1,44}));
    EXPECT_CALL(_rightEngineMock, setValues(std::vector<uint8_t>{1,44}));
    _sut.transferCharacteristicValues(std::vector<uint8_t>{1,44});
}
