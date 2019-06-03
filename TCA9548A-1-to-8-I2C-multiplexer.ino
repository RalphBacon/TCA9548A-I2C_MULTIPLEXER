/**
   TCA9548 I2CScanner.pde -- I2C bus scanner for Arduino

   Based on code c. 2009, Tod E. Kurt, http://todbot.com/blog/

*/

#include "Wire.h"

#define TCAADDR 0x70

void tcaselect(uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}


// standard Arduino setup()
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Serial.println("\nTCA9548A Scanner ready!");

  for (uint8_t t = 0; t < 8; t++) {
    tcaselect(t);
    Serial.print("TCA Port #"); Serial.println(t);

    for (uint8_t addr = 0; addr <= 127; addr++) {
      
      // Don't report on the TCA9548A itself!
      if (addr == TCAADDR) continue;

      // See whether a device is on this address
      Wire.beginTransmission(addr);

      // See if something acknowledged the transmission
      int response = Wire.endTransmission();
      if (response == 0) {
        Serial.print("Found I2C 0x");  Serial.println(addr, HEX);
      }
    }

    // Slow the loop scanner down a bit
    delay(1000);
  }
  Serial.println("\nScan completed.");
}

void loop()
{
}
