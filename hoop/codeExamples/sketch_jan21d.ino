/*
  The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 */

#include <Wire.h>
#include <SeeedGrayOLED.h>
#include <avr/pgmspace.h>
#include <stdlib.h>

#include <SPI.h>
#include <SD.h>

File myFile;
File bMap;
unsigned  char bitmp[512];
int index=0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(8)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  // open the file for reading:
  myFile = SD.open("t2.txt");
  //bMap = SD.open("t.bmp", FILE_READ);
  if (myFile) {
     while (myFile.available()) {
       bitmp [index] = (unsigned char) myFile.read();
       index++;
       }
     for(int i=0; i<512; i++){
       Serial.write(bitmp[i]);
     }
  myFile.close();
  Wire.begin(); 
  SeeedGrayOled.init();              // initialize SEEED OLED display
  SeeedGrayOled.clearDisplay();                  //  clear the screen and set start position to top left corner
  SeeedGrayOled.drawBitmap(bitmp,96*96/8);   //  Draw binary Bitmap (96 pixels *96 pixels  / 8) bytes
  }
 else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop() {
  // nothing happens after setup
}


