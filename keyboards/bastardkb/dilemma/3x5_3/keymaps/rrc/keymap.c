/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2023 casuanoob <casuanoob@hotmail.com> (@casuanoob)
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

enum dilemma_keymap_layers {
    LAYER_BASE = 0,
    LAYER_FUNCTION,
    LAYER_NAVIGATION,
    LAYER_MEDIA,
    LAYER_POINTER,
    LAYER_NUMERAL,
    LAYER_SYMBOLS,
};

// Automatically enable sniping-mode on the pointer layer.
// #define DILEMMA_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#define ESC_MED LT(LAYER_MEDIA, KC_ESC)
#define SPC_NAV LT(LAYER_NAVIGATION, KC_SPC)
#define TAB_FUN LT(LAYER_FUNCTION, KC_TAB)
#define ENT_SYM LT(LAYER_SYMBOLS, KC_ENT)
#define BSP_NUM LT(LAYER_NUMERAL, KC_BSPC)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE


#define LYR_BSE 0
#define LYR_SYM 1
#define LYR_NAV 2
#define LYR_NUM 3

// clang-format off
/** \brief QWERTY layout (3 rows, 10 columns). */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LYR_BSE] = LAYOUT_split_3x5_3(
         KC_Q,          KC_W,          KC_E,          KC_R,          KC_T,                           KC_Y,                  KC_U,                 KC_I,          KC_O,          KC_P,
         LALT_T(KC_A),  RGUI_T(KC_S),  LCTL_T(KC_D),  LSFT_T(KC_F),  KC_G,                           KC_H,                  RSFT_T(KC_J),         RCTL_T(KC_K),  RGUI_T(KC_L),  RALT_T(KC_SCLN),
         KC_Z,          KC_X,          KC_C,          KC_V,          KC_B,                           KC_N,                  KC_M,                 KC_COMM,       KC_DOT,        KC_SLSH,
                                       KC_ESC,        KC_SPC,        LT(LYR_NAV, KC_TAB),            LT(LYR_NUM, KC_BSPC),  LT(LYR_SYM, KC_ENT),  KC_ESC
    ),

    [LYR_SYM] = LAYOUT_split_3x5_3(
         _______,  _______,    KC_LCBR,  KC_RCBR,  _______,            _______,  _______,  KC_DQT,    KC_GRV,   KC_PIPE,
         KC_HASH,  KC_DOLLAR,  KC_LPRN,  KC_RPRN,  KC_EQL,             KC_TILD,  KC_UNDS,  KC_MINUS,  KC_ASTR,  KC_AMPR,
         KC_PERC,  KC_CIRC,    KC_LBRC,  KC_RBRC,  KC_PLUS,            KC_AT,    KC_EXLM,  KC_GRV,    KC_QUOT,  KC_BSLS,
                               _______,  CW_TOGG,  _______,            _______,  _______,  _______
    ),

    [LYR_NAV] = LAYOUT_split_3x5_3(
         KC_WH_D,  _______,  KC_WH_U,  _______,     _______,               _______,     _______,     _______,  _______,  _______,
         _______,  _______,  _______,  KC_MS_BTN1,  KC_MS_BTN1,            KC_LEFT,     KC_DOWN,     KC_UP,    KC_RGHT,  _______,
         _______,  _______,  _______,  _______,     _______,               _______,     _______,     _______,  _______,  _______,
                             _______,  _______,     _______,               KC_MS_BTN1,  KC_MS_BTN2,  _______
    ),

    [LYR_NUM] = LAYOUT_split_3x5_3(
         _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,
         KC_0,     KC_1,     KC_2,     KC_3,     KC_4,               KC_5,     KC_6,     KC_7,     KC_8,     KC_9,
         _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,
                             _______,  _______,  _______,            _______,  _______,  _______
    )


};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef DILEMMA_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    dilemma_set_pointer_sniping_enabled(layer_state_cmp(state, DILEMMA_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // DILEMMA_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LYR_BSE] = {ENCODER_CCW_CW(KC_WH_D, KC_WH_U), ENCODER_CCW_CW(KC_WH_U, KC_WH_D)},
    [LYR_SYM] = {ENCODER_CCW_CW(KC_DOWN, KC_UP), ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
    [LYR_NAV] = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
    [LYR_NUM] = {ENCODER_CCW_CW(KC_WH_D, KC_WH_U), ENCODER_CCW_CW(KC_WH_D, KC_WH_U)},
};
#endif // ENCODER_MAP_ENABLE

// Override caps word to not shift - to _
// https://docs.qmk.fm/features/caps_word
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_MINS:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}
