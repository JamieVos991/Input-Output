/* Written by Rupak Poddar */

#include <FastLED.h>             
#define NUMLEDS 60              
#define DATA_PIN D8                
#define SENSITIVITY 300           
#define MAX_BRIGHTNESS 200        
#define ANALOG A0          
#define SATURATION 150          
#define MINVAL 60
#define HUE_INIT 10
#define HUE_CHANGE 1

CRGB leds[NUMLEDS];
byte brightness[NUMLEDS];
byte hue[NUMLEDS];
int analogVal;
int DELAY;

void setup() { 
  Serial.begin(9600);
  pinMode(ANALOG, INPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUMLEDS);

  for(int i = 0; i <= NUMLEDS; i++){
    brightness[i] = 0;
    hue[i] = 0;
  }

  //Turn off all the LEDs
  for(int i=0; i <= NUMLEDS; i++)  
  {
  leds[i] = CRGB::Black;
  }

  //Update the LED strip
  FastLED.show(); 
}

void loop() {
  analogVal = analogRead(ANALOG);

  if(analogVal > SENSITIVITY)
  analogVal = SENSITIVITY;

  if(analogVal < MINVAL)
  analogVal = 0;

  LinearFlowing();
  
  FastLED.show();
}

void LinearFlowing(){
  byte val = map(analogVal, 0, SENSITIVITY+1, 0, MAX_BRIGHTNESS);
  DELAY = map(analogVal, 0, SENSITIVITY+1, 20, 1);
  
  for(int i = 0; i <= NUMLEDS; i++){
    brightness[NUMLEDS-i] = brightness[NUMLEDS-i-1];
  }
  
  for(int i = 0; i <= NUMLEDS; i++){
    hue[NUMLEDS-i] = hue[NUMLEDS-i-1];
  }
  
  brightness[0] = val;
  byte hue = HUE_INIT;
  for(int i = 0; i <= NUMLEDS; i++){
    leds[i] = CHSV(hue += HUE_CHANGE, SATURATION, brightness[i]);
  }
  delay(DELAY);
}
