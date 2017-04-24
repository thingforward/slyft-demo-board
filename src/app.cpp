#include <Arduino.h>

#include "Grove_LED_Bar/Grove_LED_Bar.h"

#include "app.h"

#include "slyft/value.h"
#include "slyft/demoapi_app.h"

#include "coap_sender/coap_sender.h"
#include "tfwifi.h"

#define	PIN_BUTTON	D6
#define PIN_ROTARY	A0
#define PIN_LEDBAR_SCL	D2
#define PIN_LEDBAR_SDA	D1

int 	rotary_value	= 0;
int 	last_rotary_value	= 0;
bool	last_button_value 	= false;
int 	flashmode = 0;

Grove_LED_Bar	led_bar(PIN_LEDBAR_SCL, PIN_LEDBAR_SDA, true);

void app_setup() {
	pinMode(PIN_BUTTON, INPUT);
	pinMode(PIN_ROTARY, INPUT);
	led_bar.begin();
}

int app_get_rotary_value() {
	return rotary_value;
}

void app_trigger_flash() {
	flashmode = 1;
}

void app_loop() {
	int rv = analogRead(PIN_ROTARY);
 	if ( abs(rv-last_rotary_value) > 10) {
		last_rotary_value = rotary_value;
		rotary_value = rv;

		float f = rotary_value / 100.0f;
		if ( f > 9) {
			f = 9;
		}

		led_bar.setLevel(f);
		//Serial.printf("rotary: %d\n", rotary_value);
	}


	// handle button press/release. Upon press,
	// post rotary value to server.
	int bv = digitalRead(PIN_BUTTON);

	if (last_button_value == false && bv == true) {
		led_bar.toggleLed(10);
		Serial.println("Button pressed");

		app_post_value();
	}
	if (last_button_value == true && bv == false) {
		Serial.println("Button released");
	}
	last_button_value = bv;


	// flash mode variable set? Then do some flashing, reset mode
	if ( flashmode == 1) {
		for (int i = 0; i < 10; i++) {
			led_bar.setLevel(i);
			delay(20);
		}
		for (int i = 10; i > 0; i--) {
			led_bar.setLevel(i);
			delay(20);
		}
		flashmode = 0;
	}

	// done app loop
}


coap_sender_struct_t	sender;

/* intermedia buffer object to construct the uri */
const uint8_t	str_uri[] = "advanced";
coap_buffer_t	buf_uri = {
	.p = str_uri, .len = sizeof(str_uri)-1
};

/* intermedia buffer struct to construct content type */
coap_content_type_t 	int_cf = COAP_CONTENTTYPE_APPLICATION_OCTECT_STREAM;
coap_buffer_t	buf_cf = {
	.p = (const uint8_t*)&int_cf, .len = 1
};

uint8_t	str_payl[64] = "";

//const char *p_server_ip = "172.20.10.6";
const char *p_server_ip = "192.168.0.100";

extern WiFiUDP Udp;
extern void DEMOAPI__demoapi__print_packet(const char *prefix, const coap_packet_t *pkt);

// use coap_sender to post the current rotary value to some endpoint
void app_post_value() {

	// empty payload buffer, initialize struct, serialize into buffer
	memset(str_payl, 0, sizeof(str_payl));
	struct DEMOAPI__value v;
	DEMOAPI__value_init(&v);
	v.v = last_rotary_value;
	size_t len = v.DEMOAPI__value_serialize(&v, str_payl, sizeof(str_payl));

	/* initialize coap sender structure */
	coap_sender_init(&sender,COAP_TYPE_NONCON, 4);
	/* set post request */
	coap_sender_post_request(&sender, str_payl, len);
	/* set our options */
	coap_sender_add_option(&sender, COAP_OPTION_URI_PATH, buf_uri);
	coap_sender_add_option(&sender, COAP_OPTION_CONTENT_FORMAT, buf_cf);

	coap_sender_dump("APP>POSTVALUE> ", &sender);

	if ( Udp.beginPacket(p_server_ip, 5683) == 1) {
		/* build packet */
		if ( coap_sender_build(&sender) == 0 && sender.buflen > 0) {
			/* send using UDP */
			if ( Udp.write(sender.buf, sender.buflen) != sender.buflen) {
				Serial.println("E udp.write");
			}
			Udp.endPacket();
		} else {
			/* an error occured during construction of coap packet buffer */
			Serial.print("E coap_build, res=");
			Serial.println(sender.build_res);
		}
	} else {
		Serial.print("E udp.beginPacket");
	}

}

// -- Application level handler for GET to /rotary
bool DEMOAPI__demoapi__get___rotary(
    struct DEMOAPI__demoapi__get___rotary_req *req,
    struct DEMOAPI__demoapi__get___rotary_resp *resp) {

    // YOUR CODE GOES HERE ----------- BEGIN

    // A return value of false causes the endpoint implementation to send a
    // CoAP 5.00 INTERNAL SERVER ERROR back to the client
    // return false;

    // When returning true, make sure to set the "response_code "value in "resp" to
    // the desired value, see coap_responsecode_t in microcoap/coap.h
    // Valid response codes need to be specified in API model.


    resp->response_code = (coap_responsecode_t)MAKE_RSPCODE(2,5);
    struct DEMOAPI__value  *q = &(resp->data.value_205);
    q->v = app_get_rotary_value();

    //  OR

    // custom response code handling, i.e.
    // resp->response_code = COAP_CONTENT;

    // default for now: 5.01 NOT_IMPLEMENTED
    //resp->response_code = (coap_responsecode_t)MAKE_RSPCODE(5,1);

    // YOUR CODE GOES HERE ----------- END

    return true;
}

// -- Application level handler for POST to /flash
bool DEMOAPI__demoapi__post___flash(
    struct DEMOAPI__demoapi__post___flash_req *req,
    struct DEMOAPI__demoapi__post___flash_resp *resp) {

    app_trigger_flash();

    // send back CHANGED
    resp->response_code = (coap_responsecode_t)MAKE_RSPCODE(2,4);

    return true;
}
