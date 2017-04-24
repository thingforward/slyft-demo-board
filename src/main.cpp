#include <Arduino.h>

#include "tfwifi.h"
#include "app.h"

#include "microcoap/coap.h"
#include "slyft/udp_microcoap_wrapper.h"

WiFiUDP Udp;

void setup() {
  Serial.begin(9600);
  //Serial.setDebugOutput(true);

  app_setup();

  setup_wifi();

  // UDP-Listen on port 5683 (default CoAP)
  Udp.begin(5683);

  // setup microcoap lib
  coap_setup();
  // connect UDP object to the endpoints
  udp_microcoap_wrapper_init(&Udp);
}

void loop() {
  delay(50);

  app_loop();

  // get coap processing object
  udp_microcoap_wrapper *c = udp_microcoap_wrapper_get();
  c->b_debug = true;

  // let it handle a message (if one is available via WifiUdp)
  c->ops->handle_udp_coap_message(c);
}
