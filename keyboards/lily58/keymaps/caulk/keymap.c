/* Copyright 2020 Naoki Katahira
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

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "lib/lib8tion/lib8tion.h"
#include "pointing_device_auto_mouse.h"
#include "users/caulk/caulk.h"

enum layer_number {
    _BASE = 0,
    _NAV,
    _SYM,
    _ADJ,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* BASE
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Ctrl |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
     * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
     * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   | NAV  | LGUI | Alt  | /Space  /       \Enter \  |BackSP| RGUI | SYM  |
     *                   |      |      |      |/       /         \      \ |      |      |      |
     *                   `-------------------''-------'           '------''--------------------'
     */

    [_BASE] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_GRV, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINS, KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LBRC, KC_RBRC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, MO(_NAV), KC_LGUI, KC_LALT, LT(_NAV, KC_SPC), LT(_SYM, KC_ENT), KC_BSPC, KC_RGUI, MO(_SYM)),

    /* NAV */
    [_NAV] = LAYOUT(    OSM(MOD_LALT), KC_TRNS,         KC_TRNS,         KC_TRNS,         KC_TRNS,         KC_TRNS,                           KC_TRNS,         KC_TRNS,         KC_TRNS,         KC_TRNS,         KC_TRNS,         KC_TRNS,
 KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_INS, KC_DEL, KC_TRNS, KC_6, KC_7, KC_8, KC_9, KC_0, LCTL(KC_LEFT), KC_DOWN, KC_UP, LCTL(KC_RGHT), KC_BSPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    /* SYM */
    [_SYM] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_GRV, KC_TILD, KC_QUOT, KC_DQUO, KC_TRNS, KC_TRNS, KC_PIPE, KC_BSLS, KC_MINS, KC_EQL, KC_PLUS, KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_TRNS, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_AMPR, CW_TOGG, KC_CIRC, KC_COLN, KC_SCLN, KC_UNDS, KC_TRNS, KC_TRNS, KC_TRNS, KC_QUES, KC_LCBR, KC_RCBR, KC_LABK, KC_RABK, KC_SLSH, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    /* ADJ */
    [_ADJ] = LAYOUT(
        QK_CLEAR_EEPROM, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                   KC_TRNS, KC_BTN4, KC_BTN5, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                   HK_S_MODE_T, KC_BTN1, KC_BTN3, KC_BTN2, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                 KC_TRNS, HK_D_MODE_T, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _NAV, _SYM, _ADJ);
    return state;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;
        case KC_MINS:
        case KC_UNDS:
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
            return true;
        default:
            return false;
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(_NAV, KC_SPC):
            return 150;
        case LT(_SYM, KC_ENT):
            return 170;
        default:
            return TAPPING_TERM;
    }
}

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
void keyboard_post_init_keymap(void) {
    set_auto_mouse_layer(_ADJ);
    set_auto_mouse_enable(true);

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
#endif
}
#endif

#ifdef RGB_MATRIX_ENABLE
static void set_nav_rgb(void) {
    uint8_t time = (uint8_t)(timer_read() >> 3);

    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        led_flags_t flags = g_led_config.flags[i];

        if (HAS_FLAGS(flags, LED_FLAG_UNDERGLOW)) {
            uint8_t wave = sin8((uint8_t)(time + (i * 8)));
            uint8_t red = (uint16_t)wave * 140 / 255;
            uint8_t blue = (uint16_t)(255 - wave) * 140 / 255;
            rgb_matrix_set_color(i, red, 0, blue);
        } else if (HAS_ANY_FLAGS(flags, (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR))) {
            rgb_matrix_set_color(i, 255, 255, 255);
        }
    }
}

bool rgb_matrix_indicators_user(void) {
    if (!rgb_matrix_is_enabled()) {
        return false;
    }

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            rgb_matrix_set_color_all(0, 255, 0);
            break;
        case _NAV:
            set_nav_rgb();
            break;
        case _SYM:
            rgb_matrix_set_color_all(128, 0, 255);
            break;
        case _ADJ:
            rgb_matrix_set_color_all(255, 80, 0);
            break;
        default:
            break;
    }

    return true;
}
#endif

#if defined(OLED_ENABLE) && !defined(HK_OLED_ENABLE)

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    return rotation;
}

static void render_logo(void) {
    static const char PROGMEM logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00};

    oled_write_P(logo, false);
}
char keylog_str[24]  = {};
char keylogs_str[21] = {};
int  keylogs_str_idx = 0;

const char code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';
    if (keycode < 60) {
        name = code_to_name[keycode];
    }

    // update keylog
    snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c", record->event.key.row, record->event.key.col, keycode, name);

    // update keylogs
    if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
        keylogs_str_idx = 0;
        for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
            keylogs_str[i] = ' ';
        }
    }

    keylogs_str[keylogs_str_idx] = name;
    keylogs_str_idx++;
}

const char *read_keylog(void) {
    return keylog_str;
}

const char *read_keylogs(void) {
    return keylogs_str;
}
// new

bool oled_task_user(void) {
#    ifdef OLED_FLIP
    bool condition = !is_keyboard_master();
#    else
    bool condition = is_keyboard_master();
#    endif
    if (condition) {
        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);

        switch (get_highest_layer(layer_state)) {
            case _BASE:
                oled_write_ln_P(PSTR("Base"), false);
                break;
            case _NAV:
                oled_write_ln_P(PSTR("Nav"), false);
                break;
            case _SYM:
                oled_write_ln_P(PSTR("Sym"), false);
                break;
            case _ADJ:
                oled_write_ln_P(PSTR("Adj"), false);
                break;
            default:
                oled_write_ln_P(PSTR("Undef"), false);
        }

        oled_write_ln(read_keylog(), false);
        oled_write_ln(read_keylogs(), false);

    } else {
        render_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#    ifdef OLED_ENABLE
        set_keylog(keycode, record);
#    endif
        // set_timelog();
    }
    return true;
}

#endif // OLED_ENABLE
