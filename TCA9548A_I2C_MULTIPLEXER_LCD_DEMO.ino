#include "Arduino.h"

// 1. for I2C communication to the LCD
#include <Wire.h>

// 2. for the LCD functions
#include <LiquidCrystal_I2C.h>

// Hexadecimal address of the LCD unit
#define I2C_ADDR 0x3F

// Tell the LCD what type we have (eg 16 x 2 or 20 x 4)
LiquidCrystal_I2C lcd1(I2C_ADDR, 16, 2);
LiquidCrystal_I2C lcd2(I2C_ADDR, 16, 2);

// Forward declaration of our print routine
void displayLCD(int channel, LiquidCrystal_I2C &LCD, long value);

// Adafruit's channel selection function
void TCAChannel(uint8_t i) {
	Wire.beginTransmission(0x70);
	Wire.write(1 << i);
	Wire.endTransmission();
}

// ------------------------------------------------------
// SETUP    SETUP    SETUP    SETUP    SETUP    SETUP
// ------------------------------------------------------
void setup()
{
	// Serial monitoring on PC (debug only)
	Serial.begin(9600);
	Wire.setClock(10000);

	// Initialise the LCD 1
	TCAChannel(7);
	lcd1.init();
	lcd1.clear();
	lcd1.noCursor();

	// Initialise the LCD 2
	TCAChannel(4);
	lcd2.init();
	lcd2.clear();
	lcd2.noCursor();
	lcd2.backlight();

	//Short pause
	delay(500);
}

// ------------------------------------------------------
// LOOP    LOOP    LOOP    LOOP    LOOP    LOOP    LOOP
// ------------------------------------------------------
void loop() {
	static unsigned long temp1 = 0;
	static unsigned long temp2 = 100;

	displayLCD(4, lcd2, temp2);
	displayLCD(7, lcd1, temp1);

	temp1++;
	temp2++;

	delay(100);
}

void displayLCD(int channel, LiquidCrystal_I2C &LCD, long value) {
	TCAChannel(channel);

	LCD.home();
	LCD.print(value);
	LCD.setCursor(0, 1);
	LCD.print("LCD ");
	LCD.print(channel);
	LCD.print(" - ");
	LCD.print(value);
}
