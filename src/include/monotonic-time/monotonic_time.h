#ifndef MONOTONIC_TIME_H
#define MONOTONIC_TIME_H

#include <stdint.h>

typedef int64_t MonotonicTimeMs;

MonotonicTimeMs monotonicTimeMsNow(void);

typedef int64_t MonotonicTimeNanoseconds;

typedef int64_t MonotonicTimestamp;

MonotonicTimeNanoseconds monotonicTimeNanosecondsNow(void);

#endif
