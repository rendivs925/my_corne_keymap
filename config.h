// Copyright 2026 rendivs925
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define TAPPING_TERM 180
#define QUICK_TAP_TERM 120

#define PERMISSIVE_HOLD_PER_KEY

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 4000

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_SLEEP
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100
#    define RGB_MATRIX_LED_FLUSH_LIMIT 16
#endif
