#define WIFI_SSID "Medialab"
#define WIFI_PASSWORD "Mediacollege2"
                 
#ifdef STATIC_IP
  IPAddress ip(192,168,0,123);
  IPAddress gateway(192,168,0,1);
  IPAddress subnet(255,255,255,0);
#endif
