/* University of Washington
 * ECE/CSE 474, 05/26/2023
 *
 * Amit Ferman
 * Austin Kennedy
 * 
 * Implements API for formatting and displaying data
 * on an LCD display.
 */

#include "display.h"

#define LCD_WIDTH 16
#define SUNNY_EMOJI byte('*')
#define CLOUDY_EMOJI byte(1) 
#define DEGREE_EMOJI byte(2) 
#define MOON_EMOJI byte(3) 
#define RAIN_EMOJI byte(4) 

// defines pixel values for cloud character
byte clouds[8] = {
    0b00000,
    0b01100,
    0b11110,
    0b00000,
    0b00110,
    0b01111,
    0b00000,
};

// defines pixel values for degree character
byte degree[8] = {
    0b00100,
    0b01010,
    0b00100,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
};

// defines pixel values for moon character
byte moon[8] = {
    0b00000,
    0b01110,
    0b11100,
    0b11000,
    0b11100,
    0b01110,
    0b00000,
};

// defines pixel values for rain character
byte rain[8] = {
    0b00000,
    0b00100,
    0b01001,
    0b00010,
    0b01000,
    0b10010,
    0b00100,
};

// display handle
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// line to display on second row
char line[] = "Temp (F): 00_ Humidity: 00_ Brightness: 00_ ";
uint8_t l = strlen(line); // cache length for faster display
int start = 0; // offset of first character, for scrolling

void setupLCD() {
    lcd.begin(16, 2);
    lcd.createChar(CLOUDY_EMOJI, clouds);
    lcd.createChar(DEGREE_EMOJI, degree);
    lcd.createChar(MOON_EMOJI, moon);
    lcd.createChar(RAIN_EMOJI, rain);
}

void refreshLCD() {
    lcd.setCursor(0, 1);
    for (int i = start; i < start + LCD_WIDTH; i++) {
        lcd.print(line[i % l]);
    }
}

void scrollLCD() {
    start++;
}

void updateBrightness(uint8_t v) {
    snprintf(line + 40, 3, "%02" PRIu8, v);
    line[42] = '%';
}

void updateTemp(uint8_t v) {
    snprintf(line + 10, 3, "%02" PRIu8, v);
    line[12] = DEGREE_EMOJI;
}

void updateHumidity(uint8_t v) {
    snprintf(line + 24, 3, "%02" PRIu8, v);
    line[26] = '%';
}

void updateClock(const Clock &clock) {
    char ts[9];
    sprintf(ts, "%02" PRIu8, clock.h);
    ts[2] = ':';
    sprintf(ts + 3, "%02" PRIu8, clock.m);
    ts[5] = ':';
    sprintf(ts + 6, "%02" PRIu8, clock.s);
    lcd.setCursor(8, 0);
    lcd.print(ts);
}

void updateWeatherConditions(byte b) {
    switch (b) {
        case SUNNY_WEATHER:
            lcd.setCursor(0, 0);
            lcd.write(SUNNY_EMOJI);
            lcd.print(' ');
            lcd.print(' ');
            break;
        case CLOUDY_WEATHER:
            lcd.setCursor(0, 0);
            lcd.write(CLOUDY_EMOJI);
            lcd.write(CLOUDY_EMOJI);
            lcd.write(CLOUDY_EMOJI);
            break;
        case MOON_WEATHER:
            lcd.setCursor(0, 0);
            lcd.write(MOON_EMOJI);
            lcd.print(' ');
            lcd.print(' ');
            break;
        case RAIN_WEATHER:
            lcd.setCursor(0, 0);
            lcd.write(RAIN_EMOJI);
            lcd.print(RAIN_EMOJI);
            lcd.print(RAIN_EMOJI);
            break;
    }
}
