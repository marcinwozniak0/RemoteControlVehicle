#include "ThirtyDegreesSteeringWheelTest.hpp"

TEST_F(ThirtyDegreesSteeringWheelTest, PinValueShouldBeSetToZeroAtBegin)
{
    const PinsConfiguration expectedConfiguration{std::make_pair(steeringWheelPwmPinNumer, pinValueInNeutralState)};

    ASSERT_EQ(expectedConfiguration, _sut.getPinsConfiguration());
}

TEST_F(ThirtyDegreesSteeringWheelTest, WhenNewConfigurationContainsUknownPinsShouldBeIgnored)
{
    const PinsConfiguration configurationWithUnknownPin{std::make_pair(unknownSteeringWheelPwmPinNumer, pinValue)};
    const PinsConfiguration currentConfiguration{std::make_pair(steeringWheelPwmPinNumer, pinValueInNeutralState)};

    _sut.setPinsConfiguration(configurationWithUnknownPin);

    ASSERT_EQ(currentConfiguration, _sut.getPinsConfiguration());
}

TEST_F(ThirtyDegreesSteeringWheelTest, ConfigurationContainsMorePinsShouldBeIgnored)
{
    const PinsConfiguration configurationWithTooManyPins{std::make_pair(steeringWheelPwmPinNumer, pinValue),
                                                         std::make_pair(unknownSteeringWheelPwmPinNumer, pinValue)};
    const PinsConfiguration currentConfiguration{std::make_pair(steeringWheelPwmPinNumer, pinValueInNeutralState)};

    _sut.setPinsConfiguration(configurationWithTooManyPins);

    ASSERT_EQ(currentConfiguration, _sut.getPinsConfiguration());
}

TEST_F(ThirtyDegreesSteeringWheelTest, CorrectConfigurationShouldReplaceOldConfiguration)
{
    const PinsConfiguration newCorrectConfiguration{std::make_pair(steeringWheelPwmPinNumer, pinValue)};

    _sut.setPinsConfiguration(newCorrectConfiguration);

    ASSERT_EQ(newCorrectConfiguration, _sut.getPinsConfiguration());
}

TEST_F(ThirtyDegreesSteeringWheelTest, SetPinsConfigurationShouldReturnTrueWhenNewPinsConfigurationIsCorrect)
{
    const PinsConfiguration newCorrectConfiguration{std::make_pair(steeringWheelPwmPinNumer, pinValue)};

    ASSERT_TRUE(_sut.setPinsConfiguration(newCorrectConfiguration));
}

TEST_F(ThirtyDegreesSteeringWheelTest, SetPinsConfigurationShouldReturnFalseWhenNewPinsConfigurationIsCorrect)
{
    const PinsConfiguration newIncorrectConfiguration{std::make_pair(unknownSteeringWheelPwmPinNumer, pinValue)};

    ASSERT_FALSE(_sut.setPinsConfiguration(newIncorrectConfiguration));
}
