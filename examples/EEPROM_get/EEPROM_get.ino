/******************************************************************************************************************************************
  EEPROM_CRC.ino
  For STM32 using Flash emulated-EEPROM

  The FlashStorage_STM32 library aims to provide a convenient way to store and retrieve user's data using the non-volatile flash memory
  of STM32F/L/H/G/WB/MP1. It's using the buffered read and write to minimize the access to Flash.
  It now supports writing and reading the whole object, not just byte-and-byte.

  Inspired by Cristian Maglie's FlashStorage (https://github.com/cmaglie/FlashStorage)

  Built by Khoi Hoang https://github.com/khoih-prog/FlashStorage_STM32
  Licensed under MIT license
 ******************************************************************************************************************************************/
/***
    eeprom_get example.

    This shows how to use the EEPROM.get() method.

    To pre-set the EEPROM data, run the example sketch eeprom_put. This sketch will run without it.
    However, the values shown will be shown from what ever is already on the EEPROM.

    This may cause the serial object to print out a large string of garbage if there is no null character
    inside one of the strings loaded.

    Written by Christopher Andrews 2015
    Released under MIT licence.
***/

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <FlashStorage_STM32.h>

struct MyObject
{
  float field1;
  byte field2;
  char name[10];
};

void secondTest()
{
  int eeAddress = sizeof(float); //Move address to the next byte after float 'f'.

  MyObject customVar; //Variable to store custom object read from EEPROM.
  EEPROM.get(eeAddress, customVar);

  Serial.println("Read custom object from EEPROM: ");
  Serial.println(customVar.field1, 5);
  Serial.println(customVar.field2);
  Serial.println(customVar.name);
}

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  delay(200);

  Serial.print(F("\nStart EEPROM_get on ")); Serial.println(BOARD_NAME);
  Serial.println(FLASH_STORAGE_STM32_VERSION);

  Serial.print("EEPROM length: ");
  Serial.println(EEPROM.length());

  float f = 0.00f;   //Variable to store data read from EEPROM.
  int eeAddress = 0; //EEPROM address to start reading from

  Serial.print("Read float from EEPROM: ");

  //Get the float data from the EEPROM at position 'eeAddress'
  EEPROM.get(eeAddress, f);
  Serial.println(f, 3);    //This may print 'ovf, nan' if the data inside the EEPROM is not a valid float.

  /***
    As get also returns a reference to 'f', you can use it inline.
    E.g: Serial.print( EEPROM.get( eeAddress, f ) );
  ***/

  /***
    Get can be used with custom structures too.
    I have separated this into an extra function.
  ***/

  secondTest(); //Run the next test.
}

void loop()
{
  /* Empty loop */
}
