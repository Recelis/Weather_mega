#ifndef Communication_H
#define Communication_H

#include <ArduinoJson.h>

class Communication
{
private:
    const int numChars = 6000;
    char receivedChars[6000];
    boolean newData = false;

public:
    Communication();
    ~Communication();
    void receiveData();
};

#endif