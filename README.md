# slyft-demo-board
code for the generic slyft.io demo board

## Deps

- [PlatformIO](http://platformio.org/)

## Board setup

- NodeMCUv2
- Grove Base Shield
- Grove Button/Touch/Switch at D6/D7
- Grove Analog Rotary at A0
- Grove LED Bar at D1/D2 I2C port
- Grove 4 digit LCD at D3/D5

## Build & flash

```
$ pio run -t upload
```

## CoAP endpoints

- GET `/.well-known/core`
- GET `/rotary`
- POST `/flash`

Supports CoAP Ping
