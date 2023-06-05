/* University of Washington
* ECE/CSE 474, 05/26/2023
*
* Amit Ferman
* Austin Kennedy
*
* Lab 4.2
*
* 
*/

#include <Arduino_FreeRTOS.h>
#include <LiquidCrystal.h>
#include <defs.h>
#include <types.h>
#include "queue.h"
#include "semphr.h"
#include <DHT_U.h>
#include <DHT.h>


// Initialize hardware
#define LED_EXTERNAL 36
#define rs 40
#define en 41
#define d4 42
#define d5 43
#define d6 44
#define d7 45

#define DHTPIN 37
#define DHTTYPE DHT11

#define WEATHER_EMOJI_DEGREES byte(0)
#define WEATHER_EMOJI_CLOUDY byte(1)  

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
DHT dht(DHTPIN, DHTTYPE);

// FreeRTOS task handles
TaskHandle_t RT1_Handle;
TaskHandle_t RefreshLCD_Handle;
TaskHandle_t SampleTime_Handle;
TaskHandle_t SampleBrightness_Handle;
TaskHandle_t SampleTemp_Handle;
TaskHandle_t SampleHumidity_Handle;

// FreeRTOS queue handles
QueueHandle_t Time_Handle;
QueueHandle_t Brightness_Handle;
QueueHandle_t Temp_Handle;
QueueHandle_t Humidity_Handle;

typedef struct TOD {
  uint8_t h;
  uint8_t m;
  uint8_t s;
} TOD;

/***************************************************
* void RT1(void *pvParameters)
*
* See lab spec.
*/
void RT1(void *pvParameters);

/***************************************************
* void RefreshLCD(void *pvParameters)
*
* See lab spec.
*/
void RefreshLCD(void *pvParameters);

/***************************************************
* void SampleTime(void *pvParameters)
*
* See lab spec.
*/
void SampleTime(void *pvParameters);

/***************************************************
* void SampleBrightness(void *pvParameters)
*
* See lab spec.
*/
void SampleBrightness(void *pvParameters);

/***************************************************
* void SampleDHT(void *pvParameters)
*
* See lab spec.
*/
void SampleDHT(void *pvParameters);




/***************************************************
* void setupLCD()
*
* See lab spec.
*/
void setupLCD();

void writeWeatherEmoji(byte b);

void writeTemp(uint8_t v);

void writeHumidity(uint8_t v);

void setup() {
  Serial.begin(115200);
  
  while (!Serial) {} 

  xTaskCreate(
    RT1
    ,  "RT1"
    ,  512
    ,  NULL
    ,  3
    ,  &RT1_Handle );

  xTaskCreate(
    RefreshLCD
    ,  "RefreshLCD"
    ,  256
    ,  NULL
    ,  3
    ,  &RefreshLCD_Handle );

  xTaskCreate(
    SampleTime
    ,  "SampleTime"
    ,  512
    ,  NULL
    ,  3
    ,  &SampleTime_Handle );

  xTaskCreate(
    SampleBrightness
    ,  "SampleBrightness"
    ,  512
    ,  NULL
    ,  3
    ,  &SampleBrightness_Handle );

  xTaskCreate(
    SampleDHT
    ,  "SampleDHT"
    ,  512
    ,  NULL
    ,  3
    ,  &SampleTemp_Handle );

  vTaskStartScheduler();
}

void loop() {}

void RT1(void *pvParameters) {
  pinMode(LED_EXTERNAL, OUTPUT);

  for (;;) {
    digitalWrite(LED_EXTERNAL, HIGH);
    vTaskDelay( 100 / portTICK_PERIOD_MS );
    digitalWrite(LED_EXTERNAL, LOW);
    vTaskDelay( 200 / portTICK_PERIOD_MS );
  }
}


void RefreshLCD(void *pvParameters) {
  setupLCD();

  uint8_t brightness = -1;
  uint8_t temp = -1;
  uint8_t humidity = -1;
  TOD time;

  for (;;) {
    // Receive sensor data if available.
    if (xQueueReceive(Brightness_Handle, &brightness, 1) == pdTRUE) {
      writeBrightness(brightness);
    } else {
      brightness = -1;
    }

    if (xQueueReceive(Temp_Handle, &temp, 1) == pdTRUE) {
      writeTemp(temp);
    } else {
      temp = -1;
    }

     if (xQueueReceive(Humidity_Handle, &humidity, 1) == pdTRUE) {
      writeHumidity(humidity);
    } else {
      humidity = -1;
    }




    
    writeWeatherEmoji(WEATHER_EMOJI_CLOUDY);
    
    
    //int sec = (millis() - start) / 1000;
    // Serial.println("1");
    //vTaskDelay(1);
    // xQueueReceive(Time_Handle, &time, 1);
  
    // Serial.print("Refresh LCD with time: ");
    // Serial.print(time.h);
    // Serial.print(":");
    // Serial.print(time.m);
    // Serial.print(":");
    // Serial.print(time.s);
    //vTaskDelay( 200 / portTICK_PERIOD_MS );
  }
  
}

void SampleTime(void *pvParameters) {
  Time_Handle = xQueueCreate(1, sizeof(TOD));

  for (;;) {
    TOD time = {1, 1, 1};
    xQueueSendToBack(Time_Handle, &time, 1);
  }
}

void SampleBrightness(void *pvParameters) {
  Brightness_Handle = xQueueCreate(1, sizeof(uint8_t));

  for (;;) {
    uint8_t v = (uint8_t) round(analogRead(A0) / 10.23);
    xQueueSendToBack(Brightness_Handle, &v, 1);
  }
}

void SampleDHT(void *pvParameters) {
  dht.begin();

  Temp_Handle = xQueueCreate(1, sizeof(uint8_t));
  Humidity_Handle = xQueueCreate(1, sizeof(uint8_t));

  for (;;) {
    uint8_t temp = (uint8_t) dht.readTemperature(true);
    uint8_t humidity = (uint8_t) dht.readHumidity();
    xQueueSendToBack(Temp_Handle, &temp, 1);
    xQueueSendToBack(Humidity_Handle, &humidity, 1);
  }
}





void writeWeatherEmoji(byte b) {
  lcd.setCursor(0,0);
  lcd.write(b);
}

void writeBrightness(uint8_t v) {
  lcd.setCursor(13, 1);
  lcd.print(v);
} 

void writeTemp(uint8_t v) {
  lcd.setCursor(1, 1);
  lcd.print(v);
} 

void writeHumidity(uint8_t v) {
  lcd.setCursor(8, 1);
  lcd.print(v);
} 

void setupLCD() {
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
