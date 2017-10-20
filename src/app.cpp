#include <Arduino.h>

#include "app.h"

#include "slyft/value.h"
#include "slyft/demoapi_app.h"


void app_setup() {
	pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
}

void app_loop() {
}

// see http://wiki.seeed.cc/Grove-Temperature_Sensor_V1.2/
const int B = 4275;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k
const int pinTempSensor = A0;     // Grove - Temperature Sensor connect to A5

//
// CoAP Application level handlers
//

// -- Application level handler for GET to /temp
bool DEMOAPI__demoapi__get___temp(
        struct DEMOAPI__demoapi__get___temp_req *req,
        struct DEMOAPI__demoapi__get___temp_resp *resp) {

  int a = analogRead(pinTempSensor);

  float R = 1023.0/a-1.0;
  R = R0*R;

  float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15; // convert to temperature via datasheet
  char str_temp[6];
  dtostrf(temperature, 4, 2, str_temp);


  resp->response_code = (coap_responsecode_t)MAKE_RSPCODE(2,5);
  struct DEMOAPI__value  *q = &(resp->data.value_205);

  sprintf(q->v, "C:%s", str_temp);

  return true;
}


// -- Application level handler for GET to /led
bool DEMOAPI__demoapi__get___led(
        struct DEMOAPI__demoapi__get___led_req *req,
        struct DEMOAPI__demoapi__get___led_resp *resp) {

  // YOUR CODE GOES HERE ----------- BEGIN



  // A return value of false causes the endpoint implementation to send a
  // CoAP 5.00 INTERNAL SERVER ERROR back to the client
  // return false;

  // When returning true, make sure to set the "response_code "value in "resp" to
  // the desired value, see coap_responsecode_t in microcoap/coap.h
  // Valid response codes need to be specified in API model.

  resp->response_code = (coap_responsecode_t)MAKE_RSPCODE(2,5);
  struct DEMOAPI__value  *q = &(resp->data.value_205);

  strncpy(q->v, (digitalRead(BUILTIN_LED)?"led_off":"led_on"), sizeof(q->v));

  // YOUR CODE GOES HERE ----------- END

  return true;
}


// -- Application level handler for POST to /led/on
bool DEMOAPI__demoapi__post___led_on(
        struct DEMOAPI__demoapi__post___led_on_req *req,
        struct DEMOAPI__demoapi__post___led_on_resp *resp) {

  // YOUR CODE GOES HERE ----------- BEGIN


  digitalWrite(BUILTIN_LED, LOW);

  // A return value of false causes the endpoint implementation to send a
  // CoAP 5.00 INTERNAL SERVER ERROR back to the client
  // return false;

  // When returning true, make sure to set the "response_code "value in "resp" to
  // the desired value, see coap_responsecode_t in microcoap/coap.h
  // Valid response codes need to be specified in API model.

  // custom response code handling, i.e.
  resp->response_code = (coap_responsecode_t)MAKE_RSPCODE(2,5);

  // YOUR CODE GOES HERE ----------- END

  return true;
}


// -- Application level handler for POST to /led/off
bool DEMOAPI__demoapi__post___led_off(
        struct DEMOAPI__demoapi__post___led_off_req *req,
        struct DEMOAPI__demoapi__post___led_off_resp *resp) {

  // YOUR CODE GOES HERE ----------- BEGIN


  digitalWrite(BUILTIN_LED, HIGH);

  // A return value of false causes the endpoint implementation to send a
  // CoAP 5.00 INTERNAL SERVER ERROR back to the client
  // return false;

  // When returning true, make sure to set the "response_code "value in "resp" to
  // the desired value, see coap_responsecode_t in microcoap/coap.h
  // Valid response codes need to be specified in API model.

  // custom response code handling, i.e.
  // resp->response_code = COAP_CONTENT;

  // default for now: 5.01 NOT_IMPLEMENTED
  resp->response_code = (coap_responsecode_t)MAKE_RSPCODE(2,5);

  // YOUR CODE GOES HERE ----------- END

  return true;
}

