
// Generated by slyft.io
// This code part has been generated on an "as is" basis, without warranties or conditions of any kind.

// endpoint implementation


    #include "Arduino.h"

#include "microcoap/coap.h"
#include "demoapi_app.h"

#include "value.h"



void DEMOAPI__demoapi__print_packet(const char *prefix, const coap_packet_t *pkt) {
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


#define COAP_MAKERESPONSE_INTERNALSERVERERROR \
return coap_make_response(scratch, \
  outpkt, (uint8_t*)outbuf, 0, \
  id_hi, id_lo, \
  &inpkt->tok, \
  (coap_responsecode_t)MAKE_RSPCODE(5, 0), COAP_CONTENTTYPE_NONE \
  );

#define COAP_MAKERESPONSE_BADREQUEST \
return coap_make_response(scratch, \
  outpkt, (uint8_t*)outbuf, 0, \
  id_hi, id_lo, \
  &inpkt->tok, \
  COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_NONE \
  );

#define RSPCODE_CLASS(rsp)  (rsp >> 5)
#define RSPCODE_DETAIL(rsp) (rsp & 31)

extern const coap_endpoint_t endpoints[];
static char well_known_rsp[256] = "\0";


int DEMOAPI__demoapi__handle_get_well_known_core(coap_rw_buffer_t *scratch,
    const coap_packet_t *inpkt, coap_packet_t *outpkt,
    uint8_t id_hi, uint8_t id_lo) {
    Serial.println("DEMOAPI__demoapi__handle_get_well_known_core");
    DEMOAPI__demoapi__print_packet("DEMOAPI__demoapi__handle_get_well_known_core>REQ>", inpkt);
    
    if (well_known_rsp[0] == '\0') {
        // set up response
        uint16_t len = sizeof(well_known_rsp);
        const coap_endpoint_t *ep = endpoints;
        char *rsp = well_known_rsp;
        int i;

        len--; // Null-terminated string

        while(NULL != ep->handler)
        {
          if (NULL == ep->core_attr) {
            ep++;
            continue;
          }

          if (0 < strlen(rsp)) {
            strncat(rsp, ",", len);
            len--;
          }

          strncat(rsp, "<", len);
          len--;

          for (i = 0; i < ep->path->count; i++) {
            strncat(rsp, "/", len);
            len--;

            strncat(rsp, ep->path->elems[i], len);
            len -= strlen(ep->path->elems[i]);
          }

          strncat(rsp, ">;", len);
          len -= 2;

          strncat(rsp, ep->core_attr, len);
          len -= strlen(ep->core_attr);

          ep++;
        }
    }


    int res = coap_make_response(scratch, outpkt, (const uint8_t *)well_known_rsp, strlen(well_known_rsp), id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CONTENT, COAP_CONTENTTYPE_APPLICATION_LINKFORMAT);

   DEMOAPI__demoapi__print_packet("DEMOAPI__demoapi__handle_get_well_known_core>RESP>", outpkt);

    return res;
}

// define coap handler functions

// Protocol-level handler for GET requests to /rotary
int DEMOAPI__demoapi__handle_get___rotary(coap_rw_buffer_t *scratch,
    const coap_packet_t *inpkt, coap_packet_t *outpkt,
    uint8_t id_hi, uint8_t id_lo) {

    Serial.println("DEMOAPI__demoapi__handle_get___rotary");
    DEMOAPI__demoapi__print_packet("DEMOAPI__demoapi__handle_get___rotary>REQ>", inpkt);
    
    // processing
    uint8_t outbuf[512];
    mpack_memset(outbuf,0,sizeof(outbuf));
    size_t resp_len = 0;
    coap_responsecode_t  resp_code;
    coap_content_type_t  resp_content_type = COAP_CONTENTTYPE_NONE;

    struct DEMOAPI__demoapi__get___rotary_req    req;
    struct DEMOAPI__demoapi__get___rotary_resp   resp;


    DEMOAPI__value_init(&(resp.data.value_205));


    Serial.println("DEMOAPI__demoapi__handle_get___rotary: Forwarding to DEMOAPI__demoapi__get___rotary");
    // forward req,resp structs to application handler
    bool handled = DEMOAPI__demoapi__get___rotary(&req, &resp);
    Serial.print("DEMOAPI__demoapi__handle_get___rotary: returned from DEMOAPI__demoapi__get___rotary: "); Serial.println(handled);

    if (handled) {
      // take response code from resp
      resp_code = resp.response_code;
      // form the response body
      if ( RSPCODE_CLASS(resp_code) == 2 && RSPCODE_DETAIL(resp_code) == 05) {
        Serial.println("DEMOAPI__demoapi__handle_get___rotary: Serializing response for code=205, schema=value");
        // handle code 205, schema is value
        resp_len = resp.data.value_205.DEMOAPI__value_serialize(&(resp.data.value_205), outbuf, sizeof(outbuf));
        resp_content_type = COAP_CONTENTTYPE_APPLICATION_OCTECT_STREAM;
        Serial.print("DEMOAPI__demoapi__handle_get___rotary: Serializing done, len="); Serial.println(resp_len); 
      }


      int res = coap_make_response(scratch,
        outpkt,
        (uint8_t*)outbuf, resp_len,
        id_hi, id_lo,
        &inpkt->tok,
        resp_code, resp_content_type
      );
      DEMOAPI__demoapi__print_packet("DEMOAPI__demoapi__handle_get___rotary>RESP>", outpkt);
      return res;
    } else {
      Serial.print("DEMOAPI__demoapi__handle_get___rotary: -> INTERNAL_SERVER_ERROR");
      COAP_MAKERESPONSE_INTERNALSERVERERROR
    }

}

// Protocol-level handler for POST requests to /flash
int DEMOAPI__demoapi__handle_post___flash(coap_rw_buffer_t *scratch,
    const coap_packet_t *inpkt, coap_packet_t *outpkt,
    uint8_t id_hi, uint8_t id_lo) {

    Serial.println("DEMOAPI__demoapi__handle_post___flash");
    DEMOAPI__demoapi__print_packet("DEMOAPI__demoapi__handle_post___flash>REQ>", inpkt);
    
    // processing
    uint8_t outbuf[512];
    mpack_memset(outbuf,0,sizeof(outbuf));
    size_t resp_len = 0;
    coap_responsecode_t  resp_code;
    coap_content_type_t  resp_content_type = COAP_CONTENTTYPE_NONE;

    struct DEMOAPI__demoapi__post___flash_req    req;
    struct DEMOAPI__demoapi__post___flash_resp   resp;



    Serial.println("DEMOAPI__demoapi__handle_post___flash: Forwarding to DEMOAPI__demoapi__post___flash");
    // forward req,resp structs to application handler
    bool handled = DEMOAPI__demoapi__post___flash(&req, &resp);
    Serial.print("DEMOAPI__demoapi__handle_post___flash: returned from DEMOAPI__demoapi__post___flash: "); Serial.println(handled);

    if (handled) {
      // take response code from resp
      resp_code = resp.response_code;
      // form the response body

      int res = coap_make_response(scratch,
        outpkt,
        (uint8_t*)outbuf, resp_len,
        id_hi, id_lo,
        &inpkt->tok,
        resp_code, resp_content_type
      );
      DEMOAPI__demoapi__print_packet("DEMOAPI__demoapi__handle_post___flash>RESP>", outpkt);
      return res;
    } else {
      Serial.print("DEMOAPI__demoapi__handle_post___flash: -> INTERNAL_SERVER_ERROR");
      COAP_MAKERESPONSE_INTERNALSERVERERROR
    }

}

