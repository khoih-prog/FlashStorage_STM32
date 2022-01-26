/******************************************************************************************************************************************
  EEPROM_Clear.ino
  For STM32 using Flash emulated-EEPROM

  The FlashStorage_STM32 library aims to provide a convenient way to store and retrieve user's data using the non-volatile flash memory 
  of STM32F/L/H/G/WB/MP1. It's using the buffered read and write to minimize the access to Flash. 
  It now supports writing and reading the whole object, not just byte-and-byte.

  Inspired by Cristian Maglie's FlashStorage (https://github.com/cmaglie/FlashStorage)

  Built by Khoi Hoang https://github.com/khoih-prog/FlashStorage_STM32
  Licensed under MIT license
 ******************************************************************************************************************************************/

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <FlashStorage_STM32.h>

void setup() 
{
  Serial.begin(115200);
  while (!Serial);

  delay(200);

  Serial.print(F("\nStart EEPROM_Clear on ")); Serial.println(BOARD_NAME);
  Serial.println(FLASH_STORAGE_STM32_VERSION);
  
  // initialize the LED pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.print("Emulated EEPROM length (bytes) = "); Serial.println(EEPROM.length());

  unsigned long startMillis = millis();
  
  for (int i = 0 ; i < EEPROM.length() ; i++) 
  {
    EEPROM.write(i, 0);
  }

  EEPROM.commit();

  // The time spent can be very short (4-5ms) if the EEPROM is not dirty.
  // For F767ZI, the time is around 1.1s for 16384 bytes of emulated-EEPROM
  Serial.print("Done clearing emulated EEPROM. Time spent (ms) = "); Serial.println(millis() - startMillis);

  // turn the LED on when we're done
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() 
{
  /** Empty loop. **/
}
