#include QMK_KEYBOARD_H
#include <stdio.h>
#include "crkbd.h"

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _SYMBOLS 1
#define _NAV 2
#define _META 3

/*
typedef enum {
    SINGLE_TAP,
    SINGLE_HOLD,
} td_state_t;

static td_state_t td_state;

int cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) {
            return SINGLE_TAP;
        } else {
            return SINGLE_HOLD;
        }
    } else {
        return 2;
    }
};

enum tab_dance_codes { CTRLSHIFT, CTRLALT, CTRLGUI };

void tap_ctrl_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state        = cur_dance(state);
    uint8_t mod_bit = MOD_BIT(state->keycode == TD(CTRLSHIFT) ? KC_LSHIFT : state->keycode == TD(CTRLALT) ? KC_RALT : KC_LGUI);
    switch (td_state) {
        case SINGLE_TAP:
            set_oneshot_mods(MOD_BIT(KC_LCTRL) | mod_bit);
            break;
        case SINGLE_HOLD:
            register_mods(mod_bit);
            break;
    }
};

void tap_ctrl_reset(qk_tap_dance_state_t *state, void *user_data) {
    uint8_t mod_bit = MOD_BIT(state->keycode == TD(CTRLSHIFT) ? KC_LSHIFT : state->keycode == TD(CTRLALT) ? KC_RALT : KC_LGUI);
    switch (td_state) {
        case SINGLE_TAP:
            // clear_oneshot_mods();
            break;
        case SINGLE_HOLD:
            unregister_mods(mod_bit);
            break;
    }
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [CTRLSHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_ctrl_finished, tap_ctrl_reset),
    [CTRLALT]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_ctrl_finished, tap_ctrl_reset),
    [CTRLGUI]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_ctrl_finished, tap_ctrl_reset),
};
*/

enum custom_keycodes { QWERTY = SAFE_RANGE, SYMBOLS, NAV, META };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(
        KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
        KC_LALT, KC_LSHIFT, KC_SPC, MO(_SYMBOLS), MO(_NAV), KC_LGUI
    ),
    [_SYMBOLS] = LAYOUT_split_3x6_3(
        KC_ESC, KC_PLUS, KC_MINS, KC_EXLM, KC_UNDS, KC_LCBR, KC_RCBR, KC_7, KC_8, KC_9, KC_HASH, KC_BSPC,
        KC_AT, KC_ASTR, KC_SLSH, KC_CIRC, KC_EQL, KC_LPRN, KC_RPRN, KC_4, KC_5, KC_6, KC_TILD, KC_DLR,
        KC_LCTL, KC_PERC, KC_AMPR, KC_PIPE, KC_GRV, KC_LBRC, KC_RBRC, KC_1, KC_2, KC_3, KC_0, KC_BSLS,
        KC_LALT, KC_LSHIFT, KC_SPC, KC_TRNS, MO(_META), KC_LGUI
    ),
    [_NAV] = LAYOUT_split_3x6_3(
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_NO, KC_PSCR,
        KC_NO, KC_F5, KC_F6, KC_F7, KC_F8, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_SLCK,
        KC_LCTL, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_DEL, KC_INS, KC_NO, KC_NO, KC_NO, KC_PAUS,
        KC_LALT, KC_LSHIFT, KC_SPC, MO(_META), KC_TRNS, KC_LGUI
    ),
    [_META] = LAYOUT_split_3x6_3(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RESET, EEP_RST, KC_NO, KC_NO, KC_NO, KC_NO,
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO
    )
};
// clang-format on

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
#endif
// SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
    iota_gfx_init(!has_usb());  // turns on the display
#endif
}

// SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

const char *read_layer_state(void) {
    switch (layer_state) {
        case 0:
            return "Layer: Default";
        case 1 << _SYMBOLS:
            return "Layer: Symbols";
        case 1 << _NAV:
            return "Layer: Nav";
        case 1 << _META | 1 << _NAV:
        case 1 << _META | 1 << _SYMBOLS:
            return "Layer: Meta";
    }
    return "Layer: Unknown";
}

const char *read_logo(void) {
    // clang-format off
    static char logo[] = {
      0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
      0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
      0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
      0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x80, 0x80, 0x80, 0x80, 0x80,
      0};
    // clang-format on

    return logo;
}

void matrix_scan_user(void) { iota_gfx_task(); }

void matrix_render_user(struct CharacterMatrix *matrix) {
    if (is_master) {
        // If you want to change the display of OLED, you need to change here
        matrix_write_ln(matrix, read_layer_state());
        // matrix_write_ln(matrix, read_keylog());
        // matrix_write_ln(matrix, read_keylogs());
        // matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
        // matrix_write_ln(matrix, read_host_led_state());
        // matrix_write_ln(matrix, read_timelog());
    } else {
        /*
        for (uint8_t x = 0; x < dwarf_height; x++) {
            for (uint8_t y = 0; y < dwarf_width; y++) {
                const size_t offset = (dwarf_height - x - 1) * dwarf_width + y;
                const size_t byte   = offset / 8;
                const size_t bit    = offset % 8;
                oled_write_pixel(x, y, (dwarf[byte] & (1 << (7 - bit))) != 0);
            }
        }
        once = true;
        */
        matrix_write(matrix, read_logo());
    }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
    if (memcmp(dest->display, source->display, sizeof(dest->display))) {
        memcpy(dest->display, source->display, sizeof(dest->display));
        dest->dirty = true;
    }
}

void iota_gfx_task_user(void) {
    struct CharacterMatrix matrix;
    matrix_clear(&matrix);
    matrix_render_user(&matrix);
    matrix_update(&display, &matrix);
}
#endif  // SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef SSD1306OLED
        // set_keylog(keycode, record);
#endif
        // set_timelog();
    }

    return true;
}
