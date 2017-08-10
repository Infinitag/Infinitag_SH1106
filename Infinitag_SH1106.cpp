/* 
* INFINITAG - open source laser tag
* Authors: Jani Taxidis, Tobias Stewen & Florian Kleene
* Website: www.infinitag.io
*
* All files are published under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
* License: https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "Infinitag_SH1106.h"

sh1106_spi create_display(int8_t resetPin, int8_t dcPin, int8_t csPin) {
  struct sh1106_spi display = {};
  display.resetPin = resetPin;
  display.dcPin = dcPin;  
  display.csPin = csPin;
  
  pinMode(display.resetPin, OUTPUT);   
  pinMode(display.dcPin, OUTPUT);  
  pinMode(display.csPin, OUTPUT);
  
  return(display);
}

void beginCommandMode(struct sh1106_spi* display) {
  digitalWrite(display->dcPin, LOW);  
  digitalWrite(display->csPin, LOW);
}

void endCommandMode(struct sh1106_spi* display) {
  digitalWrite(display->csPin, HIGH);
}

void beginDataMode(struct sh1106_spi* display) {
  digitalWrite(display->dcPin, HIGH); 
  digitalWrite(display->csPin, LOW);
}

void endDataMode(struct sh1106_spi* display) {
  digitalWrite(display->csPin, HIGH); 
}

void display_command(struct sh1106_spi* display, uint8_t command) {
  beginCommandMode(display);
  SPI.transfer(command);
  endCommandMode(display);
}

void display_command_param(struct sh1106_spi* display, uint8_t command, uint8_t param) {
  beginCommandMode(display);
  SPI.transfer(command);
  SPI.transfer(param);
  endCommandMode(display);  
}

void display_buffer(struct sh1106_spi* display, const uint8_t* buffer) {
  const byte rowCount = SCREEN_HEIGHT >> 3;
  for (byte row = 0; row < rowCount; row++)
  {
    display_command(display, (SH1106_PAGE_ADDR | row));
    display_command(display, (SH1106_LOWER_COLUMN_ADDR | 0x02));
    display_command(display, (SH1106_HIGHER_COLUMN_ADDR | 0x0));
       
    beginDataMode(display);
    for (byte col = 0; col < SCREEN_WIDTH; col++)
    { 
      if(!buffer)
      {
        SPI.transfer(0x00);
      }
      else
      {
        SPI.transfer(buffer[col + SCREEN_WIDTH * row]);
      }
    }
    endDataMode(display);
  }
}

void initialize_display(struct sh1106_spi* display) {
  SPI.setBitOrder(MSBFIRST);
  
  delay(10);
  
  //reset display
  digitalWrite(display->resetPin, LOW);
  delay(1);
  digitalWrite(display->resetPin, HIGH);
    
  display_buffer(display, 0);
  
  //turn display on
  display_command(display, (SH1106_DISPLAY_ON | 1));

  //set contrast high
  display_command_param(display, SH1106_SET_CONTRAST, 0xFF);

  //Flip Display
  display_command(display, SH1106_COMMON_SCANDIRECTION_REV);
  display_command(display, SH1106_SET_SEGMENT_REMAP_REV);
}