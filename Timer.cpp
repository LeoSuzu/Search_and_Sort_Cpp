#include "Timer.h"

Timer::Timer()
{
    start_time = clock();
}

double Timer::elapsed_time() const
{
    clock_t end_time = clock();
    return ((double)(end_time - start_time)) / ((double)CLK_TCK);
}

void Timer::reset()
{
    start_time = clock();
}
