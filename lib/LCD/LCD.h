#ifndef LCD_H
#define LCD_H

#include <LCDBox.h>
#include <LCDBoxCurrent.h>

#include <Adafruit_I2CDevice.h>
#include <SPI.h>          
#include "Adafruit_GFX.h"
#include <ArduinoJson.h>
#include <MCUFRIEND_kbv.h>

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

class LCD
{
private:
    MCUFRIEND_kbv tft;
    void drawBox(LCDBox box, int boxNumber);
    void drawCurrentBox(LCDBoxCurrent box);
public:
    LCD();
    ~LCD();
    void startScreen();
    void refreshScreen();
    void drawScreen(char * receivedChars);
};

#endif