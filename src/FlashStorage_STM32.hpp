/******************************************************************************************************************************************
  FlashStorage_STM32.hpp
  For STM32 using Flash emulated-EEPROM

  The FlashStorage_STM32 library aims to provide a convenient way to store and retrieve user's data using the non-volatile flash memory
  of STM32F/L/H/G/WB/MP1. It's using the buffered read and write to minimize the access to Flash.
  It now supports writing and reading the whole object, not just byte-and-byte.

  Inspired by Cristian Maglie's FlashStorage (https://github.com/cmaglie/FlashStorage)

  Built by Khoi Hoang https://github.com/khoih-prog/FlashStorage_STM32
  Licensed under MIT license
  Version: 1.2.0

  Version Modified By   Date        Comments
  ------- -----------  ----------   -----------
  1.0.0   K Hoang      26/01/2021  Initial coding to support STM32F/L/H/G/WB/MP1 using emulated-EEPROM
  1.0.1   K Hoang      23/02/2021  Fix compiler warnings.
  1.1.0   K Hoang      26/04/2021  Add support to new STM32 core v2.0.0 and new STM32L5 boards.
  1.2.0   K Hoang      25/01/2022  Fix `multiple-definitions` linker error
  ******************************************************************************************************************************************/

// The .hpp contains only definitions, and can be included as many times as necessary, without `Multiple Definitions` Linker Error
// The .h contains implementations, and can be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error

#pragma once

#ifndef FlashStorage_STM32_hpp
#define FlashStorage_STM32_hpp

#ifndef FLASH_STORAGE_STM32_VERSION
  #define FLASH_STORAGE_STM32_VERSION            "FlashStorage_STM32 v1.2.0"

  #define FLASH_STORAGE_STM32_VERSION_MAJOR      1
  #define FLASH_STORAGE_STM32_VERSION_MINOR      2
  #define FLASH_STORAGE_STM32_VERSION_PATCH      0

  #define FLASH_STORAGE_STM32_VERSION_INT        1002000

#endif

#include <Arduino.h>

// Only use this with emulated EEPROM, without integrated EEPROM
#if !defined(DATA_EEPROM_BASE)

#include "utility/stm32_eeprom.hpp"

  class EEPROMClass
  {
    public:
    
      EEPROMClass() : _initialized(false), _dirtyBuffer(false), _commitASAP(true) , _validEEPROM(true) {}

      /**
       * Read an eeprom cell
       * @param index
       * @return value
       */
      uint8_t read(const int& address)
      {
        if (!_initialized) 
          init();
          
        return eeprom_buffered_read_byte(address);
      }
      
      /**
       * Update an eeprom cell
       * @param index
       * @param value
       */
      void update(const int& address, const uint8_t& value)
      {
        if (!_initialized) 
          init();
          
        if (eeprom_buffered_read_byte(address) != value)
        {
          _dirtyBuffer = true;
          eeprom_buffered_write_byte(address, value);
        }
      }

      /**
       * Write value to an eeprom cell
       * @param index
       * @param value
       */
      void write(const int& address, const uint8_t& value)
      {
        update(address, value);
      }
     
      /**
       * Update eeprom cells from an object
       * @param index
       * @param value
       */
      //Functionality to 'get' and 'put' objects to and from EEPROM.
      template< typename T > T &get( const int& idx, T &t )
      {       
        // Copy the data from the flash to the buffer if not yet
        if (!_initialized) 
          init();
          
        uint16_t offset = idx;
        uint8_t* _pointer = (uint8_t *) &t;
        
        for ( uint16_t count = sizeof(T) ; count ; --count, ++offset )
        {  
          *_pointer++ = eeprom_buffered_read_byte(offset);
        }
          
        return t;
      }
      
      template< typename T > const T &put( const int& idx, const T &t )
      {            
        // Copy the data from the flash to the buffer if not yet
        if (!_initialized) 
          init();
        
        uint16_t offset = idx;
           
        const uint8_t* _pointer = (const uint8_t *) &t;
        
        for ( uint16_t count = sizeof(T) ; count ; --count, ++offset )
        {              
          eeprom_buffered_write_byte(offset, *_pointer++);
        }

        if (_commitASAP)
        {
          // Save the data from the buffer to the flash right away
          eeprom_buffer_flush();
          
          _dirtyBuffer = false;
          _validEEPROM = true;
        }
        else  
        {
          // Delay saving the data from the buffer to the flash. Just flag and wait for commit() later
          _dirtyBuffer = true;    
        }
             
        return t;
      }

      /**
       * Check whether the eeprom data is valid
       * @return true, if eeprom data is valid (has been written at least once), false if not
       */
      bool isValid()
      {         
        return _validEEPROM;
      }

      /**
       * Write previously made eeprom changes to the underlying flash storage
       * Use this with care: Each and every commit will harm the flash and reduce it's lifetime (like with every flash memory)
       */
      void commit()
      {
        if (!_initialized) 
          init();
          
        if (_dirtyBuffer) 
        {
          // Save the data from the buffer to the flash
          eeprom_buffer_flush();
          
          _dirtyBuffer = false;
          _validEEPROM = true;
        }
      }

      uint16_t length() { return E2END + 1; }
      
      void setCommitASAP(bool value = true) { _commitASAP = value; }
      bool getCommitASAP() { return _commitASAP; }

    private:
    
      void init()
      {
        // Copy the data from the flash to the buffer
        eeprom_buffer_fill();       
        _initialized = true;
      }

      bool _initialized;     
      bool _dirtyBuffer;
      bool _commitASAP;
      bool _validEEPROM;
  };
  
  static EEPROMClass EEPROM;

#else

  #include "EEPROM.h"
  
#endif    // #if !defined(DATA_EEPROM_BASE)

#endif    //#ifndef FlashStorage_STM32_hpp
