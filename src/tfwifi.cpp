#include <Arduino.h>
#include "tfwifi.h"

//const char* ssid     = "ThingForwardWiFi";
//const char* password = "iotthingforward";
const char* ssid     = "building IoT";
const char* password = "biot2017";

const int TFWIFI_MAX_TRY_COUNT = 20;

void setup_wifi() {
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    int try_count = 0;
    while (WiFi.status() != WL_CONNECTED && try_count++ < TFWIFI_MAX_TRY_COUNT) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("WiFi connected");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
    } else {
      Serial.println("E Not connected, CoAP functionality will not be available");
      WiFi.disconnect(true);
    }
}
