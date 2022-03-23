#ifndef LCDBox_H
#define LCDBox_H

#include "LCDBoxCurrent.h"

class LCDBox : public LCDBoxCurrent
{
    // draws a box with weather details
    private:
        
    public:
        float tempMin;
        float tempMax;
         LCDBox();
        LCDBox(float min, float max, float hum, char * main, char * description);
        ~LCDBox();
};

#endif