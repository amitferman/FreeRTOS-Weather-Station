/* University of Washington
 * ECE/CSE 474, 05/26/2023
 *
 * Amit Ferman
 * Austin Kennedy
 * 
 * Defines API for DHT11 sensor (temperature and humidity)
 * and photocell (brightness).
 */

#ifndef _DHT_H_
#define _DHT_H_

#include <Arduino.h>
#include <DHT_U.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

/***************************************************
* void setupSensors();
*
* Initializes each sensor.
*/
void setupSensors();

/***************************************************
* uint8_t readDHTFahrenheit();
*
* Reads the temperature in Fahrenheit from the DHT11.
*/
uint8_t readDHTFahrenheit();

/***************************************************
* uint8_t readDHTHumidity();
*
* Reads the humidity (0-100) from the DHT11.
*/
uint8_t readDHTHumidity();

/***************************************************
* uint8_t readBrightness();
*
* Reads the brightness (0-100) from the photocell.
*/
uint8_t readBrightness();

#endif // _DHT_H_
