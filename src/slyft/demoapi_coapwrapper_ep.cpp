// Generated by slyft.io
// This code part has been generated on an "as is" basis, without warranties or conditions of any kind.

// endpoints

#include "microcoap/coap.h"


static const coap_endpoint_path_t DEMOAPI__demoapi__paths_get_well_known_core = {2, {".well-known", "core"}};

int DEMOAPI__demoapi__handle_get_well_known_core(coap_rw_buffer_t *scratch,
const coap_packet_t *inpkt, coap_packet_t *outpkt,
uint8_t id_hi, uint8_t id_lo);



// enumerate all single resources as endpoint_path types

static const coap_endpoint_path_t DEMOAPI__demoapi__paths__temp = {1, {"temp"}};
static const coap_endpoint_path_t DEMOAPI__demoapi__paths__led = {1, {"led"}};
static const coap_endpoint_path_t DEMOAPI__demoapi__paths__led_on = {2, {"led","on"}};
static const coap_endpoint_path_t DEMOAPI__demoapi__paths__led_off = {2, {"led","off"}};

// define handler functions

int DEMOAPI__demoapi__handle_get___temp(coap_rw_buffer_t *scratch,
    const coap_packet_t *inpkt, coap_packet_t *outpkt,
    uint8_t id_hi, uint8_t id_lo);

int DEMOAPI__demoapi__handle_get___led(coap_rw_buffer_t *scratch,
    const coap_packet_t *inpkt, coap_packet_t *outpkt,
    uint8_t id_hi, uint8_t id_lo);

int DEMOAPI__demoapi__handle_post___led_on(coap_rw_buffer_t *scratch,
    const coap_packet_t *inpkt, coap_packet_t *outpkt,
    uint8_t id_hi, uint8_t id_lo);

int DEMOAPI__demoapi__handle_post___led_off(coap_rw_buffer_t *scratch,
    const coap_packet_t *inpkt, coap_packet_t *outpkt,
    uint8_t id_hi, uint8_t id_lo);


// define array with all endpoints
extern const coap_endpoint_t endpoints[] =
{

    {COAP_METHOD_GET, DEMOAPI__demoapi__handle_get_well_known_core, &DEMOAPI__demoapi__paths_get_well_known_core, "ct=40"},

    {COAP_METHOD_GET, DEMOAPI__demoapi__handle_get___temp, &DEMOAPI__demoapi__paths__temp, "ct=0"},	/* Return temperature (as string) */
    {COAP_METHOD_GET, DEMOAPI__demoapi__handle_get___led, &DEMOAPI__demoapi__paths__led, "ct=0"},	/* Return value of led */
    {COAP_METHOD_POST, DEMOAPI__demoapi__handle_post___led_on, &DEMOAPI__demoapi__paths__led_on, "ct=0"},	/* Turn LED on */
    {COAP_METHOD_POST, DEMOAPI__demoapi__handle_post___led_off, &DEMOAPI__demoapi__paths__led_off, "ct=0"},	/* Turn LED off */
    {(coap_method_t)0, NULL, NULL, NULL}
};
