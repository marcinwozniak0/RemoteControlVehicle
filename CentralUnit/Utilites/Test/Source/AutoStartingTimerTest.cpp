#include <gtest/gtest.h>

#include "AutoStartingTimer.hpp"

TEST(AutoStartingTimerTest, timerShouldBeStartedInCtor)
{
    AutoStartingTimer<seconds> sut;
    ASSERT_TRUE(sut.isTimerRunning());
}
