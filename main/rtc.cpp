#include "rtc.h"

void readClock(Clock *const clock) {
    uint8_t h = 1, m = 2, s = 3; // TODO: fetch from RTC module
    clock->h = 1;
    clock->m = 2;
    clock->s = 3;
}
