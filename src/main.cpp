/*
   MIT License

  Copyright (c) 2025 Felix Biego

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

*/

#include <Arduino.h>

#include "display.hpp"
#include <lvgl.h>
#include <WS2812FX.h>

#define LED_COUNT 1
#define LED_PIN 0


LGFX tft;
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void my_disp_flush(lv_display_t *display, const lv_area_t *area, unsigned char *data)
{
  uint32_t w = lv_area_get_width(area);
  uint32_t h = lv_area_get_height(area);
  tft.pushImageDMA(area->x1, area->y1, w, h, (uint16_t *)data);
  lv_display_flush_ready(display); /* tell lvgl that flushing is done */
}


void my_touchpad_read(lv_indev_t *indev_driver, lv_indev_data_t *data)
{
  uint16_t x, y;
  uint8_t touched = tft.getTouch(&x, &y);
  if (!touched)
  {
    data->state = LV_INDEV_STATE_RELEASED;
  }
  else
  {
    data->state = LV_INDEV_STATE_PRESSED;
    /*Set the coordinates*/
    data->point.x = x;
    data->point.y = y;
  }
}

uint32_t my_tick(void)
{
  return millis();
}

void on_slider_event(lv_event_t *e)
{
  lv_obj_t *slider = (lv_obj_t *)lv_event_get_target(e);
  uint16_t value = lv_slider_get_value(slider);
  tft.setBrightness(value);
  ws2812fx.setBrightness(value);
}

void setup()
{

  Serial.begin(115200);

  tft.init();
  tft.setBrightness(255);

  lv_init();

  lv_tick_set_cb(my_tick);

  lv_display_t *lv_display = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);
  lv_display_set_color_format(lv_display, LV_COLOR_FORMAT_RGB565_SWAPPED);
  lv_display_set_flush_cb(lv_display, my_disp_flush);

  uint8_t *lv_buffer = (uint8_t *)heap_caps_malloc(LV_BUFFER_SIZE, MALLOC_CAP_DMA | MALLOC_CAP_SPIRAM);
  uint8_t *lv_buffer_2 = (uint8_t *)heap_caps_malloc(LV_BUFFER_SIZE, MALLOC_CAP_DMA | MALLOC_CAP_SPIRAM);
  lv_display_set_buffers(lv_display, lv_buffer, lv_buffer_2, LV_BUFFER_SIZE, LV_DISPLAY_RENDER_MODE_PARTIAL);

  lv_indev_t *lv_input = lv_indev_create();
  lv_indev_set_type(lv_input, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(lv_input, my_touchpad_read);

  lv_obj_t *label1 = lv_label_create(lv_screen_active());
  lv_obj_align(label1, LV_ALIGN_TOP_MID, 0, 30);
  lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);
  lv_obj_set_width(label1, SCREEN_WIDTH - 50);
  lv_label_set_text(label1, "LVGL test\n"
                            "You should be able to move the slider below");

  /*Create a slider below the label*/
  lv_obj_t *slider1 = lv_slider_create(lv_screen_active());
  lv_obj_set_width(slider1, SCREEN_WIDTH - 60);
  lv_obj_align_to(slider1, label1, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
  lv_slider_set_range(slider1, 1, 255);
  lv_slider_set_value(slider1, 255, LV_ANIM_OFF);
  lv_obj_add_event_cb(slider1, on_slider_event, LV_EVENT_VALUE_CHANGED, NULL);

  ws2812fx.init();
  ws2812fx.setBrightness(255);
  ws2812fx.setSpeed(1000);
  ws2812fx.setColor(0x007BFF);
  ws2812fx.setMode(FX_MODE_STATIC);
  ws2812fx.start();

}

void loop()
{
  lv_timer_handler();
  delay(5);
  ws2812fx.service();
}
