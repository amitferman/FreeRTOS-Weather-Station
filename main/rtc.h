#ifndef _RTC_H_
#define _RTC_H_

#include <Arduino.h>

typedef struct Clock {
  uint8_t h;
  uint8_t m;
  uint8_t s;
} Clock;

void readClock(Clock *const clock);

#endif // _RTC_H_


