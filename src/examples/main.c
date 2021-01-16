#include <monotonic-time/monotonic_time.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    MonotonicTimeMs now = monotonicTimeMsNow();

    printf("%lu", now);
    return 0;
}