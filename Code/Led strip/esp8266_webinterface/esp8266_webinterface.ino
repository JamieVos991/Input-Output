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

#define WIFI_SSID "Fam Vos"
#define WIFI_PASSWORD "ArjJam17"

// Bug fix
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

#define PIN D8 // data

#define WIFI_TIMEOUT 30000
#define HTTP_PORT 80

String modes = "";
uint8_t myModes[] = {};


WS2812FX ws2812fx = WS2812FX(60, PIN, NEO_GRB + NEO_KHZ800);
WEB_SERVER server(HTTP_PORT);

void setup() {
  Serial.begin(115200);

  modes.reserve(5000);
  modes_setup();

  ws2812fx.init();
  ws2812fx.start();

  Serial.println("Wifi setup");
  wifi_setup();

  server.on("/", srv_handle_index_html);
  server.on("/main.js", srv_handle_main_js);
  server.on("/modes", srv_handle_modes);
  server.on("/set", srv_handle_set);
  server.begin();
}


void loop() {

  server.handleClient();
  ws2812fx.service();

}




/* Connect to WiFi */

void wifi_setup() {

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.mode(WIFI_STA);

  unsigned long connect_start = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("IP address: ");       //  IP adress
  Serial.println(WiFi.localIP());     //
}


/*
   Build <li> string for all modes.
*/

void modes_setup() {
  modes = "";
  uint8_t num_modes = sizeof(myModes) > 0 ? sizeof(myModes) : ws2812fx.getModeCount();
  for (uint8_t i = 0; i < num_modes; i++) {
    uint8_t m = sizeof(myModes) > 0 ? myModes[i] : i;
    modes += "<li><a href='#'>";
    modes += ws2812fx.getModeName(m);
    modes += "</a></li>";
  }
}

/* Webserver Functions */

void srv_handle_index_html() {
  server.send_P(200, "text/html", index_html);
}

void srv_handle_main_js() {
  server.send_P(200, "application/javascript", main_js);
}

void srv_handle_modes() {
  server.send(200, "text/plain", modes);
}

void srv_handle_set() {

  /* Van kleur veranderen */

  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "c") {
      uint32_t tmp = (uint32_t) strtol(server.arg(i).c_str(), NULL, 10);
      if (tmp <= 0xFFFFFF) {
        ws2812fx.setColor(tmp);
      }
    }


    /* Van mode veranderen */

    if (server.argName(i) == "m") {
      uint8_t tmp = (uint8_t) strtol(server.arg(i).c_str(), NULL, 10);
      uint8_t new_mode = sizeof(myModes) > 0 ? myModes[tmp % sizeof(myModes)] : tmp % ws2812fx.getModeCount();
      ws2812fx.setMode(new_mode);
      Serial.print("mode is "); Serial.println(ws2812fx.getModeName(ws2812fx.getMode()));
    }
  }
}
