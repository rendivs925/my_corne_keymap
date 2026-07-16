// Copyright 2026 rendivs925
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _NAV,
    _SYM,
    _ADJ,
};

enum custom_keycodes {
    PREV_DIAG = SAFE_RANGE,
    NEXT_DIAG,
    TMUX_COPY_MODE,
};

// Thumb philosophy: only Esc/Super is dual-role. Space, Enter, Quote, and alphas
// stay deterministic for fast terminal and editor use.
#define GUI_ESC LGUI_T(KC_ESC)
#define NAV     TL_LOWR
#define SYM     TL_UPPR

// i3 currently uses Mod1/Alt. Change this one line to G(kc) after migrating i3
// to Mod4/Super.
#define WM(kc) A(kc)

#define TAB_PREV   C(S(KC_TAB))
#define TAB_NEXT   C(KC_TAB)
#define TERM_CLEAR C(KC_L)
#define TERM_COPY  C(S(KC_C))
#define TERM_PASTE C(S(KC_V))
#define WORD_LEFT  A(KC_B)
#define WORD_RIGHT A(KC_F)

static void tap_clean_16(uint16_t keycode) {
    const uint8_t saved_mods = get_mods();
    const uint8_t saved_oneshot_mods = get_oneshot_mods();

    clear_mods();
    clear_oneshot_mods();
    tap_code16(keycode);
    set_mods(saved_mods);
    set_oneshot_mods(saved_oneshot_mods);
}

static void tap_diag_sequence(uint16_t bracket_keycode) {
    const uint8_t saved_mods = get_mods();
    const uint8_t saved_oneshot_mods = get_oneshot_mods();

    clear_mods();
    clear_oneshot_mods();
    tap_code16(bracket_keycode);
    tap_code(KC_D);
    set_mods(saved_mods);
    set_oneshot_mods(saved_oneshot_mods);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T,      KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_BSPC,
        KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G,      KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        KC_LALT, KC_Z, KC_X, KC_C, KC_V, KC_B,      KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                         KC_LCTL, NAV, KC_SPC,      KC_ENT, SYM, GUI_ESC
    ),

    // NAV: browser/i3 on top, modifiers and HJKL-shaped arrows on home row,
    // diagnostics/tmux/clipboard plus word and page movement on bottom row.
    [_NAV] = LAYOUT_split_3x6_3(
        TAB_PREV,  WM(KC_1), WM(KC_2), WM(KC_3), WM(KC_4), WM(KC_5),      WM(KC_6), WM(KC_7),    WM(KC_8),     WM(KC_9),  WM(KC_0), TAB_NEXT,
        KC_NO,    KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  TERM_CLEAR,    KC_HOME,  KC_LEFT,     KC_DOWN,      KC_UP,    KC_RGHT,  KC_END,
        TERM_CLEAR, PREV_DIAG, NEXT_DIAG, TMUX_COPY_MODE, TERM_COPY, TERM_PASTE,  KC_PGDN,  WORD_LEFT, WORD_RIGHT, KC_PGUP,  KC_BSPC, KC_DEL,
                                  KC_TRNS, KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS
    ),

    // SYM: Rust-oriented rolls: ::, ->, =>, <>, and adjacent (), [], {} pairs.
    [_SYM] = LAYOUT_split_3x6_3(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TILD,
        KC_PIPE, KC_COLN, KC_MINS, KC_EQL,  KC_LT,   KC_GT,      KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR,
        KC_AMPR, KC_UNDS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,     KC_PERC, KC_CIRC, KC_ASTR, KC_PLUS, KC_QUES, KC_BSLS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
    ),

    // ADJ is protected behind NAV + SYM. QK_BOOT is intentionally on a corner.
    [_ADJ] = LAYOUT_split_3x6_3(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  QK_BOOT,
        KC_NO,   CW_TOGG, QK_REP,  QK_AREP, KC_NO,   KC_NO,      KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_BRID, KC_BRIU, KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                  KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GUI_ESC:
            return true;
        default:
            return false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case PREV_DIAG:
            tap_diag_sequence(KC_LBRC);
            return false;

        case NEXT_DIAG:
            tap_diag_sequence(KC_RBRC);
            return false;

        case TMUX_COPY_MODE:
            // tmux prefix is Ctrl-S; shell flow control must be disabled with stty -ixon.
            tap_clean_16(C(KC_S));
            wait_ms(10);
            tap_clean_16(KC_LBRC);
            return false;
    }

    return true;
}

#ifdef OLED_ENABLE
static const char *layer_name(void) {
    switch (get_highest_layer(layer_state)) {
        case _NAV:
            return "NAV";
        case _SYM:
            return "SYM";
        case _ADJ:
            return "ADJ";
        default:
            return "BASE";
    }
}

static void oled_write_mods(uint8_t mods) {
    oled_write_P(PSTR("Mods: "), false);
    oled_write_char((mods & MOD_MASK_GUI) ? 'G' : '-', false);
    oled_write_char((mods & MOD_MASK_ALT) ? 'A' : '-', false);
    oled_write_char((mods & MOD_MASK_CTRL) ? 'C' : '-', false);
    oled_write_char((mods & MOD_MASK_SHIFT) ? 'S' : '-', false);
    oled_write_ln_P(PSTR(""), false);
}

bool oled_task_user(void) {
    static layer_state_t last_layer_state = 0;
    static uint8_t       last_mods = 0;
    static bool          last_caps_word = false;
    static bool          last_master = false;
    static bool          initialized = false;

    const layer_state_t current_layer_state = layer_state;
    const uint8_t       current_mods = get_mods() | get_oneshot_mods();
    const bool          current_caps_word = is_caps_word_on();
    const bool          current_master = is_keyboard_master();

    if (initialized && current_layer_state == last_layer_state && current_mods == last_mods && current_caps_word == last_caps_word && current_master == last_master) {
        return false;
    }

    initialized = true;
    last_layer_state = current_layer_state;
    last_mods = current_mods;
    last_caps_word = current_caps_word;
    last_master = current_master;

    oled_clear();
    oled_write_P(PSTR("Corne "), false);
    oled_write_ln_P(current_master ? PSTR("PRI") : PSTR("SEC"), false);
    oled_write_P(PSTR("Layer: "), false);
    oled_write_ln(layer_name(), false);
    oled_write_P(PSTR("Caps: "), false);
    oled_write_ln_P(current_caps_word ? PSTR("ON") : PSTR("off"), false);
    oled_write_mods(current_mods);

    return false;
}
#endif
