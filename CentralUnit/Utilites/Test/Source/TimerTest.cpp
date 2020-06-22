#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#include <ratio>

#include "Timer.hpp"

using namespace testing;
using namespace std::chrono_literals;

using TimeTick = duration<int64_t, std::centi>;
using CentiSecond = std::chrono::duration<long double, std::centi>;

namespace std::chrono
{
std::ostream& operator<<(std::ostream& stream, TimeTick const& milliseconds)
{
  return stream << "Time stamp = " << milliseconds.count();
}
}//std::chrono

namespace
{
constexpr auto zeroedTimerValue = CentiSecond(0);
constexpr auto timeStamp = CentiSecond(1);
constexpr auto twoTimeStamps = CentiSecond(2);

void elapsOneTimeStamp()
{
    std::this_thread::sleep_for(timeStamp);
}
}//namespace

struct TimerTest : Test
{
    Timer<TimeTick> _sut;
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
