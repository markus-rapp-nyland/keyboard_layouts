#include QMK_KEYBOARD_H

enum layer_number {
  _COLEMAK = 0,
  _NAVI,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* COLEMAK (actually colemak-dh)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  = / +  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Y  |   Ø  |  - | &  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | BcSp |   A  |   R  |   S  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|   `   |    |   \   |------+------+------+------+------+------|
 * |   [  |   Z  |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   H  |   ,  |   .  |   / - _  |  ]   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI | LCTL | /LShift /       \ NAVI \  | RGUI |  RCTL  | RAlt / |
 *                   |      |      |      |/[Space]/         \[Entr]\ |      |        | AltGR  |
 *                   `----------------------------'           '------''--------------------'
 */

[_COLEMAK] = LAYOUT(
   KC_ESC, KC_1, KC_2,    KC_3,    KC_4,       KC_5,                                    KC_6,      KC_7,            KC_8,    KC_9,    KC_0,    KC_EQL,
   KC_TAB, KC_Q, KC_W,    KC_F,    KC_P,       KC_B,                                    KC_J,      KC_L,            KC_U,    KC_Y,    KC_SCLN, KC_MINS,
  KC_BSPC, KC_A, KC_R,    KC_S,    KC_T,       KC_G,                                    KC_M,      KC_N,            KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LBRC, KC_Z, KC_X,    KC_C,    KC_D,       KC_V,         KC_GRV,          KC_BSLS,  KC_K,      KC_H,            KC_COMM, KC_DOT, KC_SLSH, KC_RBRC,
                       KC_LALT, KC_LGUI,    KC_LCTL, LSFT_T(KC_SPC), LT(_NAVI,KC_ENT), KC_RALT, KC_RGUI, KC_RCTL
),
/* NAVI
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  |  F10 | PrScr|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      | PgUp |      | F11  |                    |  F12 |      |  Up  |      | |<<  | Break|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Del  |      | Home | PgDn | End  |      |-------.    ,-------|      | Left | Down | Rght |  ||  |WinBrk|
 * |------+------+------+------+------+------| MAIN  |    | LOCK  |------+------+------+------+------+------|
 * | Ins  |      |      |LC+Ins|      |LS+Ins|-------|    |-------|      |      |      |      |  >>| |      |
 * `-----------------------------------------/ LShift/     \      \-----------------------------------------'
 *                   | LCtl | LAlt |  Meh | /[Space]/       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_NAVI] = LAYOUT(
    _______,   KC_F1,   KC_F2,   KC_F3,        KC_F4,        KC_F5,                           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PSCR,
    _______, _______, _______, KC_PGUP,      _______,       KC_F11,                           KC_F12,  _______, KC_UP,   _______, KC_MPRV, KC_PAUS,
     KC_DEL, _______, KC_HOME, KC_PGDN,       KC_END,      _______,                           _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_MPLY, RGUI(KC_PAUS),
     KC_INS, _______, _______, LCTL(KC_INS), _______, LSFT(KC_INS), DF(_COLEMAK),  DF(_NAVI), _______, _______, _______, _______, KC_MNXT, _______,
                                    KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS,       _______,   _______, _______, _______
)
};

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
