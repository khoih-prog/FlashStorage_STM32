/******************************************************************************************************************************************
  EEPROM_iteration.ino
  For STM32 using Flash emulated-EEPROM

  The FlashStorage_STM32 library aims to provide a convenient way to store and retrieve user's data using the non-volatile flash memory
  of STM32F/L/H/G/WB/MP1. It's using the buffered read and write to minimize the access to Flash.
  It now supports writing and reading the whole object, not just byte-and-byte.

  Inspired by Cristian Maglie's FlashStorage (https://github.com/cmaglie/FlashStorage)

  Built by Khoi Hoang https://github.com/khoih-prog/FlashStorage_STM32
  Licensed under MIT license
  Version: 1.1.0

  Version Modified By   Date        Comments
  ------- -----------  ----------   -----------
  1.0.0   K Hoang      26/01/2021  Initial coding to support STM32F/L/H/G/WB/MP1 using emulated-EEPROM
  1.0.1   K Hoang      23/02/2021  Fix compiler warnings.
  1.1.0   K Hoang      26/04/2021  Add support to new STM32 core v2.0.0 and new STM32L5 boards.
 ******************************************************************************************************************************************/
/***
    eeprom_iteration example.

    A set of example snippets highlighting the simplest methods for traversing the EEPROM.

    Running this sketch is not necessary, this is simply highlighting certain programming methods.

    Written by Christopher Andrews 2015
    Released under MIT licence.
***/

#include <FlashStorage_STM32.h>

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  delay(200);

  Serial.print(F("\nStart EEPROM_iteration on ")); Serial.println(BOARD_NAME);
  Serial.println(FLASH_STORAGE_STM32_VERSION);

  Serial.print("EEPROM length: ");
  Serial.println(EEPROM.length());

  /***
    Iterate the EEPROM using a for loop.
  ***/

  for (int index = 0 ; index < EEPROM.length() ; index++) 
  {
    // Add one to each cell in the EEPROM
    EEPROM.write(index, EEPROM.read(index) + 1);
  }

  EEPROM.commit();

  Serial.println("Done for loop");

  /***
    Iterate the EEPROM using a while loop.
  ***/

  int index = 0;

  while (index < EEPROM.length()) 
  {
    //Add one to each cell in the EEPROM
    // Add one to each cell in the EEPROM
    EEPROM.write(index, EEPROM.read(index) + 1);
    index++;
  }

  EEPROM.commit();

  Serial.println("Done while loop");

  /***
    Iterate the EEPROM using a do-while loop.
  ***/

  int idx = 0;  //Used 'idx' to avoid name conflict with 'index' above.

  do 
  {
    //Add one to each cell in the EEPROM
    // Add one to each cell in the EEPROM
    EEPROM.write(index, EEPROM.read(index) + 1);
    idx++;
  } while (idx < EEPROM.length());

  EEPROM.commit();

  Serial.println("Done do-while loop");
  
} //End of setup function.

void loop() {}
