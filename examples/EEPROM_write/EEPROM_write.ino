/******************************************************************************************************************************************
  EEPROM_write.ino
  For STM32 using Flash emulated-EEPROM

  The FlashStorage_STM32 library aims to provide a convenient way to store and retrieve user's data using the non-volatile flash memory
  of STM32F/L/H/G/WB/MP1. It's using the buffered read and write to minimize the access to Flash.
  It now supports writing and reading the whole object, not just byte-and-byte.

  Inspired by Cristian Maglie's FlashStorage (https://github.com/cmaglie/FlashStorage)

  Built by Khoi Hoang https://github.com/khoih-prog/FlashStorage_STM32
  Licensed under MIT license
 ******************************************************************************************************************************************/
/*
   EEPROM Write

   Stores values read from analog input 0 into the EEPROM. These values will stay in the EEPROM
   when the board is turned off and may be retrieved later by another sketch.
*/

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <FlashStorage_STM32.h>

// start reading from the first byte (address 0) of the EEPROM
int address = 0;

void setup()
{
  Serial.begin(115200);

  while (!Serial);

  delay(200);

  Serial.print(F("\nStart EEPROM_write on "));
  Serial.println(BOARD_NAME);
  Serial.println(FLASH_STORAGE_STM32_VERSION);

  Serial.print("EEPROM length: ");
  Serial.println(EEPROM.length());
}

void loop()
{
  unsigned long startMillis = millis();

  for (int i = 0 ; i < EEPROM.length() ; i++)
  {
    /***
      The function EEPROM.update(address, val) is equivalent to the following:

      if( EEPROM.read(address) != val )
      {
        EEPROM.write(address, val);
      }
    ***/
    EEPROM.write(i, (uint8_t) analogRead(0));
  }

  EEPROM.commit();

  Serial.print("Done writing emulated EEPROM. Time spent (ms) = ");
  Serial.println(millis() - startMillis);

  delay(60000);
}
