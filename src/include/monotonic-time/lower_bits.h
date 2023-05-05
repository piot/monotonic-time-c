/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef MONOTONIC_TIME_LOWER_BITS_H
#define MONOTONIC_TIME_LOWER_BITS_H

#include <monotonic-time/monotonic_time.h>

typedef uint16_t MonotonicTimeLowerBitsMs;

MonotonicTimeLowerBitsMs monotonicTimeMsToLowerBits(MonotonicTimeMs now);
MonotonicTimeMs monotonicTimeMsFromLowerBits(MonotonicTimeMs now, MonotonicTimeLowerBitsMs lowerBits);

#endif
