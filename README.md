# FlashStorage_STM32 Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/FlashStorage_STM32.svg?)](https://www.ardu-badge.com/FlashStorage_STM32)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/FlashStorage_STM32.svg)](https://github.com/khoih-prog/FlashStorage_STM32/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/FlashStorage_STM32/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/FlashStorage_STM32.svg)](http://github.com/khoih-prog/FlashStorage_STM32/issues)

---
---

## Table of Contents

* [Important Change from v1.2.0](#Important-Change-from-v120)
* [Why do we need this FlashStorage_STM32 library](#why-do-we-need-this-FlashStorage_STM32-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For STM32 boards to use LAN8720](#1-for-stm32-boards-to-use-lan8720)
  * [2. For STM32 boards to use Serial1](#2-for-stm32-boards-to-use-serial1)
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)
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
  * [ 12. **multiFileProject**](examples/multiFileProject) **New** 
* [Examples from other libraries](#examples-from-other-libraries)
  * [  1. Library WiFiManager_Generic_Lite](#1-library-wifimanager_generic_lite)
  * [  2. Library WiFiManager_NINA_Lite](#2-library-wifimanager_nina_lite)
  * [  3. Library Ethernet_Manager_STM32](#3-library-ethernet_manager_stm32)
  * [  4. Library ESP_AT_WM_Lite](#4-library-esp_at_wm_lite) 
  * [  5. Library BlynkEthernet_STM32_WM](#5-library-blynkethernet_stm32_wm) 
* [Example StoreNameAndSurname](#example-storenameandsurname)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. Ethernet_STM32_LAN8720 on BLACK_F407VE using LAN8720 Ethernet and STM32Ethernet Library](#1-ethernet_stm32_lan8720-on-black_f407ve-using-lan8720-ethernet-and-stm32ethernet-library)
    * [1.1. DoubleReset Detected => Enter Config Portal](#11-doublereset-detected--enter-config-portal)
    * [1.2. Config Data Saved => Running normally](#12-config-data-saved--running-normally)
  * [2. StoreNameAndSurname on NUCLEO_H743ZI2 with 16KB emulated-EEPROM](#2-storenameandsurname-on-nucleo_h743zi2-with-16KB-emulated-eeprom)
    * [2.1. First Start](#21-first-start)
    * [2.2. After reset](#22-after-reset)
  * [3. StoreNameAndSurname on NUCLEO_L552ZE_Q with 2KB emulated-EEPROM](#3-storenameandsurname-on-nucleo_l552ze_q-with-2KB-emulated-eeprom)
    * [3.1. First Start](#31-first-start)
    * [3.2. After reset](#32-after-reset)
  * [4. StoreNameAndSurname on NUCLEO_F767ZI with 16KB emulated-EEPROM](#4-storenameandsurname-on-nucleo_f767zi-with-16KB-emulated-eeprom)
    * [4.1. First Start](#41-first-start)
    * [4.2. After reset](#42-after-reset) 
* [FAQ](#faq)
  * [Can I use a single object to store more stuff?](#can-i-use-a-single-object-to-store-more-stuff)
  * [The content of the FlashStorage is erased each time a new sketch is uploaded?](#the-content-of-the-flashstorage-is-erased-each-time-a-new-sketch-is-uploaded)
  * [Do you recommend to use FLASH instead of EEPROM?](#do-you-recommend-to-use-flash-instead-of-eeprom)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Important Change from v1.2.0

Please have a look at [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)

---
---

### Why do we need this [FlashStorage_STM32 library](https://github.com/khoih-prog/FlashStorage_STM32)

### Features

The FlashStorage_STM32 library, inspired by [Cristian Maglie's FlashStorage](https://github.com/cmaglie/FlashStorage), provides a convenient way to store and retrieve user's data using emulated-EEPROM, from the non-volatile flash memory of STM32F/L/H/G/WB/MP1.

The flash memory, generally used to store the firmware code, can also be used to store / retrieve more user's data and faster than from EEPROM. Thanks to the **buffered data writing and reading**, the flash access time is greatly reduced to **increase the life of the flash**.

Currently, the library supports both new [**STM32 core v2.0.0+**](https://github.com/stm32duino/Arduino_Core_STM32/releases/tag/2.2.0) and previous [**STM32 core v1.9.0-**](https://github.com/stm32duino/Arduino_Core_STM32/releases/tag/1.9.0)

---

### Currently supported Boards

1. **STM32F/L/H/G/WB/MP1 boards with / without integrated EEPROM**

- Nucleo-144
- Nucleo-64
- Nucleo-32
- Discovery
- Generic STM32F0, STM32F1, STM32F2, STM32F3, STM32F4, STM32F7
- STM32L0, STM32L1, STM32L4, **STM32L5**
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

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`Arduino Core for STM32 v2.2.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32 boards. [![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)

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

### Packages' Patches

#### 1. For STM32 boards to use LAN8720

Already updated and tested with latest **STM32 core v2.2.0**

To use LAN8720 on some STM32 boards 

- **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
- **Discovery (DISCO_F746NG)**
- **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

you have to copy the files [stm32f4xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx) and [stm32f7xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system) to overwrite the old files.

Supposing the STM32 stm32 core version is 2.2.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/system/STM32F4xx/stm32f4xx_hal_conf_default.h` for STM32F4.
- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/system/STM32F7xx/stm32f7xx_hal_conf_default.h` for Nucleo-144 STM32F7.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx/stm32f4xx_hal_conf_default.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx/stm32f7xx_hal_conf_default.h


#### 2. For STM32 boards to use Serial1

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/2.2.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.2.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 2.2.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/variants/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/variants/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_L053R8/variant.h`

---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can include this `.hpp` file

```
// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "FlashStorage_STM32.hpp"     //https://github.com/khoih-prog/FlashStorage_STM32
```

in many files. But be sure to use the following `.h` file **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "FlashStorage_STM32.h"           //https://github.com/khoih-prog/FlashStorage_STM32
```

Check the new [**multiFileProject** example](examples/multiFileProject) for a `HOWTO` demo.

Have a look at the discussion in [Different behaviour using the src_cpp or src_h lib #80](https://github.com/khoih-prog/ESPAsync_WiFiManager/discussions/80)

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
12. [**multiFileProject**](examples/multiFileProject) **New** 


---

### Examples from other libraries

### 1. Library [WiFiManager_Generic_Lite](https://github.com/khoih-prog/WiFiManager_Generic_Lite)

 1. [STM32_WiFi](https://github.com/khoih-prog/WiFiManager_Generic_Lite/tree/main/examples/STM32_WiFi)
 2. [STM32_WiFi_MQTT](https://github.com/khoih-prog/WiFiManager_Generic_Lite/tree/main/examples/STM32_WiFi_MQTT)
 
### 2. Library [WiFiManager_NINA_Lite](https://github.com/khoih-prog/WiFiManager_NINA_Lite)

 1. [STM32_WiFiNINA](https://github.com/khoih-prog/WiFiManager_NINA_Lite/tree/master/examples/STM32_WiFiNINA)
 2. [STM32_WiFiNINA_MQTT](https://github.com/khoih-prog/WiFiManager_NINA_Lite/tree/master/examples/STM32_WiFiNINA_MQTT)
 
### 3. Library [Ethernet_Manager_STM32](https://github.com/khoih-prog/Ethernet_Manager_STM32)

 1. [AM2315_Ethernet_STM32](https://github.com/khoih-prog/Ethernet_Manager_STM32/tree/main/examples/AM2315_Ethernet_STM32)
 2. [DHT11_Ethernet_STM32](https://github.com/khoih-prog/Ethernet_Manager_STM32/tree/main/examples/DHT11_Ethernet_STM32)
 3. [Ethernet_STM32](https://github.com/khoih-prog/Ethernet_Manager_STM32/tree/main/examples/Ethernet_STM32)
 4. [MQTT_ThingStream_Ethernet_STM32](https://github.com/khoih-prog/Ethernet_Manager_STM32/tree/main/examples/MQTT_ThingStream_Ethernet_STM32)
 
### 4. Library [ESP_AT_WM_Lite](https://github.com/khoih-prog/ESP_AT_WM_Lite)

 1. [STM32_ESP8266Shield](https://github.com/khoih-prog/ESP_AT_WM_Lite/tree/master/examples/STM32_ESP8266Shield)
 
### 5. Library [BlynkEthernet_STM32_WM](https://github.com/khoih-prog/BlynkEthernet_STM32_WM)

 1. [BI_Ethernet_Blynk](https://github.com/khoih-prog/BlynkEthernet_STM32_WM/tree/master/examples/BI_Ethernet_Blynk)
 2. [BI_Ethernet_Blynk_Email](https://github.com/khoih-prog/BlynkEthernet_STM32_WM/tree/master/examples/BI_Ethernet_Blynk_Email)
 3. [BI_Ethernet_WM_Config](https://github.com/khoih-prog/BlynkEthernet_STM32_WM/tree/master/examples/BI_Ethernet_WM_Config)
 4. [LAN8720_Ethernet_Blynk](https://github.com/khoih-prog/BlynkEthernet_STM32_WM/tree/master/examples/LAN8720_Ethernet_Blynk)
 5. [LAN8720_Ethernet_Blynk_Email](https://github.com/khoih-prog/BlynkEthernet_STM32_WM/tree/master/examples/LAN8720_Ethernet_Blynk_Email)
 6. [LAN8720_Ethernet_WM_Config](https://github.com/khoih-prog/BlynkEthernet_STM32_WM/tree/master/examples/LAN8720_Ethernet_WM_Config)
 
     ......
 
and many more to libraries come.

---
---

### Example [StoreNameAndSurname](examples/StoreNameAndSurname)


```cpp
// Demonstrate how to use FlashStorage_STM32 with an API that is similar to the EEPROM library to Store and retrieve structured data.

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
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

### Debug Terminal Output Samples

### 1. Ethernet_STM32_LAN8720 on BLACK_F407VE using LAN8720 Ethernet and STM32Ethernet Library

The following is the sample terminal output when running example [Ethernet_STM32_LAN8720](https://github.com/khoih-prog/Ethernet_Manager_STM32/tree/main/examples/Ethernet_STM32_LAN8720) on STM32F4 BLACK_F407VE with LAN8720 Ethernet using STM32Ethernet Library.

#### 1.1 DoubleReset Detected => Enter Config Portal

```
Start Ethernet_STM32_LAN8720 on BLACK_F407VE
Ethernet Shield type : LAN8720 Ethernet & STM32Ethernet Library
Ethernet_Manager_STM32 v1.3.1
DoubleResetDetector_Generic v1.7.3

EEPROM size = 16384, start = 0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[ETM] EEPROMsz:4096
[ETM] EEPROM Length():16384
[ETM] CCSum=0xaed,RCSum=0x4d385471
[ETM] ChkCrR:CrCCsum=0x21dd,CrRCsum=0x3338
[ETM] InitCfgFile,sz=60
[ETM] SaveEEPROM,Sz=16384,DataSz=0,WCSum=0x569
[ETM] CrCCSum=0xc30
[ETM] Start connectEthernet using DHCP
[ETM] MAC:FE-98-FC-DD-D9-BA
[ETM] Dynamic IP OK, connected
[ETM] IP:192.168.2.169
[ETM] bg: isForcedConfigPortal = false
[ETM] bg:Stay forever in CP:No ConfigDat
Connected! IP address: 192.168.2.169

Your stored Credentials :
MQTT Server = blank
Port = blank
MQTT UserName = blank
MQTT PWD = blank
Subs Topics = blank
Pubs Topics = blank
HStop doubleResetDetecting
ClearFlag write = 0xd0d04321
HHHHH[ETM] h:Updating EEPROM. Please wait for reset
[ETM] SaveEEPROM,Sz=16384,DataSz=0,WCSum=0x729
[ETM] CrCCSum=0x1087
[ETM] h:Rst
```

---

#### 1.2 Config Data Saved => Running normally

<p align="center">
    <img src="https://github.com/khoih-prog/FlashStorage_STM32/blob/main/pics/ConfigPortal.png">
</p>


```
Start Ethernet_STM32_LAN8720 on BLACK_F407VE
Ethernet Shield type : LAN8720 Ethernet & STM32Ethernet Library
Ethernet_Manager_STM32 v1.3.1
DoubleResetDetector_Generic v1.7.3

EEPROM size = 16384, start = 0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[ETM] EEPROMsz:4096
[ETM] EEPROM Length():16384
[ETM] CCSum=0x729,RCSum=0x729
[ETM] ChkCrR:CrCCsum=0x1087,CrRCsum=0x1087
[ETM] CrCCSum=1087,CrRCSum=1087
[ETM] Valid Stored Dynamic Data
[ETM] ======= Start Stored Config Data =======
[ETM] Header=STM32, BoardName=Black_V407VE
[ETM] StaticIP=blank
[ETM] Start connectEthernet using DHCP
[ETM] MAC:FE-98-FD-D6-DA-BA
[ETM] Dynamic IP OK, connected
[ETM] IP:192.168.2.170
[ETM] begin:Ethernet Connected.
Connected! IP address: 192.168.2.170

Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pass
Subs Topics = Subs
Pubs Topics = Pubs
HStop doubleResetDetecting
ClearFlag write = 0xd0d04321
HSetFlag write = 0xd0d01234
[ETM] EEPROMsz:4096
[ETM] EEPROM Length():16384
[ETM] CCSum=0x729,RCSum=0x729
[ETM] ChkCrR:CrCCsum=0x1087,CrRCsum=0x1087
[ETM] CrCCSum=1087,CrRCSum=1087
[ETM] Valid Stored Dynamic Data
[ETM] ======= Start Stored Config Data =======
[ETM] Header=STM32, BoardName=Black_V407VE
[ETM] StaticIP=blank
[ETM] Start connectEthernet using DHCP
[ETM] MAC:FE-98-FD-D6-DB-BA
[ETM] Dynamic IP OK, connected
[ETM] IP:192.168.2.149
[ETM] begin:Ethernet Connected.
Connected! IP address: 192.168.2.149

Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pass
Subs Topics = Subs
Pubs Topics = Pubs
HStop doubleResetDetecting
ClearFlag write = 0xd0d04321
HHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH
HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH
HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH
HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH H
```

---

### 2. StoreNameAndSurname on NUCLEO_H743ZI2 with 16KB emulated-EEPROM

The following is the sample terminal output when running example [StoreNameAndSurname](examples/StoreNameAndSurname) on STM32H7 Nucleo-144 NUCLEO_H743ZI2

#### 2.1 First Start

```
Start StoreNameAndSurname on NUCLEO_H743ZI2
FlashStorage_STM32 v1.2.0
EEPROM length: 16384
EEPROM is empty, writing WRITTEN_SIGNATURE and some example data:
Insert your name : My_Name

Insert your surname : My_Surname

<< Your name: My_Name
. Your surname: My_Surname
 >> have been saved. Thank you!
```

#### 2.2 After reset

```
Start StoreNameAndSurname on NUCLEO_H743ZI2
FlashStorage_STM32 v1.2.0
EEPROM length: 16384
Hi My_Name
 My_Surname
, nice to see you again :-)
Clearing WRITTEN_SIGNATURE for next try
Done clearing signature in emulated EEPROM. You can reset now
```

---

### 3. StoreNameAndSurname on NUCLEO_L552ZE_Q with 2KB emulated-EEPROM

The following is the sample terminal output when running example [StoreNameAndSurname](examples/StoreNameAndSurname) on STM32L5 Nucleo-144 NUCLEO_L552ZE_Q

#### 3.1 First Start

```
Start StoreNameAndSurname on NUCLEO_L552ZE_Q
FlashStorage_STM32 v1.2.0
EEPROM length: 2048
EEPROM is empty, writing WRITTEN_SIGNATURE and some example data:
Insert your name : My_Name

Insert your surname : My_Surname

<< Your name: My_Name
. Your surname: My_Surname
 >> have been saved. Thank you!
```

#### 3.2 After reset

```
Start StoreNameAndSurname on NUCLEO_L552ZE_Q
FlashStorage_STM32 v1.2.0
EEPROM length: 2048
Hi My_Name
 My_Surname
, nice to see you again :-)
Clearing WRITTEN_SIGNATURE for next try
Done clearing signature in emulated EEPROM. You can reset now
```

---

### 4. StoreNameAndSurname on NUCLEO_F767ZI with 16KB emulated-EEPROM

The following is the sample terminal output when running example [StoreNameAndSurname](examples/StoreNameAndSurname) on STM32F7 Nucleo-144 NUCLEO_F767ZI

#### 4.1 First Start

```
Start StoreNameAndSurname on NUCLEO_F767ZI
FlashStorage_STM32 v1.2.0
EEPROM length: 16384
EEPROM is empty, writing WRITTEN_SIGNATURE and some example data:
Insert your name : My_Name

Insert your surname : My_Surname

<< Your name: My_Name
. Your surname: My_Surname
 >> have been saved. Thank you!
```

#### 4.2 After reset

```
Start StoreNameAndSurname on NUCLEO_F767ZI
FlashStorage_STM32 v1.2.0
EEPROM length: 16384
Hi My_Name
 My_Surname
, nice to see you again :-)
Clearing WRITTEN_SIGNATURE for next try
Done clearing signature in emulated EEPROM. You can reset now
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


### Issues

Submit issues to: [FlashStorage_STM32 issues](https://github.com/khoih-prog/FlashStorage_STM32/issues)

---

### TO DO

1. Search for bug and improvement.
2. Similar features for remaining Arduino boards

---

### DONE

1. Basic emulated-EEPROM for STM32F/L/H/G/WB/MP1.
2. Add support to new [**STM32 core v1.9.0**](https://github.com/stm32duino/Arduino_Core_STM32/releases/tag/1.9.0)
3. Similar features for remaining Arduino boards such as SAMD21, SAMD51, etc.
4. Add Table of Contents
5. Add support to new [**STM32 core v2.2.0+**](https://github.com/stm32duino/Arduino_Core_STM32/releases/tag/2.2.0)
6. Fix `multiple-definitions` linker error. 


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

