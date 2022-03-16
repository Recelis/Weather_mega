#include "Communication.h"


Communication::Communication()
{
  // Set up Mega Serial
  Serial1.begin(9600);
}

void Communication::receiveData()
{
  static short int ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial1.available() > 0 && newData == false)
  {


    rc = Serial1.read();
    if (rc != endMarker && ndx < numChars)
    {
      receivedChars[ndx] = rc;
      ndx++;
    }
    else
    {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
  if (newData){
    newData = false;
    Serial.println(receivedChars);
  }
  // combines the location city data with weather data
  // send to Mega
  // DynamicJsonDocument doc(1500);
  // deserializeJson(doc, sevenDayForecast);
  // Serial.println(sevenDayForecast);
}

Communication::~Communication()
{
}