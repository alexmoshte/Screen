#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *header_panel;
    lv_obj_t *header_title;
    lv_obj_t *veno_logo;
    lv_obj_t *order_table;
    lv_obj_t *tab_id_pan;
    lv_obj_t *tab_id_text;
    lv_obj_t *order_pan;
    lv_obj_t *order_text;
    lv_obj_t *timestamp_pan;
    lv_obj_t *timestamp;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
};

void create_screen_main();
void tick_screen_main();

void create_screens();
void tick_screen(int screen_index);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/