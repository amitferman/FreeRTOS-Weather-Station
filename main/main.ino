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
TaskHandle_t SetupLCD_H;
TaskHandle_t RefreshLCD_H;
TaskHandle_t ReadEnv_H;
QueueHandle_t Env_QH;

void RT1_T(void *pvParameters);
void SetupLCD_T(void *pvParameters);
void RefreshLCD_T(void *pvParameters);
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
  xTaskCreate(SetupLCD_T, "SetupLCD_T", 1024, NULL, 3, &SetupLCD_H);
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

void SetupLCD_T(void *pvParameters) {
  setupClock(); // TODO : move
  setupSensors();
  setupLCD();
  xTaskCreate(RefreshLCD_T, "RefreshLCD_T", 256, NULL, 3, &RefreshLCD_H);
  vTaskDelete(NULL);
}

void RefreshLCD_T(void *pvParameters) {
  Environment env;
  uint32_t count = 0;
  for (;;) {
    if (xQueueReceive(Env_QH, &env, 1) == pdTRUE) {
      updateBrightness(env.brightness);
      updateTemp(env.temperature);
      updateHumidity(env.humidity);
      updateClock(env.clock);
      
      if (env.clock.h < 7 && env.clock.h > 20) { // 10pm to 7am
        updateWeatherConditions(MOON_WEATHER);
      } else {
        if (env.brightness > 60) {
          updateWeatherConditions(SUNNY_WEATHER);
        } else if (env.humidity > 80) {
          updateWeatherConditions(RAIN_WEATHER);
        } else {
          updateWeatherConditions(CLOUDY_WEATHER);
        }
      }

      refreshLCD();
    }

    // scrolling implemented within this task to avoid issues
    // between two tasks concurrently using the display
    if (count % 40 == 0) {
      scrollLCD();
    }
    
    vTaskDelay(15 / portTICK_PERIOD_MS); // P = 15 ms
    count++;
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
