#include <Arduino.h>

#include "microcoap/coap.h"
#include "coap_sender.h"


void coap_sender_clean(coap_sender_struct_t *s) {
	memset(s,0,sizeof(coap_sender_struct_t));
	s->option_idx = s->buflen = 0;
	s->build_res = -1;
}

void coap_sender_init(coap_sender_struct_t *s, coap_msgtype_t type, int with_token_length) {
	coap_sender_clean(s);

	coap_packet_t *pkt = &(s->coap_packet);

	/* set basic header data, choose random msg id */
	pkt->hdr.ver = 0x01;
	pkt->hdr.t = type;
	pkt->hdr.code = MAKE_RSPCODE(0,0);
	pkt->hdr.id[0] = random(1,255);
	pkt->hdr.id[1] = random(1,255);

	/* set token to random bytes, given a with_token_length > 0 */
	pkt->hdr.tkl = 0;
	if ( with_token_length > 0) {
		for( int i = 0; i < with_token_length; i++) {
			s->buf_token[i] = random(65,127);
		}
		pkt->hdr.tkl = strlen(s->buf_token);
	}
	pkt->tok.len = pkt->hdr.tkl;
	pkt->tok.p = (const uint8_t*)s->buf_token;

	pkt->payload.len = 0;
}

void coap_sender_get_request(coap_sender_struct_t *s) {
	coap_packet_t *pkt = &(s->coap_packet);
	pkt->hdr.code = MAKE_RSPCODE(0,1);
    	pkt->payload.len = 0;
}

void coap_sender_post_request(coap_sender_struct_t *s, const uint8_t *payload, size_t sz_payload) {
	coap_packet_t *pkt = &(s->coap_packet);
	pkt->hdr.code = MAKE_RSPCODE(0,2);
    	pkt->payload.len = sz_payload;
	pkt->payload.p = payload;
}

/*void coap_sender_add_option(coap_sender_struct_t *s, coap_option_t o) {
	coap_packet_t *pkt = &(s->coap_packet);
	if (s->option_idx >= MAXOPT) {
		return;
	}
	pkt->numopts = 1+(s->option_idx);
	pkt->opts[s->option_idx] = o;

	s->option_idx++;
}*/

void coap_sender_add_option(coap_sender_struct_t *s, coap_option_num_t num, coap_buffer_t o) {
	coap_packet_t *pkt = &(s->coap_packet);
	if (s->option_idx >= MAXOPT) {
		return;
	}
	pkt->numopts = 1+(s->option_idx);
	pkt->opts[s->option_idx].num = num;
	pkt->opts[s->option_idx].buf.len = o.len;
	pkt->opts[s->option_idx].buf.p = o.p;

	s->option_idx++;
}

int coap_sender_build(coap_sender_struct_t *s) {
	coap_packet_t *pkt = &(s->coap_packet);
	s->buflen = sizeof(s->buf);
	s->build_res = coap_build((uint8_t*)s->buf, &s->buflen, pkt);

	return s->build_res;
}

void coap_sender_dump(const char *prefix, coap_sender_struct_t *s) {
	coap_packet_t *pkt = &(s->coap_packet);
	Serial.printf(prefix);
	Serial.printf(" COAP_HEADER:");
	Serial.printf(" ver=0x%02X", pkt->hdr.ver);
	Serial.printf(",t=0x%02X", pkt->hdr.t);
	Serial.printf(",tkl=0x%02X", pkt->hdr.tkl);
	Serial.printf(",code=0x%02X", pkt->hdr.code);
	Serial.printf(",id=0x%02X%02X", pkt->hdr.id[0], pkt->hdr.id[1]);
	if (pkt->tok.len > 0) {
			Serial.printf(",tok=0x");
			for (int i = 0; i < pkt->tok.len; i++) {
					Serial.printf("%02X",pkt->tok.p[i]);
			}
	}
	Serial.println();
	Serial.printf(prefix);
	Serial.printf(" OPTIONS");
	Serial.printf("(num=%d): ", pkt->numopts);
	for (int i = 0; i < pkt->numopts; i++) {
			Serial.printf("%d:num=%d,val=",i,pkt->opts[i].num);
			for ( int j = 0; j < pkt->opts[i].buf.len; j++) {
					Serial.printf("%c", pkt->opts[i].buf.p[j]);
			}
			Serial.print(",");
	}
	Serial.println();
	Serial.printf(prefix);
	Serial.printf(" PAYLOAD(len=%d): 0x", pkt->payload.len);
	if (pkt->payload.len > 0) {
			for (int i = 0; i < pkt->payload.len; i++) {
					Serial.printf("%02X ",pkt->payload.p[i]);
			}
	}
	Serial.println();

}
