#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>
#include "cycleCounter.h"


class Timer {
private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;
    uint64_t startCycles;
    uint64_t endCycles;
    double elapsedTime; // in milliseconds
    uint64_t elapsedCycles; // in cycles

public:
    Timer() : elapsedTime(0), elapsedCycles(0) {}

    void start();

    void stop();

    double getElapsedTime() const;

    uint64_t getElapsedCycles() const;

    void printElapsedTime() const;
    void printElapsedCycles() const;
    void printElapsedTimeAndCycles() const;
};

#endif // TIMER_H