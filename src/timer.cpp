#include "timer.h"

void Timer::start() {
    startTime = std::chrono::high_resolution_clock::now();
    startCycles = CycleCounter::rdtsc();
}

void Timer::stop() {
    endCycles = CycleCounter::rdtsc();
    endTime = std::chrono::high_resolution_clock::now();
    elapsedTime = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - startTime).count();
    elapsedCycles = endCycles - startCycles;
}

double Timer::getElapsedTime() const {
    return elapsedTime;
}

uint64_t Timer::getElapsedCycles() const {
    return elapsedCycles;
}

void Timer::printElapsedTime() const {
    std::cout << "Elapsed time: " << elapsedTime << " ms" << std::endl;
}

void Timer::printElapsedCycles() const {
    std::cout << "Elapsed cycles: " << elapsedCycles << std::endl;
}

void Timer::printElapsedTimeAndCycles() const {
    std::cout << "Elapsed time:   " << elapsedTime << " ms" << std::endl;
    std::cout << "Elapsed cycles: " << elapsedCycles << std::endl;
}
