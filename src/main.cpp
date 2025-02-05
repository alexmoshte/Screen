#include "ttscrn.h"

static uint32_t draw_buf[DRAW_BUF_SIZE / 16];
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

static uint32_t my_tick_get_cb()
{
  return millis();
}

void setup()
{
  Serial.begin(115200);

  UpButton.setDebounceTime(DEBOUNCE_TIME);
  DownButton.setDebounceTime(DEBOUNCE_TIME);
  
  tft.begin();
  tft.setRotation(TFT_ROTATION);

  //Init disp
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
  TableParInit();
  TableFeatures(&objects);
  TableParameters(&objects);
  RowUpdate(3, "Table 3", "Bill", "6 min ago");
  
  pinMode(UP_BUTTON_PIN, INPUT_PULLDOWN);
  pinMode(DOWN_BUTTON_PIN, INPUT_PULLDOWN);

/*Attaching ISRs to the button pins*/
  attachInterrupt(digitalPinToInterrupt(UP_BUTTON_PIN), UpButtonISR, RISING);
  attachInterrupt(digitalPinToInterrupt(DOWN_BUTTON_PIN), DownButtonISR, RISING);
}

void loop()
{
 
  lv_timer_handler();
  lv_task_handler();
  vTaskDelay(pdMS_TO_TICKS(10)); //10ms
   
  ButtonScroll_Poll(&objects);

  // if(UpButtonPressed || DownButtonPressed)
  // {
  //    ButtonScroll_IT(&objects);
  // }
}