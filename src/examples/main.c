#include <monotonic-time/monotonic_time.h>
#include <stdio.h>
#include <Windows.h>
int main(int argc, char* argv[])
{
    printf("ready...\n");
    Sleep(1000);

    printf("START!\n");
    MonotonicTimeMs nowms = monotonicTimeMsNow();
    MonotonicTimeNanoseconds now = monotonicTimeNanosecondsNow();
    Sleep(980);

    MonotonicTimeNanoseconds after = monotonicTimeNanosecondsNow();
    MonotonicTimeMs afterms = monotonicTimeMsNow();
    printf("End!\n");
    printf("\n%lu %lu %lu\n", now, after, after - now);

    printf("%lu %lu %lu\n", nowms, afterms, afterms - nowms);
    return 0;
}