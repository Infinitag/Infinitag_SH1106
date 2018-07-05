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

#define INFINITAG_SCREEN_WIDTH 128
#define INFINITAG_SCREEN_HEIGHT 64

class Infinitag_SH1106
{
public:
    Infinitag_SH1106(int8_t aResetPin, int8_t aDCPin, int8_t aCSPin);
    
    /**
    * initialized the specified display the SPI interface should already be initialized
    * the displays contents will be empty. The SPI bitpattern is set to MSBFIRST
    */
    void Init();
    
    /**
    * Copies the contents of buffer to the displays RAM 
    * the buffer should be of size INFINITAG_SCREEN_WIDTHxINFINITAG_SCREEN_HEIGHT/8 Bytes
    */ 
    void Display(const uint8_t* aDisplayBuffer);
private:
    /**
    * Display command/data utilities
    */
    void BeginCommandMode();
    void EndCommandMode();
    void BeginDataMode();
    void EndDataMode();
    void Command(uint8_t aCommand);
    void CommandParam(uint8_t aCommand, uint8_t aParam);
    
    int8_t myResetPin; //reset pin on arduino (digital)
    int8_t myDCPin;    //data/command pin on arduino (digital)
    int8_t myCSPin;    //chip select pin for spi interface (digital)
};

extern Infinitag_SH1106 theDisplay;

#endif