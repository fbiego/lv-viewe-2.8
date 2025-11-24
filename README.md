# Viewe 2.8" 240x320 Board

## Overview

The UEDX24320028E-WB is a 2.8-inch 240×320 capacitive-touch smart display powered by the ESP32-S3. It features built-in Wi-Fi & BLE 5, high-capacity Flash/PSRAM, and an optimized UART protocol, making it a powerful solution for rapid HMI and IoT development.

<p align="center" width="80%">
    <img src="images/view_2.8.jpg" alt="">
</p>

## Links

Here you can find additional relevant information such as datasheets and schematics.

- [`Official Viewe Repo`](https://github.com/VIEWESMART/UEDX24320028ESP32-2.8inch-Touch-Display)
- [`Product Link`](https://viewedisplay.com/product/esp32-2-8-inch-240x320-mcu-ips-tft-display-touch-screen-arduino-lvgl-wifi-ble-uart-smart-module/)

## Hardware Features

- ESP32-S3-N16R8, 16 MB Flash + 8 MB PSRAM (520 KB SRAM / 448 KB ROM)
- Type C USB programming port
- 2.8" TFT Touch 240×320 resolution
- MicroSD card slot
- WS2812B LED
- Buzzer
- RS485 & UART header


## Pin Overview

| IPS Screen Pin  | ESP32S3 Pin|
| :------------------: | :------------------:|
| CS         | IO42       |
| SCK         | IO40       |
| MOSI         | IO45       |
| DC         | IO41       |
| RST         | IO39       |
| BACKLIGHT   | IO13       |

| Touch Chip Pin  | ESP32S3 Pin|
| :------------------: | :------------------:|
| RST         | IO2(Not Used)|
| INT         | IO4(Not Used)|
| SDA         | IO1       |
| SCL         | IO3       |

| USB (CH340C) Pin  | ESP32S3 Pin|
| :------------------: | :------------------:|
| D+(USB-DP)    | IO20       |
| D-(USB-DN)    | IO19       |

| button Pin  | ESP32S3 Pin|
| :------------------: | :------------------:|
|   boot    | IO0       |
|   reset   | chip-en   |

| SD Card Pin  | ESP32S3 Pin|
| :------------------: | :------------------:|
| D1         | IO18       |
| D2         | IO15       |
| MOSI        | IO17       |
| MISO         | IO16       |

| UART/RS485 Pin  | ESP32S3 Pin|
| :------------------: | :------------------:|
| UARTTX         | IO43(RXD0)      |
| UARTRX         | IO44(TXD0)      |

| RGB LED Pin  | ESP32S3 Pin|
| :------------------: | :------------------:|
| RGB LED         | IO0   |

| Buzzer Pin  | ESP32S3 Pin|
| :------------------: | :------------------:|
|   buzzer    | IO38  |
