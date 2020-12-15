#include <monotonic-time/monotonic_time.h>
#include <time.h>
#include <sys/time.h>

static inline uint64_t timespecToMilliSeconds(const struct timespec *t)
{
    return t->tv_sec * 1000;
}

static inline uint64_t timespecToNanoSeconds(const struct timespec *t)
{
    return t->tv_sec * 10e9 + t->tv_nsec;
}

static inline uint64_t timevalToMilliseconds(const struct timeval *t)
{
    return t->tv_sec * 1000 + t->tv_usec / 1000;
}

MonotonicTimeMs monotonicTimeMsNow()
{
#if 0
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);

#else
    struct timeval tv;

    int errorCode = gettimeofday(&tv, 0);
    if (errorCode < 0) {
        return 0;
    }

    return timevalToMilliseconds(&tv);
#endif
}
