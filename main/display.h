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

#define WEATHER_EMOJI_DEGREES byte(0)
#define WEATHER_EMOJI_CLOUDY byte(1)  


void setupLCD();

void writeWeatherEmoji(const byte b);

void writeTemp(const uint8_t v);

void writeHumidity(const uint8_t v);

void writeBrightness(const uint8_t v);

void writeClock(const Clock &clock);

#endif // _DISPLAY_H_
