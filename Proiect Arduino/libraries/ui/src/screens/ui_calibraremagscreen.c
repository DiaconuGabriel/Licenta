// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_calibraremagscreen_screen_init(void)
{
    ui_calibraremagscreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_calibraremagscreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_calibraremagscreen, lv_color_hex(0x293039), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_calibraremagscreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_butoncal = lv_btn_create(ui_calibraremagscreen);
    lv_obj_set_width(ui_butoncal, 159);
    lv_obj_set_height(ui_butoncal, 38);
    lv_obj_set_align(ui_butoncal, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_butoncal, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_butoncal, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_butoncal, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_butoncal, lv_color_hex(0x181C20), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_butoncal, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_butoncal, lv_color_hex(0x181C20), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_butoncal, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_textcalibrare = lv_label_create(ui_butoncal);
    lv_obj_set_width(ui_textcalibrare, 95);
    lv_obj_set_height(ui_textcalibrare, 20);
    lv_obj_set_x(ui_textcalibrare, 2);
    lv_obj_set_y(ui_textcalibrare, 0);
    lv_obj_set_align(ui_textcalibrare, LV_ALIGN_CENTER);
    lv_label_set_text(ui_textcalibrare, "Calibreaza");
    lv_obj_set_style_text_color(ui_textcalibrare, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_textcalibrare, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_textcalibrare, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_textecalibrare = lv_obj_create(ui_calibraremagscreen);
    lv_obj_remove_style_all(ui_textecalibrare);
    lv_obj_set_width(ui_textecalibrare, 195);
    lv_obj_set_height(ui_textecalibrare, 195);
    lv_obj_set_align(ui_textecalibrare, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_textecalibrare, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_textecalibrare, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_textecalibrare, lv_color_hex(0x38414C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_textecalibrare, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_textecalibrare, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_textecalibrare, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_textecalibrare, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_textmag = lv_label_create(ui_textecalibrare);
    lv_obj_set_width(ui_textmag, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_textmag, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_textmag, 0);
    lv_obj_set_y(ui_textmag, -15);
    lv_obj_set_align(ui_textmag, LV_ALIGN_CENTER);
    lv_label_set_text(ui_textmag, "Roteste ceasul ");

    ui_textmag1 = lv_label_create(ui_textecalibrare);
    lv_obj_set_width(ui_textmag1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_textmag1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_textmag1, -1);
    lv_obj_set_y(ui_textmag1, 14);
    lv_obj_set_align(ui_textmag1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_textmag1, "in forma de 8");

    lv_obj_add_event_cb(ui_butoncal, ui_event_butoncal, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_calibraremagscreen, ui_event_calibraremagscreen, LV_EVENT_ALL, NULL);

}
