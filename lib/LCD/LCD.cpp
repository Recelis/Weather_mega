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
    // convert receivedChars arduinojson
    DynamicJsonDocument doc(800);
    deserializeJson(doc, receivedChars);
    float temp = doc["current"]["temp"];
   
    String location = doc["location"];
    
    // set the box objects
    LCDBoxCurrent boxCurrent(doc["location"], doc["current"]["temp"], doc["current"]["humidity"], doc["current"]["weather"][0]["main"], doc["current"]["weather"][0]["description"]);

    LCDBox box0(doc["daily"][0]["temp"]["min"], doc["daily"][0]["temp"]["max"], doc["daily"][0]["humidity"], doc["daily"][0]["weather"][0]["main"], doc["daily"][0]["weather"][0]["description"]);

    LCDBox box1(doc["daily"][1]["temp"]["min"], doc["daily"][1]["temp"]["max"], doc["daily"][1]["humidity"], doc["daily"][1]["weather"][0]["main"], doc["daily"][1]["weather"][0]["description"]);

    LCDBox box2(doc["daily"][2]["temp"]["min"], doc["daily"][2]["temp"]["max"], doc["daily"][2]["humidity"], doc["daily"][2]["weather"][0]["main"], doc["daily"][2]["weather"][0]["description"]);

    LCDBox box3(doc["daily"][3]["temp"]["min"], doc["daily"][3]["temp"]["max"], doc["daily"][3]["humidity"], doc["daily"][3]["weather"][0]["main"], doc["daily"][3]["weather"][0]["description"]);

    LCDBox box4(doc["daily"][4]["temp"]["min"], doc["daily"][4]["temp"]["max"], doc["daily"][4]["humidity"], doc["daily"][4]["weather"][0]["main"], doc["daily"][4]["weather"][0]["description"]);

    LCDBox box5(doc["daily"][5]["temp"]["min"], doc["daily"][5]["temp"]["max"], doc["daily"][5]["humidity"], doc["daily"][5]["weather"][0]["main"], doc["daily"][5]["weather"][0]["description"]);

    LCDBox box6(doc["daily"][6]["temp"]["min"], doc["daily"][6]["temp"]["max"], doc["daily"][6]["humidity"], doc["daily"][6]["weather"][0]["main"], doc["daily"][6]["weather"][0]["description"]);

    
    // drawing has to take place from left to right so that
    // any overwriting cuts things off
    drawCurrentBox(boxCurrent);
    drawBox(box0, 120, 6, '0');
    drawBox(box1, 240, 6, '1');
    drawBox(box2, 360, 6, '2');

    drawBox(box3, 6, 160, '3');
    drawBox(box4, 120, 160, '4');
    drawBox(box5, 240, 160, '5');
    drawBox(box6, 360, 160, '6');
}

void LCD::drawCurrentBox(LCDBoxCurrent box)
{
    int currentX = 6;
    int currentY = 6;
    currentY = printmsg(currentX, currentY, 2, WHITE, "Current");
    currentY = printmsg(currentX, currentY, 3, YELLOW, box.weatherMain);
    currentY = printmsg(currentX, currentY, 1, WHITE, box.weatherDescription);
    char tempBuff[10]; // create memory buffs outside for inside scope access
    floatToCharArr(box.temp, tempBuff);
    strcat(tempBuff, "C");
    currentY = printmsg(currentX, currentY, 2, BLUE, tempBuff);

    char humBuff[10]; // create memory buffs outside for inside scope access
    floatToCharArr(box.humidity, humBuff);
    strcat(humBuff, "%");
    currentY = printmsg(currentX, currentY, 2, GREEN, humBuff);
    currentY = printmsg(currentX, currentY, 2, RED, box.location);
}

void LCD::drawBox(LCDBox box, int x, int y, char day)
{
    int currentY = y;
    char dayVal[10];
    if (day == '0')
    {
        strcpy(dayVal, "Today");
    }
    else if (day == '1')
    {
        strcpy(dayVal, "Tomorrow");
    }
    else
    {
        strcpy(dayVal, "Day ");
        char dayStr[2] = {day, '\0'};
        strcat(dayVal, dayStr);
    }
    currentY = printmsg(x, currentY, 1, WHITE, dayVal);
    currentY = printmsg(x, currentY, 2, YELLOW, box.weatherMain);
    currentY = printmsg(x, currentY, 1, WHITE, box.weatherDescription);

    char tempMinBuff[10]; // create memory buffs outside for inside scope access
    floatToCharArr(box.tempMin, tempMinBuff);
    char tempMaxBuff[10];
    floatToCharArr(box.tempMax, tempMaxBuff);

    // concat tempMin and tempMax
    char tempBuff[60];
    strcpy(tempBuff, tempMinBuff);
    strcat(tempBuff, " - ");
    strcat(tempBuff, tempMaxBuff);
    strcat(tempBuff, "C");
    currentY = printmsg(x, currentY, 1, WHITE, tempBuff);

    char humBuff[10];
    floatToCharArr(box.humidity, humBuff);
    strcat(humBuff, "%");
    currentY = printmsg(x, currentY, 1, WHITE, humBuff);
}

void LCD::floatToCharArr(float value, char *buff)
{
    int val_int = (int)value;                     // compute the integer part of the float
    int val_fra = (int)((value - val_int) * 100); // compute 2 decimal places (and convert it to int)
    sprintf(buff, "%d.%02d", val_int, val_fra); // create a string with the 'floated' value including preceding 0s
    return buff;
}

// returns the new y location (including padding of 2) factoring in the textSize
int LCD::printmsg(int x, int y, int textSize, int color, const char *msg)
{
    tft.setTextColor(color, BLACK);
    tft.setTextSize(textSize); // default 6*8
    tft.setCursor(x, y);
    tft.println(msg);
    return 8 * textSize + 2 + y;
}

LCD::~LCD()
{
}