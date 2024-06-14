/*
 * Example use of chdir(), ls(), mkdir(), and  rmdir().
 */
#include "SdFat.h"
#include "sdios.h"

// SD_FAT_TYPE = 0 for SdFat/File as defined in SdFatConfig.h,
// 1 for FAT16/FAT32, 2 for exFAT, 3 for FAT16/FAT32 and exFAT.
#define SD_FAT_TYPE 1
/*
  Change the value of SD_CS_PIN if you are using SPI and
  your hardware does not use the default value, SS.
  Common values are:
  Arduino Ethernet shield: pin 4
  Sparkfun SD shield: pin 8
  Adafruit SD shields and modules: pin 10
*/

// SDCARD_SS_PIN is defined for the built-in SD on some boards.
#ifndef SDCARD_SS_PIN
const uint8_t SD_CS_PIN = SS;
#else  // SDCARD_SS_PIN
// Assume built-in SD is used.
const uint8_t SD_CS_PIN = SDCARD_SS_PIN;
#endif  // SDCARD_SS_PIN

// Try max SPI clock for an SD. Reduce SPI_CLOCK if errors occur.
#define SPI_CLOCK SD_SCK_MHZ(50)

// Try to select the best SD card configuration.
#if HAS_SDIO_CLASS
#define SD_CONFIG SdioConfig(FIFO_SDIO)
#elif  ENABLE_DEDICATED_SPI
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SPI_CLOCK)
#else  // HAS_SDIO_CLASS
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, SHARED_SPI, SPI_CLOCK)
#endif  // HAS_SDIO_CLASS
//------------------------------------------------------------------------------  

#if SD_FAT_TYPE == 0
SdFat sd;
File file;
File root;
#elif SD_FAT_TYPE == 1
SdFat32 sd;
File32 file;
File32 root;
#elif SD_FAT_TYPE == 2
SdExFat sd;
ExFile file;
ExFile root;
#elif SD_FAT_TYPE == 3
SdFs sd;
FsFile file;
FsFile root;
#endif  // SD_FAT_TYPE

// Create a Serial output stream.
ArduinoOutStream cout(Serial);
//------------------------------------------------------------------------------
// Store error strings in flash to save RAM.
#define error(s) sd.errorHalt(&Serial, F(s))
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);

  // Wait for USB Serial
  while (!Serial) {
    yield();
  }
  delay(1000);
  cout << F("Type any character to start\n");
  while (!Serial.available()) {
    yield();
  }

  // Initialize the SD card.
  if (!sd.begin(SD_CONFIG)) {
    sd.initErrorHalt(&Serial);
  }


   if (!root.open("/")) {
    error("open root");
  }

  cout << F("\nList of files on the SD.\n");
  sd.ls("/", LS_R);




}
//------------------------------------------------------------------------------
// Nothing happens in loop.
void loop() {}