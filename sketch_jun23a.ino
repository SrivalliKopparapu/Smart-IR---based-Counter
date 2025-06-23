#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define ENTRY_SENSOR 2
#define EXIT_SENSOR 3
int count = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  pinMode(ENTRY_SENSOR, INPUT);
  pinMode(EXIT_SENSOR, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("People Count:");
  lcd.setCursor(0, 1);
  lcd.print(count);
  Serial.begin(9600);
}
void loop() {
  if (digitalRead(ENTRY_SENSOR) == LOW) {
    delay(500);
    if (digitalRead(ENTRY_SENSOR) == LOW) {
      count++;
      updateLCD();
      Serial.println("Person Entered");
    }
    while (digitalRead(ENTRY_SENSOR) == LOW);
  }
  if (digitalRead(EXIT_SENSOR) == LOW) {
    delay(500);
    if (digitalRead(EXIT_SENSOR) == LOW) {
      if (count > 0) {
        count--;
        updateLCD();
        Serial.println("Person Exited");
      }
    }
    while (digitalRead(EXIT_SENSOR) == LOW);
  }
}
void updateLCD() {
  lcd.setCursor(0, 1);
  lcd.print("         "); 
  lcd.setCursor(0, 1);
  lcd.print(count);
}
