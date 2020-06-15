#include <gtest/gtest.h>
#include <chrono>
#include <thread>

#include "Timer.hpp"

namespace std::chrono {
std::ostream& operator<<(std::ostream& stream, milliseconds const& milliseconds)
{
  return stream << "Timestamp = " << milliseconds.count();
}
}//std::chrono

using namespace testing;
using namespace std::literals::chrono_literals;

namespace
{
constexpr auto zeroedTimerValue = 0ms;
constexpr auto timeStamp = 1ms;
constexpr auto twoTimeStamps = 2ms;

void elapsOneTimeStamp()
{
    std::this_thread::sleep_for(timeStamp);
}
}//namespace

struct TimerTest : Test
{
    Timer<milliseconds> _sut;
};


TEST_F(TimerTest, timerShouldReturnZeroAtBegin)
{
    ASSERT_EQ(_sut.getElapsedTime(), zeroedTimerValue);
}

TEST_F(TimerTest, timerShouldReturnZeroIfTimerWasNotStarted)
{
    elapsOneTimeStamp();
    ASSERT_EQ(_sut.getElapsedTime(), zeroedTimerValue);
}

TEST_F(TimerTest, timerShouldReturnOneTimeStampAfterOneTimeStampPeriod)
{
    _sut.start();

    elapsOneTimeStamp();

    ASSERT_EQ(_sut.getElapsedTime(), timeStamp);
}

TEST_F(TimerTest, timerShouldStopCountingAfterStop)
{
    _sut.start();

    elapsOneTimeStamp();

    _sut.stop();

    elapsOneTimeStamp();

    ASSERT_EQ(_sut.getElapsedTime(), timeStamp);
}

TEST_F(TimerTest, timerShouldStartCountingWhenWasStaredAfterStop)
{
    _sut.start();

    elapsOneTimeStamp();

    _sut.stop();

    elapsOneTimeStamp();

    _sut.start();

    elapsOneTimeStamp();

    ASSERT_EQ(_sut.getElapsedTime(), twoTimeStamps);
}

TEST_F(TimerTest, secondTimerStopWithoutStartShouldNotAffectedOnElapsedTime)
{
    _sut.start();

    elapsOneTimeStamp();

    _sut.stop();

    elapsOneTimeStamp();

    _sut.stop();

    ASSERT_EQ(_sut.getElapsedTime(), timeStamp);
}

TEST_F(TimerTest, secondTimerStartWithoutStopShouldNotAffectedOnElapsedTime)
{
    _sut.start();

    elapsOneTimeStamp();

    _sut.start();

    elapsOneTimeStamp();

    ASSERT_EQ(_sut.getElapsedTime(), twoTimeStamps);
}

TEST_F(TimerTest, afterResetTimerShouldBeZeroed)
{
    _sut.start();

    elapsOneTimeStamp();

    _sut.reset();

    ASSERT_EQ(_sut.getElapsedTime(), zeroedTimerValue);
}

TEST_F(TimerTest, afterResetTimerShouldContiuneCountingFromZero)
{
    _sut.start();

    elapsOneTimeStamp();

    _sut.reset();

    elapsOneTimeStamp();

    ASSERT_EQ(_sut.getElapsedTime(), timeStamp);
}

TEST_F(TimerTest, isRunnuningShouldReturnTrue)
{
    _sut.start();

    ASSERT_TRUE(_sut.isTimerRunning());
}

TEST_F(TimerTest, isRunnuningShouldReturnFalse)
{
    _sut.start();
    _sut.stop();

    ASSERT_FALSE(_sut.isTimerRunning());
}

TEST_F(TimerTest, isRunnuningShouldReturnTrueAfterResetOnRunningTimer)
{
    _sut.start();

    ASSERT_TRUE(_sut.isTimerRunning());
}

TEST_F(TimerTest, isRunnuningShouldReturnFalseAfterResetOnStoppedTimer)
{
    _sut.start();
    _sut.stop();
    _sut.reset();

    ASSERT_FALSE(_sut.isTimerRunning());
}
