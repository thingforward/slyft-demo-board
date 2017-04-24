

// Generated by slyft.io
// This code part has been generated on an "as is" basis, without warranties or conditions of any kind.

// slyftlet=c99-generic-msgpack

#ifndef demoapi_VALUE_H
#define demoapi_VALUE_H


struct DEMOAPI__value {
  /* value as integer */
  int32_t	v;

  /**
  * Wipes contents to \0
  * @param self      pointer to target struct DEMOAPI__value
  */
  void (*DEMOAPI__value_clean)(struct DEMOAPI__value *self);

  /**
  * Given an input buffer and its size, this functions parses the elements
  * of struct DEMOAPI__value
  * @param self          pointer to target struct DEMOAPI__value
  * @param input_buf     input buffer
  * @param sz_input_buf  size of input buffer
  * @return 0=success, 1=error
  */
  int (*DEMOAPI__value_parse)(struct DEMOAPI__value *self, const uint8_t *input_buf, size_t sz_input_buf);

  /**
  * Given a struct DEMOAPI__value, this function serializes it into given output buffer.
  * @param self              pointer to source struct DEMOAPI__value
  * @param output_buf        output buffer
  * @param sz_output_buf     size of output buffer
  * @return Length of output buf (0=error)
  */
  size_t (*DEMOAPI__value_serialize)(const struct DEMOAPI__value *self, uint8_t *output_buf, size_t sz_output_buf);

};

/**
 * Initializes struct struct DEMOAPI__value. empties fields, sets function pointers
 * @param self  struct DEMOAPI__value
 */
void DEMOAPI__value_init(struct DEMOAPI__value *self);

/* ORIGINAL SCHEMA
{"$schema"=>"http://json-schema.org/draft-04/schema#", "id"=>"value", "title"=>"Single value schema", "description"=>"Transport the value of an input", "type"=>"object", "properties"=>{"v"=>{"type"=>"integer", "description"=>"value as integer"}}, "additionalProperties"=>false, "required"=>["v"], "minProperties"=>1}
 */
#endif		//demoapi_VALUE_H
