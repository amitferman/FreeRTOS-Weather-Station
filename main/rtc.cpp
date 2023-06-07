#include "rtc.h"
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

tmElements_t tm;

const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}

void setupClock() {
    bool parse = false;
    bool config = false;
    if (getDate(__DATE__) && getTime(__TIME__)) {
        parse = true;

        if (RTC.write(tm)) {
            config = true;
        }
    }
}

void readClock(Clock *const clock) {
    // tmElements_t tm;
    RTC.read(tm);
    clock->h = tm.Hour;
    clock->m = tm.Minute;
    clock->s = tm.Second;
}