/* University of Washington
 * ECE/CSE 474, 05/26/2023
 *
 * Amit Ferman
 * Austin Kennedy
 */

#include <Arduino_FreeRTOS.h>
#include <defs.h>
#include <types.h>
#include "queue.h"
#include "rtc.h"
#include "display.h"
#include "sensors.h"

#define LED_EXTERNAL 36

TaskHandle_t RT1_H;
TaskHandle_t WriteLCD_H;
TaskHandle_t ReadEnv_H;
QueueHandle_t Env_QH;

void RT1_T(void *pvParameters);
void WriteLCD_T(void *pvParameters);
void ReadEnv_T(void *pvParameters);

typedef struct Environment {
  Clock clock;
  uint8_t brightness;
  uint8_t temperature;
  uint8_t humidity;
} Environment;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  xTaskCreate(RT1_T, "RT1_T", 512, NULL, 3, &RT1_H);
  xTaskCreate(WriteLCD_T, "WriteLCD_T", 256, NULL, 3, &WriteLCD_H);
  xTaskCreate(ReadEnv_T, "ReadEnv_T", 512, NULL, 3, &ReadEnv_H);
  vTaskStartScheduler();
}

void loop() {}

void RT1_T(void *pvParameters) {
  pinMode(LED_EXTERNAL, OUTPUT);
  for (;;) {
    digitalWrite(LED_EXTERNAL, HIGH);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    digitalWrite(LED_EXTERNAL, LOW);
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

void WriteLCD_T(void *pvParameters) {
  setupSensors();
  setupLCD();

  Environment env;
  for (;;) {
    if (xQueueReceive(Env_QH, &env, 1) == pdTRUE) {
      writeBrightness(env.brightness);
      writeTemp(env.temperature);
      writeHumidity(env.humidity);
      writeClock(env.clock);

      writeWeatherEmoji(WEATHER_EMOJI_CLOUDY);
    }
  }
}

void ReadEnv_T(void *pvParameters) {
  Env_QH = xQueueCreate(1, sizeof(Environment));
  Environment env;
  for (;;) {
    readClock(&(env.clock));
    env.brightness = readBrightness();
    env.temperature = readDHTFahrenheit();
    env.humidity = readDHTHumidity();
    xQueueSendToBack(Env_QH, &env, 1);
  }
}
