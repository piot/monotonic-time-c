#include <clog/clog.h>
#ifndef TORNADO_OS_WINDOWS
#include <monotonic-time/monotonic_time.h>
#endif

#if TORNADO_OS_WINDOWS
#include <WinSock2.h>
#else
#include <sys/time.h>
#endif
#include <time.h>


static inline uint64_t timespecToNanoSeconds(const struct timespec* t)
{
    return t->tv_sec * 1000000000 + t->tv_nsec;
}

static inline uint64_t timevalToMilliseconds(const struct timeval* t)
{
    return t->tv_sec * 1000 + t->tv_usec / 1000;
}


MonotonicTimeMs monotonicTimeMsNow()
{
#if 1
    struct timespec time;
    int ret = clock_gettime(CLOCK_MONOTONIC_RAW, &time);
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
    int ret = clock_gettime(CLOCK_MONOTONIC_RAW, &time);
    if (ret != 0) {
        CLOG_ERROR("couldn't gettime");
    }

    return time.tv_sec * 10e9  + time.tv_nsec;
}

#endif
