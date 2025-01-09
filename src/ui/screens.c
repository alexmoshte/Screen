#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 320);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // header_panel
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.header_panel = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 40);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffd74242), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // header_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.header_title = obj;
                    lv_obj_set_pos(obj, 138, -8);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "ORDER QUEUE");
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff030303), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // veno_logo
                    lv_obj_t *obj = lv_img_create(parent_obj);
                    objects.veno_logo = obj;
                    lv_obj_set_pos(obj, -53, -12);
                    lv_obj_set_size(obj, 174, 32);
                    lv_img_set_src(obj, &img_va_logo_trnsprnt_red);
                    lv_img_set_zoom(obj, 60);
                    lv_img_set_angle(obj, 1);
                }
            }
        }
        {
            // order_table
            lv_obj_t *obj = lv_table_create(parent_obj);
            objects.order_table = obj;
            lv_obj_set_pos(obj, 0, 75);
            lv_obj_set_size(obj, 480, 245);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffd74242), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // tab_ID_pan
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.tab_id_pan = obj;
            lv_obj_set_pos(obj, 0, 40);
            lv_obj_set_size(obj, 160, 35);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffd74242), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // tab_ID_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.tab_id_text = obj;
                    lv_obj_set_pos(obj, 21, -11);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Table ID");
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_decor(obj, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // order_pan
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.order_pan = obj;
            lv_obj_set_pos(obj, 159, 40);
            lv_obj_set_size(obj, 160, 35);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffd74242), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // order_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.order_text = obj;
                    lv_obj_set_pos(obj, 33, -11);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Order");
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // req_No_pan
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.req_no_pan = obj;
            lv_obj_set_pos(obj, 319, 40);
            lv_obj_set_size(obj, 161, 35);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffd74242), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // req_No_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.req_no_text = obj;
                    lv_obj_set_pos(obj, 3, -11);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Requests");
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

void tick_screen_main() {
}


void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
}

typedef void (*tick_screen_func_t)();

tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};

void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
