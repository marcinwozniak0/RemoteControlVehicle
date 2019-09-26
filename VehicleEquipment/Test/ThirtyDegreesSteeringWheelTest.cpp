#include "ThirtyDegreesSteeringWheelTest.hpp"

TEST_F(ThirtyDegreesSteeringWheelTest, PinValueShouldBeSetToZeroAtBegin)
{
    const PinsConfiguration expectedConfiguration{std::make_pair(steeringWheelPwmPinNumer, pinValueInNeutralState)};

    ASSERT_EQ(expectedConfiguration, _sut.getConfiguration());
}

TEST_F(ThirtyDegreesSteeringWheelTest, WhenNewConfigurationContainsUknownPinsShouldBeIgnored)
{
    const PinsConfiguration configurationWithUnknownPin{std::make_pair(unknownSteeringWheelPwmPinNumer, pinValue)};
    const PinsConfiguration currentConfiguration{std::make_pair(steeringWheelPwmPinNumer, pinValueInNeutralState)};

    _sut.setConfiguration(configurationWithUnknownPin);

    ASSERT_EQ(currentConfiguration, _sut.getConfiguration());
}

TEST_F(ThirtyDegreesSteeringWheelTest, ConfigurationContainsMorePinsShouldBeIgnored)
{
    const PinsConfiguration configurationWithTooManyPins{std::make_pair(steeringWheelPwmPinNumer, pinValue),
                std::make_pair(unknownSteeringWheelPwmPinNumer, pinValue)};
    const PinsConfiguration currentConfiguration{std::make_pair(steeringWheelPwmPinNumer, pinValueInNeutralState)};

    _sut.setConfiguration(configurationWithTooManyPins);

    ASSERT_EQ(currentConfiguration, _sut.getConfiguration());
}

TEST_F(ThirtyDegreesSteeringWheelTest, CorrectConfigurationShouldReplaceOldConfiguration)
{
    const PinsConfiguration newCorrectConfiguration{std::make_pair(steeringWheelPwmPinNumer, pinValue)};

    _sut.setConfiguration(newCorrectConfiguration);

    ASSERT_EQ(newCorrectConfiguration, _sut.getConfiguration());
}
