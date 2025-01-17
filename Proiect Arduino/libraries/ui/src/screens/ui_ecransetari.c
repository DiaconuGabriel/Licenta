// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_ecransetari_screen_init(void)
{
    ui_ecransetari = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ecransetari, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ecransetari, lv_color_hex(0x2C3038), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ecransetari, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_setariscris = lv_textarea_create(ui_ecransetari);
    lv_obj_set_width(ui_setariscris, 243);
    lv_obj_set_height(ui_setariscris, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_x(ui_setariscris, 0);
    lv_obj_set_y(ui_setariscris, -102);
    lv_obj_set_align(ui_setariscris, LV_ALIGN_CENTER);
    lv_textarea_set_max_length(ui_setariscris, 100);
    lv_textarea_set_text(ui_setariscris, "Setari\n");
    lv_textarea_set_one_line(ui_setariscris, true);
    lv_obj_set_style_text_color(ui_setariscris, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_setariscris, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_setariscris, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_setariscris, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_setariscris, lv_color_hex(0x181C20), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_setariscris, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_setariscris, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_setariscris, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_setariscris, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_setariscris, 11, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_setariscris, -18, LV_PART_MAIN | LV_STATE_DEFAULT);



    ui_butonwifi = lv_btn_create(ui_ecransetari);
    lv_obj_set_width(ui_butonwifi, 140);
    lv_obj_set_height(ui_butonwifi, 33);
    lv_obj_set_x(ui_butonwifi, 0);
    lv_obj_set_y(ui_butonwifi, -53);
    lv_obj_set_align(ui_butonwifi, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_butonwifi, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_butonwifi, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_butonwifi, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_butonwifi, lv_color_hex(0x181C20), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_butonwifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_butonwifi, lv_color_hex(0x181C20), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_butonwifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_butonwifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_butonwifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_butonwifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_butonwifi, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_wifi = lv_label_create(ui_butonwifi);
    lv_obj_set_width(ui_wifi, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_wifi, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_wifi, -16);
    lv_obj_set_y(ui_wifi, 2);
    lv_obj_set_align(ui_wifi, LV_ALIGN_CENTER);
    lv_label_set_text(ui_wifi, "WIFI");
    lv_obj_set_style_text_color(ui_wifi, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_wifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_wifi, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_switchwifi = lv_switch_create(ui_butonwifi);
    lv_obj_set_width(ui_switchwifi, 35);
    lv_obj_set_height(ui_switchwifi, 18);
    lv_obj_set_x(ui_switchwifi, 43);
    lv_obj_set_y(ui_switchwifi, 2);
    lv_obj_set_align(ui_switchwifi, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_switchwifi, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE);     /// Flags

    lv_obj_set_style_bg_color(ui_switchwifi, lv_color_hex(0x181C20), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_switchwifi, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_butonluminozitate = lv_btn_create(ui_ecransetari);
    lv_obj_set_width(ui_butonluminozitate, 140);
    lv_obj_set_height(ui_butonluminozitate, 33);
    lv_obj_set_x(ui_butonluminozitate, 0);
    lv_obj_set_y(ui_butonluminozitate, 37);
    lv_obj_set_align(ui_butonluminozitate, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_butonluminozitate, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_butonluminozitate, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_butonluminozitate, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_butonluminozitate, lv_color_hex(0x181C20), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_butonluminozitate, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_butonluminozitate, lv_color_hex(0x181C20), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_butonluminozitate, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_butonluminozitate, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_butonluminozitate, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_butonluminozitate, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_butonluminozitate, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_luminoz = lv_label_create(ui_butonluminozitate);
    lv_obj_set_width(ui_luminoz, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_luminoz, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_luminoz, LV_ALIGN_CENTER);
    lv_label_set_text(ui_luminoz, "Luminozitate");
    lv_obj_set_style_text_color(ui_luminoz, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_luminoz, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_luminoz, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_butondespre = lv_btn_create(ui_ecransetari);
    lv_obj_set_width(ui_butondespre, 140);
    lv_obj_set_height(ui_butondespre, 33);
    lv_obj_set_x(ui_butondespre, 1);
    lv_obj_set_y(ui_butondespre, 82);
    lv_obj_set_align(ui_butondespre, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_butondespre, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_butondespre, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_butondespre, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_butondespre, lv_color_hex(0x181C20), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_butondespre, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_butondespre, lv_color_hex(0x181C20), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_butondespre, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_butondespre, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_butondespre, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_butondespre, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_butondespre, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_despre = lv_label_create(ui_butondespre);
    lv_obj_set_width(ui_despre, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_despre, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_despre, LV_ALIGN_CENTER);
    lv_label_set_text(ui_despre, "Despre");
    lv_obj_set_style_text_color(ui_despre, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_despre, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_despre, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_butonbluetooth = lv_btn_create(ui_ecransetari);
    lv_obj_set_width(ui_butonbluetooth, 140);
    lv_obj_set_height(ui_butonbluetooth, 33);
    lv_obj_set_x(ui_butonbluetooth, 0);
    lv_obj_set_y(ui_butonbluetooth, -8);
    lv_obj_set_align(ui_butonbluetooth, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_butonbluetooth, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_butonbluetooth, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_butonbluetooth, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_butonbluetooth, lv_color_hex(0x181C20), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_butonbluetooth, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_butonbluetooth, lv_color_hex(0x181C20), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_butonbluetooth, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_butonbluetooth, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_butonbluetooth, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_butonbluetooth, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_butonbluetooth, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_bluetooth = lv_label_create(ui_butonbluetooth);
    lv_obj_set_width(ui_bluetooth, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_bluetooth, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_bluetooth, -20);
    lv_obj_set_y(ui_bluetooth, 2);
    lv_obj_set_align(ui_bluetooth, LV_ALIGN_CENTER);
    lv_label_set_text(ui_bluetooth, "Bluetooth");
    lv_obj_set_style_text_color(ui_bluetooth, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_bluetooth, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_bluetooth, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_switchble = lv_switch_create(ui_butonbluetooth);
    lv_obj_set_width(ui_switchble, 35);
    lv_obj_set_height(ui_switchble, 18);
    lv_obj_set_x(ui_switchble, 44);
    lv_obj_set_y(ui_switchble, 2);
    lv_obj_set_align(ui_switchble, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_switchble, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE);     /// Flags

    lv_obj_set_style_bg_color(ui_switchble, lv_color_hex(0x181C20), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_switchble, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_butonwifi, ui_event_butonwifi, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_butonluminozitate, ui_event_butonluminozitate, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_butondespre, ui_event_butondespre, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ecransetari, ui_event_ecransetari, LV_EVENT_ALL, NULL);

}
