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
    tft.setRotation(1);
    tft.fillScreen(BLACK);
}

void LCD::drawScreen(char *receivedChars)
{
    Serial.println(receivedChars);
    // convert receivedChars arduinojson
    DynamicJsonDocument doc(800);
    deserializeJson(doc, receivedChars);
    float temp = doc["current"]["temp"];
    Serial.println(temp);
    String location = doc["location"];
    Serial.println(location);
    // set the box objects
    LCDBoxCurrent boxCurrent(doc["location"], doc["current"]["temp"], doc["current"]["humidity"], doc["current"]["weather"][0]["main"], doc["current"]["weather"][0]["description"]);
    Serial.println(boxCurrent.temp);
    
    LCDBox box0(doc["daily"][0]["temp"]["min"],doc["daily"][0]["temp"]["max"], doc["daily"][0]["humidity"], doc["daily"][0]["weather"][0]["main"], doc["daily"][0]["weather"][0]["description"]);

    LCDBox box1(doc["daily"][1]["temp"]["min"],doc["daily"][1]["temp"]["max"], doc["daily"][1]["humidity"], doc["daily"][1]["weather"][0]["main"], doc["daily"][1]["weather"][0]["description"]);

    LCDBox box2(doc["daily"][2]["temp"]["min"],doc["daily"][2]["temp"]["max"], doc["daily"][2]["humidity"], doc["daily"][2]["weather"][0]["main"], doc["daily"][2]["weather"][0]["description"]);

    LCDBox box3(doc["daily"][3]["temp"]["min"],doc["daily"][3]["temp"]["max"], doc["daily"][3]["humidity"], doc["daily"][3]["weather"][0]["main"], doc["daily"][3]["weather"][0]["description"]);

    LCDBox box4(doc["daily"][4]["temp"]["min"],doc["daily"][4]["temp"]["max"], doc["daily"][4]["humidity"], doc["daily"][4]["weather"][0]["main"], doc["daily"][4]["weather"][0]["description"]);

    LCDBox box5(doc["daily"][5]["temp"]["min"],doc["daily"][5]["temp"]["max"], doc["daily"][5]["humidity"], doc["daily"][5]["weather"][0]["main"], doc["daily"][5]["weather"][0]["description"]);
    
    drawCurrentBox(boxCurrent);
}

void LCD::drawCurrentBox(LCDBoxCurrent box)
{
    printmsg(0,0, 2, WHITE, box.weatherMain);
}

void LCD::drawBox(LCDBox box, int boxNumber)
{
    
}

void LCD::printmsg(int x, int y, int textSize, int color, const char *msg)
{
    tft.setTextColor(color, BLACK);
    tft.setTextSize(textSize);
    tft.setCursor(x, y);
    tft.println(msg);
}

LCD::~LCD()
{
}