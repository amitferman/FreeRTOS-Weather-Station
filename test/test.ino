
/* University of Washington
* ECE/CSE 474, 05/26/2023
*
* Amit Ferman
* Austin Kennedy
*
* Lab 4.2
*/

#include <LiquidCrystal.h>

#define rs 40
#define en 41
#define d4 42
#define d5 43
#define d6 44
#define d7 45

void setup() {
  Serial.begin(115200);
  
    LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
    lcd.begin(16, 2);
    lcd.setCursor(0,0);
    lcd.print("test");

}

void loop(){}

