#pragma once

#include "Timer.hpp"

template <typename Duration>
class AutoStartingTimer : public Timer<Duration>
{
public:
    AutoStartingTimer()
    {
        Timer<Duration>::start();
    }
};
