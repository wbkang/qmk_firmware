/* Copyright 2022 DZTECH <moyi4681@Live.cn>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// #include QMK_KEYBOARD_H
#include <quantum.h>
#include <rgblight/rgblight.h>
#include "../../config.h"
#include "../../tiger80.h"

#include "print.h"


enum layers {
    _LAYER_BASE,
    _LAYER_MAC,
    _LAYER_FN,
    _LAYER_MAC_FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_LAYER_BASE] = LAYOUT_tkl_f13_ansi_tsangan(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  /*KC_MUTE*/ QK_BOOTLOADER,    KC_PSCR, KC_SCRL, KC_PAUS,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    KC_DEL,  KC_END,  KC_PGDN,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,             KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                                       KC_RALT, MO(_LAYER_FN), KC_RIGHT_CTRL,    KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_LAYER_MAC] = LAYOUT_tkl_f13_ansi_tsangan(
        //ESC     F1         F2          F3          F4          F5          F6          F7          F8          F9          F10      F11       F12      F13            PRINT     SCLR      Pause
        KC_F1,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS,
        //        1          2           3           4           5           6           7           8           9           0        -         EQUALS   Backspc        INS
        KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS,
        // TAB    Q          W           E           R           T           Y           U           I           O           P        [         ]        backslash      DEL   
        KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS,  KC_TRNS,
        // CAPS   A          S           D           F           G           H           J           K           L           ;        '                  ENTER
        KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,           KC_TRNS,
        // LSFT              Z           X           C           V           B           N           M           ,           .        /                  RSFT  
        KC_TRNS,             KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,           KC_TRNS,                KC_TRNS,
        KC_TRNS,  OSL(_LAYER_MAC_FN),   KC_LGUI,                   KC_TRNS,                                                             A(KC_SPC), MO(_LAYER_FN),  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_LAYER_FN] = LAYOUT_tkl_f13_ansi_tsangan(
        //ESC     F1         F2          F3          F4          F5          F6          F7          F8          F9          F10      F11       F12      F13            PRINT     SCLR      Pause
        KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_MPRV,  KC_MPLY, KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS,
        //        1          2           3           4           5           6           7           8           9           0        -         EQUALS   Backspc        INS
        KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_KB_MUTE,KC_VOLD,KC_VOLU, KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS,
        // TAB    Q          W           E           R           T           Y           U           I           O           P        [         ]        backslash      DEL   
        KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS,  KC_TRNS,
        // CAPS   A          S           D           F           G           H           J           K           L           ;        '                  ENTER
        KC_CAPS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,           KC_TRNS,
        // LSFT              Z           X           C           V           B           N           M           ,           .        /                  RSFT  
        KC_TRNS,             KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    TG(_LAYER_MAC),    KC_TRNS,    KC_TRNS, KC_TRNS,           KC_TRNS,                KC_TRNS,
        KC_TRNS,  KC_TRNS,   KC_TRNS,                            KC_TRNS,                                                             KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_LAYER_MAC_FN] = LAYOUT_tkl_f13_ansi_tsangan(
        //ESC     F1         F2          F3          F4          F5          F6          F7          F8          F9          F10      F11       F12      F13            PRINT     SCLR      Pause
        KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS,
        //        1          2           3           4           5           6           7           8           9           0        -         EQUALS   Backspc        INS
        KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS ,KC_TRNS,  KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS,
        // TAB    Q          W           E           R           T           Y           U           I           O           P        [         ]        backslash      DEL   
        KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS,  KC_TRNS,
        // CAPS   A          S           D           F           G           H           J           K           L           ;        '                  ENTER
        KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,           KC_TRNS,
        // LSFT              Z           X           C           V           B           N           M           ,           .        /                  RSFT  
        KC_TRNS,             KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    C(G(KC_SPC)), KC_TRNS,           KC_TRNS,                KC_TRNS,
        KC_TRNS,  KC_TRNS,   KC_TRNS,                            KC_TRNS,                                                             KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    // [_LAYER_X] = LAYOUT_tkl_f13_ansi_tsangan(
    //     //ESC     F1         F2          F3          F4          F5          F6          F7          F8          F9          F10      F11       F12      F13            PRINT     SCLR      Pause
    //     KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS,
    //     //        1          2           3           4           5           6           7           8           9           0        -         EQUALS   Backspc        INS
    //     KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS ,KC_TRNS,  KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS,
    //     // TAB    Q          W           E           R           T           Y           U           I           O           P        [         ]        backslash      DEL   
    //     KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS,  KC_TRNS,
    //     // CAPS   A          S           D           F           G           H           J           K           L           ;        '                  ENTER
    //     KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,           KC_TRNS,
    //     // LSFT              Z           X           C           V           B           N           M           ,           .        /                  RSFT  
    //     KC_TRNS,             KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,           KC_TRNS,                KC_TRNS,
    //     KC_TRNS,  KC_TRNS,   KC_TRNS,                            KC_TRNS,                                                             KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    // ),
};


layer_state_t layer_state_set_user(layer_state_t state) {
    dprintf("Highest Layer is %d\n", get_highest_layer(state));
    state = update_tri_layer_state(state, _LAYER_MAC, _LAYER_FN, _LAYER_MAC_FN);
    switch (get_highest_layer(state)) {
    case _LAYER_BASE:
        rgblight_setrgb (RGB_WHITE);
        break;
    case _LAYER_MAC:
        rgblight_setrgb (RGB_RED);
        break;
    case _LAYER_MAC_FN:
        rgblight_setrgb (RGB_ORANGE);
        break;
    case _LAYER_FN:
        rgblight_setrgb (0x00,  0xFF, 0x00);
        break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb (0x00,  0x00, 0x00);
        break;
    }
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // dprintf("record->event.key is %d (rebuilt)\n", record->event.key);
    return true;
}


void keyboard_post_init_user(void) {
    // debug_enable=true;
    rgblight_mode_noeeprom((uint8_t)RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv_noeeprom(HSV_WHITE);
}