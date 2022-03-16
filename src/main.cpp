#include <Arduino.h>
#include <SPI.h>          // f.k. for Arduino-1.5.2
#include <Adafruit_I2CDevice.h>
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>
#include <string.h>

#include <Communication.h>

Communication myCommunication;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  myCommunication.receiveData();
}