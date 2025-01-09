
#include <Arduino.h>

#include <TFT_eSPI.h>
#include <lvgl.h>
#include "ui/ui.h"

#define TFT_HOR_RES   480
#define TFT_VER_RES   320
#define TFT_ROTATION  LV_DISPLAY_ROTATION_0

#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
static uint32_t draw_buf[DRAW_BUF_SIZE / 16];
objects_t objects;
//static uint32_t *draw_buf;

TFT_eSPI tft = TFT_eSPI();

void my_disp_flush( lv_display_t *disp, const lv_area_t *area, uint8_t * px_map)
{   
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);
  uint32_t wh = w*h;

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)px_map, w * h, true);
  tft.endWrite();
  lv_disp_flush_ready(disp);
}

static uint32_t my_tick_get_cb(){
  return millis();
}

void setup()
{
  Serial.begin(115200);

  //  draw_buf = (uint32_t *)malloc(DRAW_BUF_SIZE);
  // if(!draw_buf)
  // {
  //   Serial.println("Failed to allocate draw buffer");
  //   while(1);
  // }

  tft.begin();
  tft.setRotation(TFT_ROTATION);

  //init disp
  lv_init();
    lv_tick_set_cb(my_tick_get_cb);

    lv_display_t * disp;
    /*TFT_eSPI can be enabled through lv_conf.h to initialize the display in a simple way*/
    disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));

    /*Else initialize the display yourself*/
    disp = lv_display_create(TFT_HOR_RES, TFT_VER_RES);
    lv_display_set_flush_cb(disp, my_disp_flush);
    lv_display_set_buffers(disp, draw_buf, NULL, sizeof(draw_buf), LV_DISPLAY_RENDER_MODE_PARTIAL);

  ui_init();

    lv_table_set_column_count(objects.order_table, 3);
    lv_table_set_column_width(objects.order_table, 0, 160);
    lv_table_set_column_width(objects.order_table, 1, 160);
    lv_table_set_column_width(objects.order_table, 2, 160);

    lv_table_set_cell_value(objects.order_table,0,0,"Table 1");
    lv_table_set_cell_value(objects.order_table,0,1,"Bill");
    lv_table_set_cell_value(objects.order_table,0,2,"2");

    lv_table_set_cell_value(objects.order_table,1,0,"Table 2");
    lv_table_set_cell_value(objects.order_table,1,1,"Call");
    lv_table_set_cell_value(objects.order_table,1,2,"5");

    lv_table_set_cell_value(objects.order_table,2,0,"Table 3");
    lv_table_set_cell_value(objects.order_table,2,1,"Served");
    lv_table_set_cell_value(objects.order_table,2,2,"0");

    lv_table_set_cell_value(objects.order_table,3,0,"Table 4");
    lv_table_set_cell_value(objects.order_table,3,1,"Cancel");
    lv_table_set_cell_value(objects.order_table,3,2,"1");

    lv_table_set_cell_value(objects.order_table,4,0,"Table 5");
    lv_table_set_cell_value(objects.order_table,4,1,"Call");
    lv_table_set_cell_value(objects.order_table,4,2,"3");

  lv_table_set_row_count(objects.order_table, 50);
  //lv_timer_handler();
  //lv_task_handler();
}
void loop()
{
  lv_timer_handler();
  lv_task_handler();
  delay(2);
}