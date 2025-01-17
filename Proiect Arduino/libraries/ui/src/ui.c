// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_ecranceas2
void ui_ecranceas2_screen_init(void);
void ui_event_ecranceas2(lv_event_t * e);
lv_obj_t * ui_ecranceas2;
lv_obj_t * ui_ora;
lv_obj_t * ui_ora1;
lv_obj_t * ui_ora2;
lv_obj_t * ui_douap1;
lv_obj_t * ui_min1;
lv_obj_t * ui_min2;
lv_obj_t * ui_douap2;
lv_obj_t * ui_sec0;
lv_obj_t * ui_sec1;
lv_obj_t * ui_baterie;
lv_obj_t * ui_procent;
lv_obj_t * ui_nr;
lv_obj_t * ui_procent1;
lv_obj_t * ui_data;
lv_obj_t * ui_zisapt;
lv_obj_t * ui_zi;
lv_obj_t * ui_luna;
lv_obj_t * ui_an;
lv_obj_t * ui_contpasi;
lv_obj_t * ui_pasi;
lv_obj_t * ui_nrpasi;
lv_obj_t * ui_Label9;
lv_obj_t * ui_contpuls;
lv_obj_t * ui_bpm;
lv_obj_t * ui_puls;
lv_obj_t * ui_ubpm;
lv_obj_t * ui_contdistanta;
lv_obj_t * ui_distanta;
lv_obj_t * ui_nrdistanta;
lv_obj_t * ui_kmdisanta;
lv_obj_t * ui_contox;
lv_obj_t * ui_oxigen;
lv_obj_t * ui_nrox;
lv_obj_t * ui_procentox;
lv_obj_t * ui_contcal;
lv_obj_t * ui_cal;
lv_obj_t * ui_nrcal;
lv_obj_t * ui_kcal;


// SCREEN: ui_busola
void ui_busola_screen_init(void);
void ui_event_busola(lv_event_t * e);
lv_obj_t * ui_busola;
lv_obj_t * ui_imunghi;
lv_obj_t * ui_imsageata;
lv_obj_t * ui_unghi;
lv_obj_t * ui_directie;


// SCREEN: ui_ecranhealth
void ui_ecranhealth_screen_init(void);
void ui_event_ecranhealth(lv_event_t * e);
lv_obj_t * ui_ecranhealth;
lv_obj_t * ui_inima;
lv_obj_t * ui_Arc1;
lv_obj_t * ui_Arc2;
void ui_event_butonmasurare(lv_event_t * e);
lv_obj_t * ui_butonmasurare;
lv_obj_t * ui_Masurare;
lv_obj_t * ui_BPM;
lv_obj_t * ui_numarpuls;
lv_obj_t * ui_Spo2;
lv_obj_t * ui_Spo2value;
lv_obj_t * ui_Sanatate;
lv_obj_t * ui_imaginespo2;


// SCREEN: ui_ecransetari
void ui_ecransetari_screen_init(void);
void ui_event_ecransetari(lv_event_t * e);
lv_obj_t * ui_ecransetari;
lv_obj_t * ui_setariscris;
void ui_event_butonwifi(lv_event_t * e);
lv_obj_t * ui_butonwifi;
lv_obj_t * ui_wifi;
lv_obj_t * ui_switchwifi;
void ui_event_butonluminozitate(lv_event_t * e);
lv_obj_t * ui_butonluminozitate;
lv_obj_t * ui_luminoz;
void ui_event_butondespre(lv_event_t * e);
lv_obj_t * ui_butondespre;
lv_obj_t * ui_despre;
lv_obj_t * ui_butonbluetooth;
lv_obj_t * ui_bluetooth;
lv_obj_t * ui_switchble;


// SCREEN: ui_ecranlumina
void ui_ecranlumina_screen_init(void);
void ui_event_ecranlumina(lv_event_t * e);
lv_obj_t * ui_ecranlumina;
lv_obj_t * ui_Slider1;


// SCREEN: ui_ecrandespre
void ui_ecrandespre_screen_init(void);
void ui_event_ecrandespre(lv_event_t * e);
lv_obj_t * ui_ecrandespre;
lv_obj_t * ui_TextArea1;
lv_obj_t * ui_Label3;


// SCREEN: ui_ecranalerte
void ui_ecranalerte_screen_init(void);
lv_obj_t * ui_ecranalerte;
lv_obj_t * ui_Textalerta;


// SCREEN: ui_ecranbluetooth
void ui_ecranbluetooth_screen_init(void);
lv_obj_t * ui_ecranbluetooth;
lv_obj_t * ui_numedispozitiv;
lv_obj_t * ui_dorestesaseconecteze;
lv_obj_t * ui_refuza;
lv_obj_t * ui_refuzal;
lv_obj_t * ui_accepta;
lv_obj_t * ui_acceptal;


// SCREEN: ui_calibraremagscreen
void ui_calibraremagscreen_screen_init(void);
void ui_event_calibraremagscreen(lv_event_t * e);
lv_obj_t * ui_calibraremagscreen;
void ui_event_butoncal(lv_event_t * e);
lv_obj_t * ui_butoncal;
lv_obj_t * ui_textcalibrare;
lv_obj_t * ui_textecalibrare;
lv_obj_t * ui_textmag;
lv_obj_t * ui_textmag1;
lv_obj_t * ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_ecranceas2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_busola, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_busola_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_ecransetari, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_ecransetari_screen_init);
    }
}
void ui_event_busola(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_ecranceas2, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_ecranceas2_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_ecranhealth, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_ecranhealth_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_calibraremagscreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_calibraremagscreen_screen_init);
    }
}
void ui_event_ecranhealth(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_ecransetari, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_ecransetari_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_busola, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_busola_screen_init);
    }
}
void ui_event_butonmasurare(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SHORT_CLICKED) {
        (e);
    }
}
void ui_event_ecransetari(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_ecranhealth, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_ecranhealth_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_ecranceas2, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_ecranceas2_screen_init);
    }
}
void ui_event_butonwifi(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        scanarewifihandlle(e);
    }
}
void ui_event_butonluminozitate(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ecranlumina, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_ecranlumina_screen_init);
    }
}
void ui_event_butondespre(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ecrandespre, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_ecrandespre_screen_init);
    }
}
void ui_event_ecranlumina(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_ecransetari, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_ecransetari_screen_init);
    }
}
void ui_event_ecrandespre(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_ecransetari, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_ecransetari_screen_init);
    }
}
void ui_event_calibraremagscreen(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_busola, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_busola_screen_init);
    }
}
void ui_event_butoncal(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        (e);
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_ecranceas2_screen_init();
    ui_busola_screen_init();
    ui_ecranhealth_screen_init();
    ui_ecransetari_screen_init();
    ui_ecranlumina_screen_init();
    ui_ecrandespre_screen_init();
    ui_ecranalerte_screen_init();
    ui_ecranbluetooth_screen_init();
    ui_calibraremagscreen_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_ecranceas2);
}
