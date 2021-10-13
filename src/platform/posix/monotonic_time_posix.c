#ifndef TORNADO_OS_WINDOWS
#include <clog/clog.h>
#include <monotonic-time/monotonic_time.h>

#include <sys/time.h>
#include <time.h>


static inline uint64_t timespecToNanoSeconds(const struct timespec* t)
{
    return t->tv_sec * 1000000000 + t->tv_nsec;
}

static inline uint64_t timevalToMilliseconds(const struct timeval* t)
{
    return t->tv_sec * 1000 + t->tv_usec / 1000;
}

#ifndef CLOCK_MONOTONIC_RAW
#define MONOTONIC_TIME_TO_USE CLOCK_MONOTONIC
#else
#define MONOTONIC_TIME_TO_USE CLOCK_MONOTONIC_RAW
#endif

MonotonicTimeMs monotonicTimeMsNow()
{
#if 1
    struct timespec time;

    int ret = clock_gettime(MONOTONIC_TIME_TO_USE, &time);
    if (ret != 0) {
        CLOG_ERROR("couldn't gettime");
    }

    return time.tv_sec * 1000 + time.tv_nsec / 1000000;
#else
    struct timeval tv;

    int errorCode = gettimeofday(&tv, 0);
    if (errorCode < 0) {
        return 0;
    }

    return timevalToMilliseconds(&tv);
#endif
}


MonotonicTimeNanoseconds monotonicTimeNanosecondsNow()
{
    struct timespec time;
    int ret = clock_gettime(MONOTONIC_TIME_TO_USE, &time);
    if (ret != 0) {
        CLOG_ERROR("couldn't gettime");
    }

    return time.tv_sec * 1000000000  + time.tv_nsec;
}

#endif
