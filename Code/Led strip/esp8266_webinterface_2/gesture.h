#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;


// initialize gesture sensor
void startGestureSensor(){
    if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
      }
      else Serial.println("Device initialized!");
    
      //gesture mode will be entered once proximity mode senses something close
      apds.enableProximity(true);
      apds.enableGesture(true);
  
  }
