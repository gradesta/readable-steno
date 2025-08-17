//---------------------------------------------------------------------------

#pragma once
#include "main_flash_layout.h"

//---------------------------------------------------------------------------

#define JAVELIN_USE_EMBEDDED_STENO 1
#define JAVELIN_USE_USER_DICTIONARY 1
#define JAVELIN_USB_MILLIAMPS 100
#define BOOTSEL_BUTTON_INDEX 29

#define JAVELIN_DEBOUNCE_MS 10
#define JAVELIN_BUTTON_MATRIX 1

constexpr uint8_t COLUMN_PINS[] = {7, 6, 5, 4, 3, 2, 29, 28, 27, 26, 22, 20};
constexpr uint8_t ROW_PINS[] = {12, 13, 14};

// clang-format off
constexpr int8_t KEY_MAP[3][12] = {
  { 0,  1,  2,  3,  4,  5, /**/  6,  7,  8,  9,  10, 11 },
  { 12, 13, 14, 15, 16, 17, /**/ 18, 19, 20, 21, 22, 23 },
  { -1, -1, -1, 24, 25, 26, /**/ 27, 28, 29, -1, -1, -1 },
};
// clang-format on

#define JAVELIN_SCRIPT_CONFIGURATION                                           \
  R"({"name":"Uni v4","layout":[{"x":0,"y":0},{"x":1,"y":0},{"x":2,"y":0},{"x":3,"y":0},{"x":4,"y":0},{"x":5,"y":0},{"x":6,"y":0},{"x":7,"y":0},{"x":8,"y":0},{"x":9,"y":0},{"x":10,"y":0},{"x":11,"y":0},{"x":0,"y":1},{"x":1,"y":1},{"x":2,"y":1},{"x":3,"y":1},{"x":4,"y":1},{"x":5,"y":1},{"x":6,"y":1},{"x":7,"y":1},{"x":8,"y":1},{"x":9,"y":1},{"x":10,"y":1},{"x":11,"y":1},{"x":3,"y":2},{"x":4,"y":2},{"x":5,"y":2},{"x":6,"y":2},{"x":7,"y":2},{"x":8,"y":2}]})"

const size_t BUTTON_COUNT = 30;

const char *const MANUFACTURER_NAME = "-";
const char *const PRODUCT_NAME = "-";
const int VENDOR_ID = 0x0000;

//---------------------------------------------------------------------------
