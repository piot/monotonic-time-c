#include <monotonic-time/monotonic_time.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    MonotonicTimeMs now = monotonicTimeMicrosecondsNow();
    printf("testing\n");

    MonotonicTimeMs after = monotonicTimeMicrosecondsNow();
    printf("%lu %lu %lu", now, after, after - now);
    return 0;
}