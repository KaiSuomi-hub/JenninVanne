#define BUFFPIXEL 1

void bmpDraw(char *filename, uint8_t x, uint16_t y) {
  tft.setRotation(1);

  File     bmpFile;
  int      bmpWidth, bmpHeight;   
  uint8_t  bmpDepth;              
  uint32_t bmpImageoffset;        
  uint32_t rowSize;               
  uint8_t  sdbuffer[3*BUFFPIXEL]; 
  uint8_t  buffidx = sizeof(sdbuffer); 
  boolean  goodBmp = false;       
  boolean  flip    = true;        
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();

  


  bmpFile = SD.open(filename);
  


  if(read16(bmpFile) == 0x4D42) { 
    read32(bmpFile);
    (void)read32(bmpFile); 
    bmpImageoffset = read32(bmpFile); 
    bmpImageoffset, DEC;
    read32(bmpFile);
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if(read16(bmpFile) == 1) {
      bmpDepth = read16(bmpFile);
      Serial.print(F("Bit Depth: ")); Serial.println(bmpDepth);
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) {

        goodBmp = true; 
        Serial.print(F("Image size: "));
        Serial.print(bmpWidth);
        Serial.print('x');
        Serial.println(bmpHeight);


        rowSize = (bmpWidth * 3 + 3) & ~3;


        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }
        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= tft.width())  w = tft.width()  - x;
        if((y+h-1) >= tft.height()) h = tft.height() - y;
        tft.setAddrWindow(x, y, x+w-1, y+h-1);
        for (row=0; row<h; row++) { 
          if(flip) 
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     
            pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) {
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer);
          }

          for (col=0; col<w; col++) {
            if (buffidx >= sizeof(sdbuffer)) {
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; 
            }

       
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            tft.pushColor(tft.color565(r,g,b));
          } 
        } 
        Serial.print(F("Loaded in "));
        Serial.print(millis() - startTime);
        Serial.println(" ms");
      } 
    }
  }

  bmpFile.close();
  if(!goodBmp) Serial.println(F("BMP format not recognized."));
}


uint16_t read16(File &f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); 
  ((uint8_t *)&result)[1] = f.read(); 
  return result;
}

uint32_t read32(File &f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); 
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); 
  return result;
}
