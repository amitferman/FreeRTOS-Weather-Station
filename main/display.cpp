#include "display.h"

#define LCD_WIDTH 16
#define SUNNY_EMOJI byte('S')
#define CLOUDY_EMOJI byte(1)  

byte clouds[8] = {
    0b00000,
    0b01100,
    0b11110,
    0b00000,
    0b00110,
    0b01111,
    0b00000,
};

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char line[] = "Temp (F): 00, Humidity: 00% Brightness: 00%";

int start = 0;

void setupLCD() {
    lcd.begin(16, 2);
    lcd.createChar(CLOUDY_EMOJI, clouds);
}

void refreshLCD() {
    lcd.setCursor(0, 1);
    for (int i = start; i < start + LCD_WIDTH; i++) {
        lcd.write(line[i % sizeof(line)]);
    }
}

void scrollLCD() {
    start++;
}

void updateBrightness(uint8_t v) {
    sprintf(line + 40, "%02" PRIu8, v);
}

void updateTemp(uint8_t v) {
    sprintf(line + 10, "%02" PRIu8, v);
}

void updateHumidity(uint8_t v) {
    sprintf(line + 24, "%02" PRIu8, v);
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
            lcd.write(SUNNY_EMOJI);
            lcd.write(SUNNY_EMOJI);
            break;
        case CLOUDY_WEATHER:
            lcd.setCursor(0, 0);
            lcd.write(CLOUDY_EMOJI);
            lcd.write(CLOUDY_EMOJI);
            lcd.write(CLOUDY_EMOJI);
            break;
    }
    
}
