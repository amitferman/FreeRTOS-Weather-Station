#include "sensors.h"

DHT dht(DHTPIN, DHTTYPE);

void setupSensors() {
    dht.begin();
}

uint8_t readDHTFahrenheit() {
    return dht.readTemperature(true);
}

uint8_t readDHTHumidity() {
    return dht.readHumidity();
}

uint8_t readBrightness() {
    return round((double) analogRead(A0) / 10.23);
}
