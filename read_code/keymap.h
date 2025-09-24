#ifndef KEYMAP_H
#define KEYMAP_H

#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
- S T P H *     * F P L T D
- S K W R *     * R B G S Z
      # A O     E U #
*/

struct Key {
      uint8_t col;
      uint8_t row;
} typedef Key;

struct Keymap {
     const Key keys[30];
} typedef Keymap;


int key_to_led(uint8_t key, bool final);
void setup_keys();
bool wait_for(uint8_t *keys, uint8_t len);

#endif