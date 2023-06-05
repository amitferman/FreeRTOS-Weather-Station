#ifndef _DHT_H_
#define _DHT_H_

#include <Arduino.h>
#include <DHT_U.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

void setupSensors();

uint8_t readDHTFahrenheit();

uint8_t readDHTHumidity();

uint8_t readBrightness();

#endif // _DHT_H_
