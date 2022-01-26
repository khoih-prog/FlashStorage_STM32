/****************************************************************************************************************************
  multiFileProject.ino
  
  For STM32 using Flash emulated-EEPROM

  The FlashStorage_STM32 library aims to provide a convenient way to store and retrieve user's data using the non-volatile flash memory
  of STM32F/L/H/G/WB/MP1. It's using the buffered read and write to minimize the access to Flash.
  It now supports writing and reading the whole object, not just byte-and-byte.

  Inspired by Cristian Maglie's FlashStorage (https://github.com/cmaglie/FlashStorage)

  Built by Khoi Hoang https://github.com/khoih-prog/FlashStorage_STM32
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

// The .hpp contains only definitions, and can be included as many times as necessary, without `Multiple Definitions` Linker Error
// The .h contains implementations, and can be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error

#if !( defined(STM32F0) || defined(STM32F1)  || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1)  || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1) || defined(STM32L5) )
  #error This code is intended to run on STM32F/L/H/G/WB/MP1 platform! Please check your Tools->Board setting.  
#endif

#define FLASH_STORAGE_STM32_VERSION_MIN_TARGET      "FlashStorage_STM32 v1.2.0"
#define FLASH_STORAGE_STM32_VERSION_MIN             1002000

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "FlashStorage_STM32.h"

#include "multiFileProject.h"

void setup() 
{
  Serial.begin(115200);
  while (!Serial);
  
  Serial.println("\nStart multiFileProject");
  Serial.println(FLASH_STORAGE_STM32_VERSION);

#if defined(FLASH_STORAGE_STM32_VERSION_MIN)
  if (FLASH_STORAGE_STM32_VERSION_INT < FLASH_STORAGE_STM32_VERSION_MIN)
  {
    Serial.print("Warning. Must use this example on Version equal or later than : ");
    Serial.println(FLASH_STORAGE_STM32_VERSION_MIN_TARGET);
  }
#endif

  testEEPROM();
}

void loop() 
{
  // put your main code here, to run repeatedly:
}
