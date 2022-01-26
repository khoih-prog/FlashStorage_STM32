/******************************************************************************************************************************************
  EmulatedEEPROM.ino
  For STM32 using Flash emulated-EEPROM

  The FlashStorage_STM32 library aims to provide a convenient way to store and retrieve user's data using the non-volatile flash memory
  of STM32F/L/H/G/WB/MP1. It's using the buffered read and write to minimize the access to Flash.
  It now supports writing and reading the whole object, not just byte-and-byte.

  Inspired by Cristian Maglie's FlashStorage (https://github.com/cmaglie/FlashStorage)

  Built by Khoi Hoang https://github.com/khoih-prog/FlashStorage_STM32
  Licensed under MIT license
 ******************************************************************************************************************************************/

// Demonstrate how to use FlashStorage_STM32 with an API that is similar to the EEPROM library.

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <FlashStorage_STM32.h>

const int WRITTEN_SIGNATURE = 0xBEEFDEED;

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  delay(200);

  Serial.print(F("\nStart EmulatedEEPROM on ")); Serial.println(BOARD_NAME);
  Serial.println(FLASH_STORAGE_STM32_VERSION);

  Serial.print("EEPROM length: ");
  Serial.println(EEPROM.length());

  // Check signature at address 0
  int signature;

  EEPROM.get(0, signature);

  // If the EEPROM is empty then no WRITTEN_SIGNATURE
  if (signature != WRITTEN_SIGNATURE)
  {
    Serial.println("EEPROM is empty, writing WRITTEN_SIGNATURE and some example data:");

    EEPROM.put(0, WRITTEN_SIGNATURE);

    Serial.print("->");

    for (int i = sizeof(WRITTEN_SIGNATURE); i < 20; i++)
    {
      EEPROM.write(i, 100 + i);
      Serial.print(" ");
      Serial.print(100 + i);
    }

    // commit() saves all the changes to EEPROM, it must be called
    // every time the content of virtual EEPROM is changed to make
    // the change permanent.
    // This operation burns Flash write cycles and should not be
    // done too often. See readme for details:
    // https://github.com/khoih-prog/FlashStorage_SAMD#limited-number-of-writes

    EEPROM.commit();
    Serial.println("\nDone writing to emulated EEPROM. You can reset now to test");
  }
  else
  {
    EEPROM.get(0, signature);

    Serial.print("EEPROM has been written.Signature = 0x"); Serial.println(signature, HEX);

    Serial.println("Here is the content of the next 16 bytes:");

    Serial.print("->");

    for (int i = sizeof(WRITTEN_SIGNATURE); i < 20; i++)
    {
      Serial.print(" ");
      Serial.print(EEPROM.read(i));
    }

    Serial.println("\nClearing WRITTEN_SIGNATURE for next try");

    EEPROM.put(0, 0);

    //EEPROM.commit();
    Serial.println("Done clearing signature in emulated EEPROM. You can reset now");
  }
}

void loop()
{
}
