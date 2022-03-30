/*
  WS2812FX Webinterface.
  
  FEATURES
    * Webinterface with mode, color, speed and brightness selectors
*/

#ifdef ARDUINO_ARCH_ESP32
  #include <WiFi.h>
  #include <WebServer.h>
  #define WEB_SERVER WebServer
  #define ESP_RESET ESP.restart()
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266WebServer.h>
  #define WEB_SERVER ESP8266WebServer
  #define ESP_RESET ESP.reset()
#endif

#include <WS2812FX.h>

extern const char index_html[];
extern const char main_js[];

#define WIFI_SSID "Medialab"
#define WIFI_PASSWORD "Mediacollege2"

//#define STATIC_IP                 
#ifdef STATIC_IP
  IPAddress ip(192,168,0,123);
  IPAddress gateway(192,168,0,1);
  IPAddress subnet(255,255,255,0);
#endif

// QUICKFIX...See https://github.com/esp8266/Arduino/issues/263
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

#define PIN D8

#define WIFI_TIMEOUT 30000              
#define HTTP_PORT 80
