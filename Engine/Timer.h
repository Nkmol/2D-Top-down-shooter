//
// Created by Ahmad Rahimi on 1/16/18.
//

#ifndef SHOOTER_TIMER_H
#define SHOOTER_TIMER_H


#include <iostream>
#include <chrono>
#include <thread>

class Timer
{
    // alias our types for simplicity
    using clock             = std::chrono::system_clock;
    using time_point_type   = std::chrono::time_point < clock, std::chrono::milliseconds > ;
public:
    // default constructor that stores the start time
    Timer();

    // gets the time elapsed from construction.
    long GetTimePassed();

private:
    time_point_type start;
};


#endif //SHOOTER_TIMER_H
