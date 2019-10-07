#include "DcEngineTest.hpp"

namespace
{
constexpr auto firstOutputPin = 0;
constexpr auto secondOutputPin = 1;
constexpr auto firstUnknownPin = 1;
constexpr auto secondUnknownPin = 1;
constexpr auto pwmPin = 2;

const PinsConfiguration pinsConfigurationAfterInitialization{{firstOutputPin,  PIN_STATE::HIGH},
                                                             {secondOutputPin, PIN_STATE::HIGH},
                                                             {pwmPin,          PIN_STATE::INITIAL_PWM}};

}

DcEngineTest::DcEngineTest()
    : _sut(firstOutputPin, secondOutputPin, pwmPin)
{}

TEST_F(DcEngineTest, PinsConfigurationShouldBeInNeutralState)
{
    ASSERT_EQ(pinsConfigurationAfterInitialization, _sut.getPinsConfiguration());
}

TEST_F(DcEngineTest, ShouldChangeOnlyThosePinsWhichAreInNewConfiguration)
{
    constexpr auto newPwmValue = 100;
    const PinsConfiguration newConfiguration{{firstOutputPin,  PIN_STATE::LOW},
                                             {firstUnknownPin, PIN_STATE::HIGH},
                                             {pwmPin,          newPwmValue}};

    const PinsConfiguration expectedConfiguration{{firstOutputPin,  PIN_STATE::LOW},
                                                  {secondOutputPin, PIN_STATE::HIGH},
                                                  {pwmPin,          newPwmValue}};

    _sut.setPinsConfiguration(newConfiguration);

    ASSERT_EQ(expectedConfiguration, _sut.getPinsConfiguration());
}
