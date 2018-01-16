//
// Created by Ahmad Rahimi on 1/16/18.
//

#include "Timer.h"
Timer::Timer()
{
    start = std::chrono::time_point_cast<std::chrono::milliseconds>(clock::now());
}

long Timer::GetTimePassed()
{
    // get the new time
    auto end = std::chrono::time_point_cast<std::chrono::milliseconds>(clock::now());

    // return the difference of the times
    return (end - start).count();
}