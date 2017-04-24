#include <Arduino.h>
#include "tfwifi.h"

//const char* ssid     = "Andreass iPhone";
const char* ssid     = "ThingForwardWiFi";
const char* password = "iotthingforward";

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

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
