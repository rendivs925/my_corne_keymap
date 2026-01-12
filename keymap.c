#include QMK_KEYBOARD_H

// ─────────────────────────────────────────────
// Layers
// ─────────────────────────────────────────────
enum layers {
    _BASE,
    _LOWER,
    _UPPER,
};

// ─────────────────────────────────────────────
// Custom Keycodes
// ─────────────────────────────────────────────
enum custom_keycodes {
    VIM_WRITE = SAFE_RANGE, // :w
    VIM_QUIT,               // :q

    PREV_DIAG,              // [d
    NEXT_DIAG,              // ]d

    CTRL_TAB,
    CTRL_SHIFT_TAB,

    TERM_CLEAR,

    CTRL_ALT_A,
    CTRL_ALT_E,
    CTRL_ALT_W,
    CTRL_ALT_B,
    CTRL_ALT_F,
    CTRL_ALT_P,
    CTRL_ALT_N,
    CTRL_ALT_K,
    CTRL_ALT_Y,
    CTRL_ALT_R,
    CTRL_ALT_L,
    CTRL_ALT_T,

    CTRL_SHIFT_C,
    CTRL_SHIFT_V,

    TMUX_COPY_MODE,         // Ctrl+S then [
};

// ─────────────────────────────────────────────
// Mod / Layer Taps
// ─────────────────────────────────────────────
#define ESC_GUI   MT(MOD_LGUI, KC_ESC)
#define SFT_QUOT  MT(MOD_RSFT, KC_QUOT)
#define ENT_ALT   MT(MOD_LALT, KC_ENT)
#define SPC_ALT   MT(MOD_LALT, KC_SPC)
#define BSP_UPP   LT(_UPPER, KC_BSPC)

#define LWR MO(_LOWER)
#define UPP MO(_UPPER)

// ─────────────────────────────────────────────
// Process Record
// ─────────────────────────────────────────────
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;

    switch (keycode) {

        // ── Vim ──────────────────────────────
        case VIM_WRITE:
            SEND_STRING(SS_TAP(X_ESC) ":w\n");
            return false;

        case VIM_QUIT:
            SEND_STRING(SS_TAP(X_ESC) ":q\n");
            return false;

        // ── Diagnostics ──────────────────────
        case PREV_DIAG:
            SEND_STRING("[d");
            return false;

        case NEXT_DIAG:
            SEND_STRING("]d");
            return false;

        // ── Tabs ─────────────────────────────
        case CTRL_TAB:
            tap_code16(C(KC_TAB));
            return false;

        case CTRL_SHIFT_TAB:
            tap_code16(C(S(KC_TAB)));
            return false;

        // ── Terminal ─────────────────────────
        case TERM_CLEAR:
            SEND_STRING("clear\n");
            return false;

        // ── Ctrl+Alt (CLI / Readline) ─────────
        case CTRL_ALT_A: tap_code16(C(A(KC_A))); return false;
        case CTRL_ALT_E: tap_code16(C(A(KC_E))); return false;
        case CTRL_ALT_W: tap_code16(C(A(KC_W))); return false;
        case CTRL_ALT_B: tap_code16(C(A(KC_B))); return false;
        case CTRL_ALT_F: tap_code16(C(A(KC_F))); return false;
        case CTRL_ALT_P: tap_code16(C(A(KC_P))); return false;
        case CTRL_ALT_N: tap_code16(C(A(KC_N))); return false;
        case CTRL_ALT_K: tap_code16(C(A(KC_K))); return false;
        case CTRL_ALT_Y: tap_code16(C(A(KC_Y))); return false;
        case CTRL_ALT_R: tap_code16(C(A(KC_R))); return false;
        case CTRL_ALT_L: tap_code16(C(A(KC_L))); return false;
        case CTRL_ALT_T: tap_code16(C(A(KC_T))); return false;

        // ── Clipboard ────────────────────────
        case CTRL_SHIFT_C:
            tap_code16(C(S(KC_C)));
            return false;

        case CTRL_SHIFT_V:
            tap_code16(C(S(KC_V)));
            return false;

        // ── tmux: Ctrl+S then [ ──────────────
        case TMUX_COPY_MODE:
            tap_code16(C(KC_S));   // prefix
            wait_ms(10);           // important
            tap_code(KC_LBRC);     // [
            return false;
    }

    return true;
}

// ─────────────────────────────────────────────
// Keymaps
// ─────────────────────────────────────────────
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // ───────────── BASE ─────────────
    [_BASE] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T,      KC_Y, KC_U, KC_I, KC_O, KC_P, ESC_GUI,
        KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G,      KC_H, KC_J, KC_K, KC_L, KC_SCLN, SFT_QUOT,
        KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B,      KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RCTL,
                         LWR, UPP, ENT_ALT,
                         SPC_ALT, BSP_UPP, LWR
    ),

    // ───────────── LOWER ─────────────
    [_LOWER] = LAYOUT_split_3x6_3(
        KC_TAB, KC_1, KC_2, KC_3, KC_4, KC_5,       KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR,
        KC_LSFT, KC_6, KC_7, KC_8, KC_9, KC_0,      KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC,
        KC_LCTL, KC_TILD, KC_ASTR, KC_PLUS, KC_MINS, KC_EQL,
                 KC_AMPR, KC_BSLS, KC_COLN, KC_SCLN, KC_PIPE, KC_RCTL,
                         LWR, UPP, ENT_ALT,
                         SPC_ALT, BSP_UPP, LWR
    ),

    // ───────────── UPPER ─────────────
    [_UPPER] = LAYOUT_split_3x6_3(
        CTRL_TAB, LALT(KC_1), LALT(KC_2), LALT(KC_3), LALT(KC_4), LALT(KC_5),
                   PREV_DIAG, NEXT_DIAG, CTRL_ALT_B, CTRL_ALT_F, CTRL_ALT_T, TERM_CLEAR,

        CTRL_SHIFT_TAB, LALT(KC_6), LALT(KC_7), LALT(KC_8), LALT(KC_9), LALT(KC_0),
                         KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, VIM_WRITE, VIM_QUIT,

        CTRL_ALT_A, CTRL_ALT_E, CTRL_ALT_W, CTRL_SHIFT_C, CTRL_SHIFT_V, TMUX_COPY_MODE,
        CTRL_ALT_P, CTRL_ALT_N, CTRL_ALT_K, CTRL_ALT_Y, CTRL_ALT_R, CTRL_ALT_L,

                         LWR, UPP, ENT_ALT,
                         SPC_ALT, BSP_UPP, KC_NO
    ),
};
