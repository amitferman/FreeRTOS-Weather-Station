/* University of Washington
 * ECE/CSE 474, 05/26/2023
 *
 * Amit Ferman
 * Austin Kennedy
 * 
 * Implements API for DHT11 sensor (temperature and humidity)
 * and photocell (brightness).
 */

#include "sensors.h"

// DHT11 handle
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
