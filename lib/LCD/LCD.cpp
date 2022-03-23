#include "LCD.h"

LCD::LCD()
{
}

void LCD::startScreen()
{
    uint16_t ID = tft.readID(); // id of LCD Screen
    if (ID == 0xD3D3)
        ID = 0x9481; // write-only shield
    tft.begin(ID);
}

void LCD::refreshScreen()
{
    tft.fillScreen(BLACK);
}

void LCD::drawScreen(char *receivedChars)
{
    Serial.println(receivedChars);
}

void LCD::drawBox(LCDBox box, int boxNumber)
{
}

LCD::~LCD()
{
}