/* University of Washington
 * ECE/CSE 474, 05/26/2023
 *
 * Amit Ferman
 * Austin Kennedy
 * 
 * Defines API for RTC module.
 */

#ifndef _RTC_H_
#define _RTC_H_

#include <Arduino.h>

/*
* A Clock is the 24-hour time of day.
*   h - hours
*   m - mins
*   s - secs
*/
typedef struct Clock {
  uint8_t h;
  uint8_t m;
  uint8_t s;
} Clock;

/***************************************************
* void setupClock();
*
* Initializes the RTC module.
*/
void setupClock();

/***************************************************
* void readClock(Clock *const clock);
*   clock - the Clock into which the time of day should be written
*
* Reads from the RTC module into the given Clock.
*/
void readClock(Clock *const clock);

#endif // _RTC_H_


