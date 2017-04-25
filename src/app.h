
/* initializes components, pinmodes etc */
void app_setup();

/* loops through application steps */
void app_loop();

/* returns value of the analog sensor */
int app_get_rotary_value();

/* triggers LED or LCD bar flashing */
void app_trigger_flash();

/* CoAP-posts the current value to the server */
void app_post_value();

/* sets the IP Address of where to CoAP-POST the current value */
void app_set_target_ip(const char *);
