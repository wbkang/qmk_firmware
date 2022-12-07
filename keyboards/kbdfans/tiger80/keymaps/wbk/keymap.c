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
#include "os_detection.h"
#include <tmk_core/protocol/usb_device_state.h>

#include "print.h"

enum custom_keycodes {
    // key for switching language with alt+space like in windows
    MACOS_SWITCH_LANGUAGE = SAFE_RANGE,
    PRINT_KEYSTROKE_COUNT,
    PRINT_SETUP_PACKETS,
    CLEAR_SETUP_PACKETS
};

enum layers {
    _LAYER_BASE,
    _LAYER_MAC,
    _LAYER_FN,
    _LAYER_MAC_FN,
};

deferred_token last_tok;
long keystroke_counter = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_LAYER_BASE] = LAYOUT_tkl_f13_ansi_tsangan(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_PSCR, KC_SCRL, KC_PAUS,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    KC_DEL,  KC_END,  KC_PGDN,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,             KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                                       KC_RALT, MO(_LAYER_FN), KC_RIGHT_CTRL,    KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_LAYER_MAC] = LAYOUT_tkl_f13_ansi_tsangan(
        //ESC     F1         F2          F3          F4          F5          F6          F7          F8          F9          F10      F11       F12      F13            PRINT     SCLR      Pause
        KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS,
        //        1          2           3           4           5           6           7           8           9           0        -         EQUALS   Backspc        INS
        KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS,
        // TAB    Q          W           E           R           T           Y           U           I           O           P        [         ]        backslash      DEL   
        KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS,  KC_TRNS,
        // CAPS   A          S           D           F           G           H           J           K           L           ;        '                  ENTER
        KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,           KC_TRNS,
        // LSFT              Z           X           C           V           B           N           M           ,           .        /                  RSFT  
        KC_TRNS,             KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,           KC_TRNS,                KC_TRNS,
        KC_TRNS,  KC_LALT,   KC_LGUI,                   KC_TRNS,                                                             MACOS_SWITCH_LANGUAGE, MO(_LAYER_FN),  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_LAYER_FN] = LAYOUT_tkl_f13_ansi_tsangan(
        //ESC     F1         F2          F3          F4          F5          F6          F7          F8          F9          F10      F11       F12      F13            PRINT     SCLR      Pause
        KC_TRNS,  PRINT_SETUP_PACKETS,   CLEAR_SETUP_PACKETS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_MPRV, KC_MPLY,  KC_MNXT, KC_TRNS,       DB_TOGG,  KC_TRNS, QK_BOOTLOADER,
        //        1          2           3           4           5           6           7           8           9           0        -         EQUALS   Backspc        INS
        KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_KB_MUTE,KC_VOLD,KC_VOLU, KC_TRNS,       PRINT_KEYSTROKE_COUNT,  KC_TRNS, KC_TRNS,
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
    state = update_tri_layer_state(state, _LAYER_MAC, _LAYER_FN, _LAYER_MAC_FN);
    dprintf("Highest Layer is %d\n", get_highest_layer(state));
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


uint32_t execute_os_switching(uint32_t trigger_time, void *cb_arg) {
    os_variant_t detected = detected_host_os();
    dprintf("Detected OS is %d\n", detected);
    if (detected == OS_MACOS || detected == OS_IOS) {
        dprintf("Switching on mac layer\n");
        layer_on(_LAYER_MAC);
        return 0;
    }
    if (detected != OS_UNSURE) {
        dprintf("Switching off mac layer\n");
        layer_off(_LAYER_MAC);
        return 0;
    }
    
    return 0;
}

void notify_usb_device_state_change_user(enum usb_device_state usb_device_state) {
    // this is the USB reset event - so reset the os detection counter.
    if (USB_DEVICE_STATE_INIT == usb_device_state) {
        erase_wlength_data();
        // usb setup packets should be done by this time (500ms by the spec + some slack time).
        last_tok = defer_exec(1000, execute_os_switching, NULL);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        keystroke_counter++;
    }
    switch (keycode) {
        case MACOS_SWITCH_LANGUAGE:
        if (!record->event.pressed) {
            SEND_STRING(SS_LOPT(" "));
            return false;
        }
        break;
        case PRINT_KEYSTROKE_COUNT:
        if (!record->event.pressed) {
            char buf[100];
            sprintf(buf, "Key pressed %ld times", keystroke_counter);
            send_string(buf);
            return false;
        }
        break;
        case PRINT_SETUP_PACKETS:
        if (!record->event.pressed) {
            print_setupdump();
            return false;
        }
        break;
        case CLEAR_SETUP_PACKETS:
        if (!record->event.pressed) {
            clear_setupdump();
            return false;
        }
        break;
        default:

        break;
    }
    return true;
}



void keyboard_post_init_user(void) {
    rgblight_mode_noeeprom((uint8_t)RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv_noeeprom(HSV_WHITE);
}

