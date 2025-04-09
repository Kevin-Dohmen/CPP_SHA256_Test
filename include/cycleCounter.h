#ifndef CYCLECOUNTER_H
#define CYCLECOUNTER_H

#include <cstdint> // For uint64_t

#ifdef _MSC_VER
#include <intrin.h> // For __rdtsc
#endif

class CycleCounter {
public:
    // Reads the current value of the time-stamp counter
    static inline uint64_t rdtsc() {
        #ifdef _MSC_VER // Windows
                return __rdtsc();
        #else // Linux
                unsigned int lo, hi;
                __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
                return ((uint64_t)hi << 32) | lo;
        #endif
    }
};

#endif // CYCLECOUNTER_H