#include "SingleAxisPropulsionSystemTest.hpp"

TEST_F(SingleAxisPropulsionSystemTest, eachEngineShouldHasTheSameValue)
{
    EXPECT_CALL(_leftEngineMock, saveValues(std::vector<uint8_t>{1,44}));
    EXPECT_CALL(_rightEngineMock, saveValues(std::vector<uint8_t>{1,44}));
    _sut.transferCharacteristicValues(std::vector<uint8_t>{1,44});
}
