#include "display.h"

byte degrees[8] = {
    0b00100,
    0b01010,
    0b00100,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
};

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

void setupLCD()
{
    lcd.begin(16, 2);

    lcd.createChar(WEATHER_EMOJI_DEGREES, degrees);
    lcd.createChar(WEATHER_EMOJI_CLOUDY, clouds);

    lcd.setCursor(10, 0);
    lcd.print(":");
    lcd.setCursor(13, 0);
    lcd.print(":");

    lcd.setCursor(3, 1);
    lcd.write(WEATHER_EMOJI_DEGREES);

    lcd.setCursor(10, 1);
    lcd.print("%");
    lcd.setCursor(15, 1);
    lcd.print("%");
}

void writeWeatherEmoji(byte b)
{
    lcd.setCursor(0, 0);
    lcd.write(b);
}

void writeBrightness(uint8_t v)
{
    lcd.setCursor(13, 1);
    lcd.print(v);
}

void writeTemp(uint8_t v)
{
    lcd.setCursor(1, 1);
    lcd.print(v);
}

void writeHumidity(uint8_t v)
{
    lcd.setCursor(8, 1);
    lcd.print(v);
}

void writeClock(const Clock &clock)
{
    lcd.setCursor(8, 0);
    lcd.print(clock.h);
    lcd.setCursor(11, 0);
    lcd.print(clock.m);
    lcd.setCursor(13, 0);
    lcd.print(clock.s);
}
