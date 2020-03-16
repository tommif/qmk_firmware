#pragma once
/* This is based on SpacebarRacecars work https://github.com/qmk/qmk_firmware/tree/master/users/spacebarracecar */

#include "quantum.h"
#include "keymap_finnish.h"

enum custom_keycodes {
  LSFT = SAFE_RANGE,     // LSFT | (
  RSFT,                  // LSFT | )
  COMM,                  // , | <
  DOT,                   // . | >
  SLSH,                  // / | ?
  SCLN,                  // ; | :
  QUOT,                  // ' | "
  BSLS,                  // \ | |

  NUM2,                  // 2 | @
  NUM4,                  // 4 | $
  NUM6,                  // 6 | ^
  NUM7,                  // 7 | &
  NUM8,                  // 8 | *
  NUM9,                  // 9 | (
  NUM0,                  // 0 | )
  EQAL,                  // = | +

  NEW_SAFE_RANGE         // Use for keymap specific keycodes
};

extern bool lshift;
extern uint8_t prev_indx;
extern uint16_t prev_kcs[6];
void add_to_prev(uint16_t kc);
void unreg_prev(void);

void timer_timeout(void);
void timer_timeout_keymap(void);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

// cut copy paste and undo
#define ctrz LCTL(KC_Z)
#define ctrx LCTL(KC_X)
#define ctrc LCTL(KC_C)
#define ctrv LCTL(KC_V)

/* Templates for Keys, with custom shifted and non shifted Characters */

// Normal shift status
#define SHIFT_NORM(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  if (lshift) { \
    register_code(KC_LSFT); \
    unregister_code(kc2); \
    register_code(kc2); \
    add_to_prev(kc2); \
  } else { \
    unregister_code(KC_LSFT); \
    unregister_code(kc1); \
    register_code(kc1); \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
} \
return false;

// Always shifted
#define SHIFT_ALL(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  register_code(KC_LSFT); \
  if (lshift) { \
    unregister_code(kc2); \
    register_code(kc2); \
    add_to_prev(kc2); \
  } else { \
    unregister_code(kc1); \
    register_code(kc1); \
    add_to_prev(kc1); \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
  unreg_prev(); \
  if (lshift) \
    register_code(KC_LSFT); \
  else \
    unregister_code(KC_LSFT); \
} \
return false;

// Never shifted
#define SHIFT_NO(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  unregister_code(KC_LSFT); \
  if (lshift) { \
    unregister_code(kc2); \
    register_code(kc2); \
    add_to_prev(kc2); \
  } else { \
    unregister_code(kc1); \
    register_code(kc1); \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
  unreg_prev(); \
  if (lshift) \
    register_code(KC_LSFT); \
  else \
    unregister_code(KC_LSFT); \
} \
return false;

// Always AltGr
#define SHIFT_ALWAYS_ALGR(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  unregister_code(KC_LSFT); \
  register_code(KC_ALGR); \
  if (lshift) { \
    unregister_code(kc2); \
    register_code(kc2); \
    unregister_code(kc2); \
    register_code(KC_LSFT); \
  } else { \
    unregister_code(kc1); \
    register_code(kc1); \
    unregister_code(kc1); \
  } \
  unregister_code(KC_ALGR); \
} \
return false;

// Inverted shift status
#define SHIFT_SWITCH(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  if (lshift) { \
    unregister_code(KC_LSFT); \
    unregister_code(kc2); \
    register_code(kc2); \
    add_to_prev(kc2); \
  } else { \
    register_code(KC_LSFT); \
    unregister_code(kc1); \
    register_code(kc1); \
    add_to_prev(kc1); \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
  unreg_prev(); \
  if (lshift) \
    register_code(KC_LSFT); \
  else \
    unregister_code(KC_LSFT); \
} \
return false;

// AltGr on shift
#define SHIFT_ALGR(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  unregister_code(KC_LSFT); \
  if (lshift) { \
    register_code(KC_ALGR); \
    unregister_code(kc2); \
    register_code(kc2); \
    unregister_code(kc2); \
    register_code(KC_LSFT); \
    unregister_code(KC_ALGR); \
  } else { \
    unregister_code(kc1); \
    register_code(kc1); \
    unregister_code(kc1); \
  } \
} \
return false;
