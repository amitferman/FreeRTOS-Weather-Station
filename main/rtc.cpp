/* University of Washington
 * ECE/CSE 474, 05/26/2023
 *
 * Amit Ferman
 * Austin Kennedy
 * 
 * Implements API for RTC module.
 */

#include "rtc.h"
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

// global time of day to save memory
static tmElements_t tm;

static const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

// Parses the time string into tm.
// Adapted from https://github.com/PaulStoffregen/DS1307RTC.
static bool getTime(const char *str) {
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

void setupClock() {
    if (getTime(__TIME__)) {
        RTC.write(tm);
    }
}

void readClock(Clock *const clock) {
    RTC.read(tm);
    clock->h = tm.Hour;
    clock->m = tm.Minute;
    clock->s = tm.Second;
}