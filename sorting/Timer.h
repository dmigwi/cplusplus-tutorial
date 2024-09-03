#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
    public:
        using Clock = std::chrono::steady_clock;
        using Microsecond = std::chrono::microseconds;
        using Second = std::chrono::duration<double, std::ratio<1>>;

        void reset() { m_timer = Clock::now(); }
        double elapsed () const
        {
            return std::chrono::duration_cast<Second>(Clock::now() - m_timer).count();
        }

    private:
        std::chrono::time_point<Clock> m_timer { Clock::now() };
};
#endif