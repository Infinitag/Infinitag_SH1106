/* 
* INFINITAG - open source laser tag
* Authors: Jani Taxidis, Tobias Stewen & Florian Kleene
* Website: www.infinitag.io
*
* All files are published under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
* License: https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "Infinitag_SH1106.h"

#define SH1106_DISPLAY_ON 0xAE
#define SH1106_DISPLAY_OFF 0xAF

#define SH1106_LOWER_COLUMN_ADDR 0x00
#define SH1106_HIGHER_COLUMN_ADDR 0x10
#define SH1106_PAGE_ADDR 0xB0
#define SH1106_START_LINE 0x40

#define SH1106_COMMON_SCANDIRECTION_REV 0xC8
#define SH1106_SET_SEGMENT_REMAP_NORM 0xA0
#define SH1106_SET_SEGMENT_REMAP_REV 0xA1

#define SH1106_SET_CONTRAST 0x81

Infinitag_SH1106::Infinitag_SH1106(int8_t aResetPin, int8_t aDCPin, int8_t aCSPin) 
    : myResetPin(aResetPin)
    , myDCPin(aDCPin)
    , myCSPin(aCSPin)
{  
  pinMode(myResetPin, OUTPUT);   
  pinMode(myDCPin, OUTPUT);  
  pinMode(myCSPin, OUTPUT);
}

void Infinitag_SH1106::Init() {
  SPI.setBitOrder(MSBFIRST);
  
  delay(10);
  
  //reset display
  digitalWrite(myResetPin, LOW);
  delay(1);
  digitalWrite(myResetPin, HIGH);
    
  Display(0);
  
  //turn display on
  Command(SH1106_DISPLAY_ON | 1);

  //set contrast high
  CommandParam(SH1106_SET_CONTRAST, 0xFF);

  //Flip Display
  Command(SH1106_COMMON_SCANDIRECTION_REV);
  Command(SH1106_SET_SEGMENT_REMAP_REV);
}

void Infinitag_SH1106::Display(const uint8_t* aBuffer) {
  const byte rowCount = INFINITAG_SCREEN_HEIGHT >> 3;
  for (byte row = 0; row < rowCount; row++)
  {
    Command(SH1106_PAGE_ADDR | row);
    Command(SH1106_LOWER_COLUMN_ADDR | 0x02);
    Command(SH1106_HIGHER_COLUMN_ADDR | 0x0);
       
    BeginDataMode();
    for (byte col = 0; col < INFINITAG_SCREEN_WIDTH; col++)
    { 
      if(!aBuffer)
      {
        SPI.transfer(0x00);
      }
      else
      {
        SPI.transfer(aBuffer[col + INFINITAG_SCREEN_WIDTH * row]);
      }
    }
    EndDataMode();
  }
}

void Infinitag_SH1106::BeginCommandMode() {
  digitalWrite(myDCPin, LOW);  
  digitalWrite(myCSPin, LOW);
}

void Infinitag_SH1106::EndCommandMode() {
  digitalWrite(myCSPin, HIGH);
}

void Infinitag_SH1106::BeginDataMode() {
  digitalWrite(myDCPin, HIGH); 
  digitalWrite(myCSPin, LOW);
}

void Infinitag_SH1106::EndDataMode() {
  digitalWrite(myCSPin, HIGH); 
}

void Infinitag_SH1106::Command(uint8_t aCommand) {
  BeginCommandMode();
  SPI.transfer(aCommand);
  EndCommandMode();
}

void Infinitag_SH1106::CommandParam(uint8_t aCommand, uint8_t aParam) {
  BeginCommandMode();
  SPI.transfer(aCommand);
  SPI.transfer(aParam);
  EndCommandMode();  
}