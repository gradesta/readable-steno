#ifndef KEYMAP_H
#define KEYMAP_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
/*
- S T P H *     * F P L T D
- S K W R *     * R B G S Z
      # A O     E U #
*/

int key_to_led(uint8_t key, bool final);

#endif