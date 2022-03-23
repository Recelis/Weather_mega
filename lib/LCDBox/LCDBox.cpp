#include "LCDBox.h"

LCDBox::LCDBox()
{
}

LCDBox::LCDBox(float min, float max, float hum, char *main, char *description)
{
    tempMin = min;
    tempMax = max;
    humidity = hum;
    weatherMain = main;
    weatherDescription = description;
}

LCDBox::~LCDBox()
{
}