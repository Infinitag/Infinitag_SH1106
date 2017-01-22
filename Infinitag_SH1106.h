/* 
* INFINITAG - open source laser tag
* Authors: Jani Taxidis, Tobias Stewen & Florian Kleene
* Website: www.infinitag.io
*
* All files are published under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
* License: https://creativecommons.org/licenses/by-nc-sa/4.0/
*/

#ifndef Infinitag_SH1106_H
#define Infinitag_SH1106_H

#include <SPI.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

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


struct sh1106_spi
{
  int8_t resetPin; //reset pin on arduino (digital)
  int8_t dcPin;    //data/command pin on arduino (digital)
  int8_t csPin;    //chip select pin for spi interface (digital)
};

/**
 * Creates a display with the specified pinout and sets the pin's mode to OUTPUT
 */
sh1106_spi create_display(int8_t resetPin, int8_t dcPin, int8_t csPin);

/**
 * Display command/data utilities
 */
void beginCommandMode(struct sh1106_spi* display);
void endCommandMode(struct sh1106_spi* display);
void beginDataMode(struct sh1106_spi* display);
void endDataMode(struct sh1106_spi* display);
void display_command(struct sh1106_spi* display, uint8_t command);
void display_command_param(struct sh1106_spi* display, uint8_t command, uint8_t param);

/**
 * Copies the contents of buffer to the displays RAM 
 * the buffer should be of size 128x8 Bytes
 */ 
void display_buffer(struct sh1106_spi* display, const uint8_t* buffer);

/**
 * initialized the specified display the SPI interface should already be initialized
 * the displays contents will be empty. The SPI bitpattern is set to MSBFIRST
 */
void initialize_display(struct sh1106_spi* display);

#endif