# FlashStorage_STM32 Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/FlashStorage_STM32.svg?)](https://www.ardu-badge.com/FlashStorage_STM32)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/FlashStorage_STM32.svg)](https://github.com/khoih-prog/FlashStorage_STM32/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/FlashStorage_STM32/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/FlashStorage_STM32.svg)](http://github.com/khoih-prog/FlashStorage_STM32/issues)

---
---

## Table of Contents

* [Why do we need this FlashStorage_STM32 library](#why-do-we-need-this-FlashStorage_STM32-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](#changelog)
  * [Releases v1.0.1](#releases-v101)
  * [Releases v1.0.0](#releases-v100)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Limited number of writes](#limited-number-of-writes)
* [Usage](#usage)
  * [Using the alternative EEPROM-like API](#using-the-alternative-eeprom-like-api)
* [Examples](#examples)
  * [  1. EEPROM_Clear](examples/EEPROM_Clear)
  * [  2. EEPROM_CRC](examples/EEPROM_CRC)
  * [  3. EEPROM_get](examples/EEPROM_get)
  * [  4. EEPROM_iteration](examples/EEPROM_iteration)
  * [  5. EEPROM_put](examples/EEPROM_put)
  * [  6. EEPROM_read](examples/EEPROM_read)
  * [  7. EEPROM_update](examples/EEPROM_update)
  * [  8. EEPROM_write](examples/EEPROM_write)
  * [  9. **EmulateEEPROM**](examples/EmulateEEPROM)
  * [ 10. **FlashStoreAndRetrieve**](examples/FlashStoreAndRetrieve)
  * [ 11. **StoreNameAndSurname**](examples/StoreNameAndSurname)
* [Examples from other libraries](#examples-from-other-libraries)
  * [  1. Library WiFiManager_Generic_Lite](#1-library-wifimanager_generic_lite)
  * [  2. Library WiFiManager_NINA_Lite](#2-library-wifimanager_nina_lite)
  * [  3. Library Ethernet_Manager_STM32](#3-library-ethernet_manager_stm32) 
* [Example StoreNameAndSurname](#example-storenameandsurname)
* [FAQ](#faq)
  * [Can I use a single object to store more stuff?](#can-i-use-a-single-object-to-store-more-stuff)
  * [The content of the FlashStorage is erased each time a new sketch is uploaded?](#the-content-of-the-flashstorage-is-erased-each-time-a-new-sketch-is-uploaded)
  * [Do you recommend to use FLASH instead of EEPROM?](#do-you-recommend-to-use-flash-instead-of-eeprom)
* [Troubleshooting](#troubleshooting)
* [Releases](#releases)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Why do we need this [FlashStorage_STM32 library](https://github.com/khoih-prog/FlashStorage_STM32)

### Features

The FlashStorage_STM32 library, inspired by [Cristian Maglie's FlashStorage](https://github.com/cmaglie/FlashStorage), provides a convenient way to store and retrieve user's data using emulated-EEPROM, from the non-volatile flash memory of STM32F/L/H/G/WB/MP1.

The flash memory, generally used to store the firmware code, can also be used to store / retrieve more user's data and faster than from EEPROM. Thanks to the **buffered data writing and reading**, the flash access time is greatly reduced to **increase the life of the flash**.

### Currently supported Boards

1. **STM32F/L/H/G/WB/MP1 boards with / without integrated EEPROM**

- Nucleo-144
- Nucleo-64
- Nucleo-32
- Discovery
- Generic STM32F0, STM32F1, STM32F2, STM32F3, STM32F4, STM32F7
- STM32L0, STM32L1, STM32L4
- STM32G0, STM32G4
- STM32H7
- STM32WB
- STM32MP1
- LoRa boards
- 3-D printer boards
- Generic Flight Controllers
- Midatronics boards

---
---

## Changelog

### Releases v1.0.1

1. Fix compiler warnings.

### Releases v1.0.0

1. Initial release to support STM32F/L/H/G/WB/MP1 board with / without integrated EEPROM


---
---

## Prerequisites

 1. [`Arduino IDE 1.8.13+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Arduino Core for STM32 v1.9.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32 boards. [![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)

---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**FlashStorage_STM32**](https://github.com/khoih-prog/FlashStorage_STM32), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/FlashStorage_STM32.svg?)](https://www.ardu-badge.com/FlashStorage_STM32) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**FlashStorage_STM32**](https://github.com/khoih-prog/FlashStorage_STM32) page.
2. Download the latest release `FlashStorage_STM32-main.zip`.
3. Extract the zip file to `FlashStorage_STM32-main` directory 
4. Copy whole `FlashStorage_STM32-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**FlashStorage_STM32** library](https://platformio.org/lib/show/11728/FlashStorage_STM32) by using [Library Manager](https://platformio.org/lib/show/11728/FlashStorage_STM32/installation). Search for **FlashStorage_STM32** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---
---

## Limited number of writes

The flash memory has a limited amount of write cycles. Typical flash memories can perform about 10000 writes cycles to the same flash block before starting to "wear out" and begin to lose the ability to retain data.

So **BEWARE: IMPROPER USE OF THIS LIBRARY CAN QUICKLY AND PERMANENTLY DESTROY THE FLASH MEMORY OF YOUR MICRO**, in particular you should avoid to call the `put()` or`commit()` functions too often and make sure that in the entire life of the micro the number of calls to `put()` or`commit()` stay well below the above limit of 10000 (it's a good rule-of-thumb to keep that number in mind even if the manufacturer of the micro guarantees a bigger number of cycles).


---
---

## Usage

### Using the alternative EEPROM-like API

Include `FlashStorage_STM32.h` to get an EEPROM emulation with the internal flash memory.

See [EmulateEEPROM](examples/EmulateEEPROM) sketch for an example.

The API is very similar to the well known Arduino EEPROM.h API but with 4 additional functions:

* `bool isValid()` returns `true` if data in the emulated-EEPROM is valid (the data written to flash at least once by `EEPROM.commit()` or `EEPROM.put()`). Otherwise emulated-EEPROM data is "undefined" and the function returns `false`.
* `void commit()` store the EEPROM data in flash. Use this with care: Every call writes the complete emulated-EEPROM data to flash. This will reduce the remaining flash-write-cycles. Don't call this method in a loop or [you will kill your flash soon](#limited-number-of-writes).
* `void setCommitASAP(bool value = true)` to set or clear the `_commitASAP` private variable (default is `true` to be safe). If _commitASAP is false, the call to `EEPROM.put()` won't force the `EEPROM.commit()` to extend the flash life. You'll have to remember to call `EEPROM.commit()` manually to save the emulated-EEPROM data into flash or data will be lost.
* `bool getCommitASAP()` to return the current value of `_commitASAP`.

---
---

### Examples

 1. [EEPROM_Clear](examples/EEPROM_Clear)
 2. [EEPROM_CRC](examples/EEPROM_CRC)
 3. [EEPROM_get](examples/EEPROM_get)
 4. [EEPROM_iteration](examples/EEPROM_iteration)
 5. [EEPROM_put](examples/EEPROM_put)
 6. [EEPROM_read](examples/EEPROM_read)
 7. [EEPROM_update](examples/EEPROM_update)
 8. [EEPROM_write](examples/EEPROM_write)
 9. [EmulateEEPROM](examples/EmulateEEPROM)
10. [FlashStoreAndRetrieve](examples/FlashStoreAndRetrieve)
11. [StoreNameAndSurname](examples/StoreNameAndSurname)


### Examples from other libraries

### 1. Library [WiFiManager_Generic_Lite](https://github.com/khoih-prog/WiFiManager_Generic_Lite)

 1. [STM32_WiFi](https://github.com/khoih-prog/WiFiManager_Generic_Lite/tree/main/examples/STM32_WiFi)
 2. [STM32_WiFi_MQTT](https://github.com/khoih-prog/WiFiManager_Generic_Lite/tree/main/examples/STM32_WiFi_MQTT)
 
### 2. Library [WiFiManager_NINA_Lite](https://github.com/khoih-prog/WiFiManager_NINA_Lite)

 1. [STM32_WiFiNINA](https://github.com/khoih-prog/WiFiManager_NINA_Lite/tree/main/examples/STM32_WiFiNINA)
 2. [STM32_WiFiNINA_MQTT](https://github.com/khoih-prog/WiFiManager_NINA_Lite/tree/main/examples/STM32_WiFiNINA_MQTT)
 
### 3. Library [Ethernet_Manager_STM32](https://github.com/khoih-prog/Ethernet_Manager_STM32)

 1. [AM2315_Ethernet_STM32](https://github.com/khoih-prog/Ethernet_Manager_STM32/tree/main/examples/AM2315_Ethernet_STM32)
 2. [DHT11_Ethernet_STM32](https://github.com/khoih-prog/Ethernet_Manager_STM32/tree/main/examples/DHT11_Ethernet_STM32)
 3. [Ethernet_STM32](https://github.com/khoih-prog/Ethernet_Manager_STM32/tree/main/examples/Ethernet_STM32)
 4. [MQTT_ThingStream_Ethernet_STM32](https://github.com/khoih-prog/Ethernet_Manager_STM32/tree/main/examples/MQTT_ThingStream_Ethernet_STM32)
 
and mamy more to come.

---
---

### Example [StoreNameAndSurname](examples/StoreNameAndSurname)


```cpp
// Demonstrate how to use FlashStorage_STM32 with an API that is similar to the EEPROM library to Store and retrieve structured data.

#include <FlashStorage_STM32.h>

const int WRITTEN_SIGNATURE = 0xBEEFDEED;

// Create a structure that is big enough to contain a name
// and a surname. The "valid" variable is set to "true" once
// the structure is filled with actual data for the first time.
typedef struct
{
  char name[100];
  char surname[100];
} Person;

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  delay(200);

  Serial.print(F("\nStart StoreNameAndSurname on ")); Serial.println(BOARD_NAME);
  Serial.println(FLASH_STORAGE_STM32_VERSION);

  Serial.print("EEPROM length: ");
  Serial.println(EEPROM.length());

  // Check signature at address 0
  int signature;

  // Create a "Person" variable and call it "owner"
  uint16_t storedAddress = 0;
  Person owner;

  EEPROM.get(storedAddress, signature);

  // If the EEPROM is empty then no WRITTEN_SIGNATURE
  if (signature == WRITTEN_SIGNATURE)
  {
    EEPROM.get(storedAddress + sizeof(signature), owner);

    // Say hello to the returning user!
    Serial.print("Hi "); Serial.print(owner.name); Serial.print(" "); Serial.print(owner.surname);
    Serial.println(", nice to see you again :-)");

    Serial.println("Clearing WRITTEN_SIGNATURE for next try");

    EEPROM.put(0, 0);
    Serial.println("Done clearing signature in emulated EEPROM. You can reset now");
  }
  else
  {
    Serial.println("EEPROM is empty, writing WRITTEN_SIGNATURE and some example data:");

    EEPROM.put(storedAddress, WRITTEN_SIGNATURE);

    // ...in this case we ask for user data.
    Serial.setTimeout(30000);
    Serial.print("Insert your name : ");
    String name = Serial.readStringUntil('\n');
    Serial.println(name);
    Serial.print("Insert your surname : ");
    String surname = Serial.readStringUntil('\n');
    Serial.println(surname);

    // Fill the "owner" structure with the data entered by the user...
    name.toCharArray(owner.name, 100);
    surname.toCharArray(owner.surname, 100);

    // ...and finally save everything into emulated-EEPROM
    EEPROM.put(storedAddress + sizeof(signature), owner);

    // Print a confirmation of the data inserted.
    Serial.print("<< Your name: "); Serial.print(owner.name);
    Serial.print(". Your surname: "); Serial.print(owner.surname);
    Serial.println(" >> have been saved. Thank you!");
  }
}

void loop()
{
  // Do nothing...
}
```

---
---


## FAQ

### Can I use a single object to store more stuff?

Yes, you can declare a `struct` with more fields and call a `EEPROM.put()` to store the entire structure. See the [StoreNameAndSurname](examples/StoreNameAndSurname) for how to do it.

### The content of the FlashStorage is erased each time a new sketch is uploaded?

Not with STM32.

### Do you recommend to use FLASH instead of EEPROM?

No. If your board provides an integrated-EEPROM, it's advisable to use that because EEPROM has longer lifetime, number of write cycles, etc.).

In the absence of an integrated-EEPROM or its size is too small for your use-case, you can use this library to use a small portion flash memory as emulated-EEPROM, provided that you keep in mind the limits as in [Limited number of writes](#limited-number-of-writes)

---
---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.

---
---

## Releases

### Releases v1.0.1

1. Fix compiler warnings.

### Releases v1.0.0

1. Initial release to support STM32F/L/H/G/WB/MP1 board with / without integrated EEPROM

### Currently supported Boards

1. **STM32F/L/H/G/WB/MP1 boards with / without integrated EEPROM**

- Nucleo-144
- Nucleo-64
- Nucleo-32
- Discovery
- Generic STM32F0, STM32F1, STM32F2, STM32F3, STM32F4, STM32F7
- STM32L0, STM32L1, STM32L4
- STM32G0, STM32G4
- STM32H7
- STM32WB
- STM32MP1
- LoRa boards
- 3-D printer boards
- Generic Flight Controllers
- Midatronics boards

---
---

### Issues

Submit issues to: [FlashStorage_STM32 issues](https://github.com/khoih-prog/FlashStorage_STM32/issues)

---

### TO DO

1. Search for bug and improvement.
2. Similar features for remaining Arduino boards

---

### DONE

1. Basic emulated-EEPROM for STM32F/L/H/G/WB/MP1.
2. Similar features for remaining Arduino boards such as SAMD21, SAMD51, etc.
3. Add Table of Contents

---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.

1. Inspired by [Cristian Maglie's FlashStorage](https://github.com/cmaglie/FlashStorage).

<table>
  <tr>
    <td align="center"><a href="https://github.com/cmaglie"><img src="https://github.com/cmaglie.png" width="100px;" alt="cmaglie"/><br /><sub><b>⭐️ Cristian Maglie</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/FlashStorage_STM32/blob/main/LICENSE)

---

### Copyright

Copyright 2021- Khoi Hoang

