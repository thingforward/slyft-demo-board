# slyft-demo-board

Code for OpenWRT Summit Demo with PIO and Linino

## Deps

- [PlatformIO](http://platformio.org/)

## On Linino

From the OpenWRT gateway side, we'd like to be able to CoAP-GET and -POST to a device. CoAPthon is a python-based
CoAP library with a small command line client to do so.

To install (via pip, remote):
```bash
$ opkg update
$ opkg install python python-pip
$ pip install --upgrade setuptools
$ pip install coapthon
```

To install from source:
```bash
$ opkg update
$ opkg install python python-pip
$ opkg install ca-bundle ca-certificates openssl-util libustream-openssl unzip wget
$ pip install --upgrade setuptools
$ wget https://github.com/Tanganelli/CoAPthon/archive/master.zip
$ unzip master
$ cd CoAPthon-master/
$ python setup.py sdist
$ pip install dist/CoAPthon-4.0.0.tar.gz -r requirements.txt
```

For additional hacking in python, also helpful are:
```bash
$ pip install msgpack-python hexdump
$ pip install platformio
```

## Device

connect your board (at present, must be an ESP8266)

### Update WiFi settings

This is a must: Please edit `src/tfwifi.cpp` and update your WiFi credentials there:

```c
const char* ssid     = "<YOUR SSID>";
const char* password = "<YOUR PASSWORD>";
```

### Build & flash

```bash
$ pio run -t upload
```

open another terminal with
```bash
$ pio device monitor
```

## Test

Using `coapclient.py` one can test different CoAP endpoints that the board now supports. The following snippets
show the command and the board's serial output.

### Reading the temperature

```bash
root@LEDE:~# coapclient.py -o GET -p coap://172.20.10.2/temp
Source: ('172.20.10.2', 5683)
Destination: None
Type: ACK
MID: 12341
Code: CONTENT
Token: Si
Content-Type: 42
Payload:
��v�C:21.34
-------------------------
udp_microcoap_wrapper rx UDP(len=11)>
udp_microcoap_wrapper> Processing CoAP message
DEMOAPI__demoapi__handle_get___temp
DEMOAPI__demoapi__handle_get___temp>REQ> COAP_HEADER: ver=0x01,t=0x00,tkl=0x02,code=0x01,id=0x3035,tok=0x5369
DEMOAPI__demoapi__handle_get___temp>REQ> OPTIONS(num=1): 0:num=11,val=temp,
DEMOAPI__demoapi__handle_get___temp>REQ> PAYLOAD(len=0): 0x
DEMOAPI__demoapi__handle_get___temp: Forwarding to DEMOAPI__demoapi__get___temp
DEMOAPI__demoapi__handle_get___temp: returned from DEMOAPI__demoapi__get___temp: 1
DEMOAPI__demoapi__handle_get___temp: Serializing response for code=205, schema=value
DEMOAPI__demoapi__handle_get___temp: Serializing done, len=11
DEMOAPI__demoapi__handle_get___temp>RESP> COAP_HEADER: ver=0x01,t=0x02,tkl=0x02,code=0x45,id=0x3035,tok=0x5369
DEMOAPI__demoapi__handle_get___temp>RESP> OPTIONS(num=1): 0:num=12,val=␀*,
DEMOAPI__demoapi__handle_get___temp>RESP> PAYLOAD(len=11): 0x81 A1 76 A7 43 3A 32 31 2E 33 34
udp_microcoap_wrapper tx UDP(len=21)

```

### Reading state of the LED

```bash
root@LEDE:~# coapclient.py -o GET -p coap://172.20.10.2/led
Source: ('172.20.10.2', 5683)
Destination: None
Type: ACK
MID: 20092
Code: CONTENT
Token: BY
Content-Type: 42
Payload:
��v�led_off
-------------------------
udp_microcoap_wrapper rx UDP(len=10)>
udp_microcoap_wrapper> Processing CoAP message
DEMOAPI__demoapi__handle_get___led
DEMOAPI__demoapi__handle_get___led>REQ> COAP_HEADER: ver=0x01,t=0x00,tkl=0x02,code=0x01,id=0x4E7C,tok=0x4259
DEMOAPI__demoapi__handle_get___led>REQ> OPTIONS(num=1): 0:num=11,val=led,
DEMOAPI__demoapi__handle_get___led>REQ> PAYLOAD(len=0): 0x
DEMOAPI__demoapi__handle_get___led: Forwarding to DEMOAPI__demoapi__get___led
DEMOAPI__demoapi__handle_get___led: returned from DEMOAPI__demoapi__get___led: 1
DEMOAPI__demoapi__handle_get___led: Serializing response for code=205, schema=value
DEMOAPI__demoapi__handle_get___led: Serializing done, len=11
DEMOAPI__demoapi__handle_get___led>RESP> COAP_HEADER: ver=0x01,t=0x02,tkl=0x02,code=0x45,id=0x4E7C,tok=0x4259
DEMOAPI__demoapi__handle_get___led>RESP> OPTIONS(num=1): 0:num=12,val=␀*,
DEMOAPI__demoapi__handle_get___led>RESP> PAYLOAD(len=11): 0x81 A1 76 A7 6C 65 64 5F 6F 66 66
udp_microcoap_wrapper tx UDP(len=21)>
```


### Turning LED on and off

```bash
root@LEDE:~# coapclient.py -o POST -P '' -p coap://172.20.10.2/led/on
Source: ('172.20.10.2', 5683)
Destination: None
Type: ACK
MID: 63039
Code: CONTENT
Token: FI
Payload:
None

root@LEDE:~# coapclient.py -o POST -P '' -p coap://172.20.10.2/led/off
Source: ('172.20.10.2', 5683)
Destination: None
Type: ACK
MID: 56964
Code: CONTENT
Token: aV
Payload:
None

-------------------------
udp_microcoap_wrapper rx UDP(len=13)>
udp_microcoap_wrapper> Processing CoAP message
DEMOAPI__demoapi__handle_post___led_on
DEMOAPI__demoapi__handle_post___led_on>REQ> COAP_HEADER: ver=0x01,t=0x00,tkl=0x02,code=0x02,id=0xF63F,tok=0x4649
DEMOAPI__demoapi__handle_post___led_on>REQ> OPTIONS(num=2): 0:num=11,val=led,1:num=11,val=on,
DEMOAPI__demoapi__handle_post___led_on>REQ> PAYLOAD(len=0): 0x
DEMOAPI__demoapi__handle_post___led_on: Forwarding to DEMOAPI__demoapi__post___led_on
DEMOAPI__demoapi__handle_post___led_on: returned from DEMOAPI__demoapi__post___led_on: 1
DEMOAPI__demoapi__handle_post___led_on>RESP> COAP_HEADER: ver=0x01,t=0x02,tkl=0x02,code=0x45,id=0xF63F,tok=0x4649
DEMOAPI__demoapi__handle_post___led_on>RESP> OPTIONS(num=0):
DEMOAPI__demoapi__handle_post___led_on>RESP> PAYLOAD(len=0): 0x
udp_microcoap_wrapper tx UDP(len=6)>
udp_microcoap_wrapper rx UDP(len=14)>
udp_microcoap_wrapper> Processing CoAP message
DEMOAPI__demoapi__handle_post___led_off
DEMOAPI__demoapi__handle_post___led_off>REQ> COAP_HEADER: ver=0x01,t=0x00,tkl=0x02,code=0x02,id=0xDE84,tok=0x6156
DEMOAPI__demoapi__handle_post___led_off>REQ> OPTIONS(num=2): 0:num=11,val=led,1:num=11,val=off,
DEMOAPI__demoapi__handle_post___led_off>REQ> PAYLOAD(len=0): 0x
DEMOAPI__demoapi__handle_post___led_off: Forwarding to DEMOAPI__demoapi__post___led_off
DEMOAPI__demoapi__handle_post___led_off: returned from DEMOAPI__demoapi__post___led_off: 1
DEMOAPI__demoapi__handle_post___led_off>RESP> COAP_HEADER: ver=0x01,t=0x02,tkl=0x02,code=0x45,id=0xDE84,tok=0x6156
DEMOAPI__demoapi__handle_post___led_off>RESP> OPTIONS(num=0):
DEMOAPI__demoapi__handle_post___led_off>RESP> PAYLOAD(len=0): 0x
udp_microcoap_wrapper tx UDP(len=6)>
```




