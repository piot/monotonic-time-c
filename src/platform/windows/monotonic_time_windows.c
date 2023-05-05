/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <WinSock2.h>
#include <Windows.h>
#include <monotonic-time/monotonic_time.h>

MonotonicTimeMs monotonicTimeMsNow(void)
{
    LARGE_INTEGER startingTime;
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&startingTime);

    return startingTime.QuadPart * 1000 / frequency.QuadPart;
}

MonotonicTimeNanoseconds monotonicTimeNanosecondsNow(void)
{
    LARGE_INTEGER startingTime;
    LARGE_INTEGER frequency;

    QueryPerformanceCounter(&startingTime);
    QueryPerformanceFrequency(&frequency);

    return startingTime.QuadPart * 1000000000 / frequency.QuadPart;
}
