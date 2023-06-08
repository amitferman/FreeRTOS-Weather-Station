/* University of Washington
 * ECE/CSE 474, 05/26/2023
 *
 * Amit Ferman
 * Austin Kennedy
 * 
 * Defines API for formatting and displaying data
 * on an LCD display.
 */

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "rtc.h"

#define rs 40
#define en 41
#define d4 42
#define d5 43
#define d6 44
#define d7 45

#define CLOUDY_WEATHER 0
#define SUNNY_WEATHER 1
#define MOON_WEATHER 2
#define RAIN_WEATHER 3

/***************************************************
* void setupLCD();
*
* Initializes the LCD display, including saving custom characters.
*/
void setupLCD();

/***************************************************
* void refreshLCD();
*
* Refreshes the LCD display with most recent data.
*/
void refreshLCD();

/***************************************************
* void scrollLCD();
*
* Updates display such that on the next refresh, it will
* shift to the right by 1.
*/
void scrollLCD();

/***************************************************
* void updateWeatherConditions(const byte b);
*   b - the weather condition, either CLOUDY_WEATHER, SUNNY_WEATHER, MOON_WEATHER, or RAIN_WEATHER
*
* Updates the weather condition character to be displayed
* on the next refresh.
*/
void updateWeatherConditions(const byte b);

/***************************************************
* void updateTemp(const uint8_t v);
*   v - the temperature in fahrenheit
*
* Updates the temperature to be displayed on the next
* refresh.
*/
void updateTemp(const uint8_t v);

/***************************************************
* void updateHumidity(const uint8_t v);
*   v - the humidity, 0 to 100
*
* Updates the humidity to be displayed on the next
* refresh.
*/
void updateHumidity(const uint8_t v);

/***************************************************
* void updateBrightness(const uint8_t v);
*   v - the brightness, 0 to 100
*
* Updates the brightness to be displayed on the next
* refresh.
*/
void updateBrightness(const uint8_t v);

/***************************************************
* void updateClock(const Clock &clock);
*   clock - the clock/time of day
*
* Updates the clock to be displayed on the next
* refresh as hours:mins:secs.
*/
void updateClock(const Clock &clock);

#endif // _DISPLAY_H_
