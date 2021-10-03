#ifndef MONOTONIC_TIME_H
#define MONOTONIC_TIME_H

#include <stdint.h>

typedef uint64_t MonotonicTimeMs;

MonotonicTimeMs monotonicTimeMsNow();

typedef uint64_t MonotonicTimeNanoseconds;

MonotonicTimeNanoseconds monotonicTimeNanosecondsNow();

#endif
