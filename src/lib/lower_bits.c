/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <clog/clog.h>
#include <monotonic-time/lower_bits.h>

MonotonicTimeLowerBitsMs monotonicTimeMsToLowerBits(MonotonicTimeMs now)
{
    return now & 0xfffff;
}

MonotonicTimeMs monotonicTimeMsFromLowerBits(MonotonicTimeMs now, MonotonicTimeLowerBitsMs lowerBits)
{
    uint64_t nowBits = (uint64_t) (now & 0xffff);
    uint64_t receivedLowerBits = (uint64_t) lowerBits;
    uint64_t top = (uint64_t) now & 0xffffffffffff0000;

    uint64_t receivedMonotonic = top | receivedLowerBits;
    if (receivedLowerBits > nowBits) {
        receivedMonotonic -= 0x10000;
    }

    uint64_t diff = (uint64_t) now - receivedMonotonic;
    if (diff > 3000) {
        CLOG_ERROR("suspicious time lower bits diff %d", diff);
    }

    return receivedMonotonic;
}
