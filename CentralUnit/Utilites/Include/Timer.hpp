#pragma once

#include <chrono>

using namespace std::chrono;
using namespace std::literals::chrono_literals;

namespace
{
steady_clock::time_point timePointIsNotSet {};
constexpr auto emptyTime = 0u;
}//namesapce

template <typename Duration>
class Timer
{
public:
    virtual void start()
    {
        if (not isTimerRunning())
        {
            _startPoint = steady_clock::now();
        }
    }

    virtual void stop()
    {
        if (isTimerRunning())
        {
            _storedTime += duration_cast<Duration>(steady_clock::now() - _startPoint);
            _startPoint = {};
        }
    }

    virtual void reset()
    {
        _storedTime = {};

        if (isTimerRunning())
        {
            _startPoint = steady_clock::now();
        }
    }

    virtual Duration getElapsedTime() const
    {
        if (isTimerInInitialState())
        {
            return {};
        }
        else if(not isTimerRunning())
        {
            return _storedTime;
        }
        else
        {
            return _storedTime + duration_cast<Duration>(steady_clock::now() - _startPoint);
        }
    }

    bool isTimerRunning() const
    {
        return timePointIsNotSet not_eq _startPoint;
    }

    ~Timer() = default;

private:
    bool isTimerInInitialState() const { return timePointIsNotSet == _startPoint and emptyTime == _storedTime.count(); }

    steady_clock::time_point _startPoint {};
    Duration _storedTime {};
};
