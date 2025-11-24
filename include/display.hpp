#pragma once

#include "Arduino_GFX_Library.h"
#include "TouchDrvCSTXXX.hpp"

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define LV_BUFFER_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT * 2)

#define LCD_DC 41
#define LCD_CS 42
#define LCD_SCK 40
#define LCD_MOSI 45
#define LCD_MISO -1
#define LCD_RST 39

#define LCD_BL 13

#define LCD_IM0 47
#define LCD_IM1 48

#define TOUCH_SDA 1
#define TOUCH_SCL 3
#define TOUCH_INT 4
#define TOUCH_RST 2

#define TOUCH_ADDR 0x2E

class LGFX
{
public:
    Arduino_DataBus *bus = new Arduino_ESP32SPIDMA(LCD_DC /* DC */, LCD_CS /* CS */, LCD_SCK /* SCK */, LCD_MOSI /* MOSI */, LCD_MISO /* MISO */, SPI2_HOST /* spi_num */);

    Arduino_GFX *gfx = new Arduino_ST7789(
        bus, LCD_RST /* RST */, 4 /* rotation */, false /* IPS */,
        SCREEN_WIDTH /* width */, SCREEN_HEIGHT /* height */);
    TouchDrvCST816 touch;

    LGFX()
    {
    }

    void pushImageDMA(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t *data)
    {
        int size = w * h;
        for (int i = 0; i < size; i++)
        {
            uint16_t red = data[i] & 0b0001111100000000;
            uint16_t green = data[i] & 0b1110000000000111;
            uint16_t blue = data[i] & 0b0000000011111000;
            data[i] = (green) | (red >> 5) | (blue << 5);
        }
        gfx->draw16bitBeRGBBitmap(x, y, data, w, h);
    }

    bool getTouch(uint16_t *x, uint16_t *y)
    {
        int16_t x_arr[5], y_arr[5];
        uint8_t touched = touch.getPoint(x_arr, y_arr, touch.getSupportTouchPoint());
        *x = x_arr[0];
        *y = y_arr[0];
        return touched;
    }

    void setBrightness(uint8_t brightness)
    {
        ledcWrite(13, brightness);
    }

    void init(void)
    {
        pinMode(LCD_IM0, OUTPUT);
        digitalWrite(LCD_IM0, LOW);
        pinMode(LCD_IM1, OUTPUT);
        digitalWrite(LCD_IM1, HIGH);

        ledcAttach(LCD_BL, 12000, 8);

        gfx->begin();

        touch.setPins(TOUCH_RST, TOUCH_INT);
        touch.begin(Wire, TOUCH_ADDR, TOUCH_SDA, TOUCH_SCL);
    }
};