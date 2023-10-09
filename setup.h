#include <LiquidCrystal.h>
#include <Wire.h>
#include "definitions21.h"

LiquidCrystal lcd(38, 40, 42, 44, 46, 48);

void mode24heures() {
  Wire.beginTransmission(RTC);
  Wire.write(REGISTRE_HRS);
  Wire.endTransmission(false);
  Wire.requestFrom(RTC, 1, true);
  byte reg = Wire.read();

  reg &= ~(1 << 5); // Bit 5 dans le registre 0x02 (heures): HIGH = 12h / LOW = 24H

  Wire.beginTransmission(RTC);
  Wire.write(REGISTRE_HRS);
  Wire.write(reg);
  Wire.endTransmission(true);
}

void LeSetup() {
  lcd.begin(16,2);
  Wire.begin();
  
  pinMode(JOY_SW_PIN, INPUT);
  digitalWrite(JOY_SW_PIN, HIGH);

  pinMode(LCD_LED_PIN, OUTPUT);
  digitalWrite(LCD_LED_PIN, HIGH);

  pinMode(SW_S2_PIN, INPUT);
  digitalWrite(SW_S2_PIN, HIGH);

  pinMode(SW_S3_PIN, INPUT);
  digitalWrite(SW_S3_PIN, HIGH);

  pinMode(SW_S4_PIN, INPUT);
  digitalWrite(SW_S4_PIN, HIGH);

  mode24heures();
}
