#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include "ui/ui.h"
#include <ezButton.h>

#define TFT_HOR_RES   480
#define TFT_VER_RES   320
#define TFT_ROTATION  LV_DISPLAY_ROTATION_0

#define UP_BUTTON_PIN 34
#define DOWN_BUTTON_PIN 35
#define DEBOUNCE_TIME 40
#define HOLD_TIME 100
#define REPEAT_RATE 5
#define SCROLL_AMOUNT 100

#define TABLE_ROW_NUMBERS 50
#define TABLE_COLUMN_NUMBERS 3

#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))


extern volatile bool UpButtonPressed;
extern volatile bool DownButtonPressed;
extern objects_t objects;

typedef struct
{
  char TableID[20];
  char OrderType[20];
  char TimeAgo[20];

} TableRowParameters;
extern TableRowParameters TabRowPar[TABLE_ROW_NUMBERS];

typedef struct 
{
  char TableID_owp[20];
  char OrderType_owp[20];
  char TimeAgo_owp[20];
}TbleOverwriteProtect;

extern TbleOverwriteProtect Tabowprct;

extern ezButton UpButton;
extern ezButton DownButton;

void UpButtonISR();
void DownButtonISR();
void TableParInit(void);
void TableFeatures(objects_t* ui);
void TableParameters(objects_t* ui);
void UpScroll(TbleOverwriteProtect* owptrct);
void DownScroll(TbleOverwriteProtect* owptrct);
void ButtonScroll_Poll(objects_t *ui);
void ButtonScroll_ez(objects_t *ui);
void ButtonScroll_IT(objects_t *ui);
void RowUpdate(uint8_t row, const char* TableID, const char* OrderType, const char* TimeAgo);