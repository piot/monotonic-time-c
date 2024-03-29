/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef MONOTONIC_TIME_H
#define MONOTONIC_TIME_H

#include <stdint.h>

typedef int64_t MonotonicTimeMs;

MonotonicTimeMs monotonicTimeMsNow(void);

typedef int64_t MonotonicTimeNanoseconds;

typedef int64_t MonotonicTimestamp;

MonotonicTimeNanoseconds monotonicTimeNanosecondsNow(void);

#define MONOTONIC_NS_TO_MS(time) ((time) / 1000000)

#endif
