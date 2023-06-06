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

void setupLCD();

void refreshLCD();

void scrollLCD();

void updateWeatherConditions(const byte b);

void updateTemp(const uint8_t v);

void updateHumidity(const uint8_t v);

void updateBrightness(const uint8_t v);

void updateClock(const Clock &clock);

#endif // _DISPLAY_H_
