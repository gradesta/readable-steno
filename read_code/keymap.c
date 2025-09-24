#include "keymap.h"

const Keymap keymap = {
      .keys = {
            {7, 12},
            {7, 13},
            {6, 12},
            {6, 13},
            {5, 12},
            {5, 13},
            {4, 12},
            {4, 13},
            {4, 14},
            {3, 12},
            {3, 13},
            {3, 14},
            {2, 12},
            {2, 13},
            {2, 14},
            {29, 12},
            {29, 13},
            {29, 14},
            {28, 12},
            {28, 13},
            {28, 14},
            {27, 12},
            {27, 13},
            {27, 14},
            {26, 12},
            {26, 13},
            {22, 12},
            {22, 13},
            {20, 12},
            {20, 13}
      }
};

int key_to_led(uint8_t key, bool final) {
    const uint8_t *vowels = "AOEU";

    if (key == '*') return 12;

    if (strchr(vowels, key) != NULL) {
        switch (key) {
            case 'A': return 11;
            case 'O': return 14;
            case 'E': return 17;
            case 'U': return 20;
        }
    }

    if (final) {
        switch (key) {
            case 'F': return 18;
            case 'R': return 19;
            case 'P': return 21;
            case 'B': return 22;
            case 'L': return 24;
            case 'G': return 25;
            case 'T': return 26;
            case 'S': return 27;
            case 'D': return 28;
            case 'Z': return 29;
        }
    } else {
        switch (key) {
            case 'S': return 2;
            case 'T': return 4;
            case 'K': return 5;
            case 'P': return 6;
            case 'W': return 7;
            case 'H': return 9;
            case 'R': return 10;
        }
    }

    return -1;
}

void setup_keys() {
    const uint8_t cols[12] = {7, 6, 5, 4, 3, 2, 29, 28, 27, 26, 22, 20};
    const uint8_t rows[3] = {12, 13, 14};

    for (int i = 0; i < 12; i++) {
        gpio_init(cols[i]);
        gpio_set_dir(cols[i], GPIO_IN);
        gpio_pull_up(cols[i]);
    }

    for (int i = 0; i < 3; i++) {
        gpio_init(rows[i]);
        gpio_set_dir(rows[i], GPIO_OUT);
        gpio_put(rows[i], false);
    }
}

bool wait_for(uint8_t *keys, uint8_t len) {

    for (int i = 0; i < 30; i++) {
        bool in_keys = false;

        for (int j = 0; j < len; j++) {
            if (i == keys[j]) {
                in_keys = true;
                break;
            }
        }
        
        if ((in_keys && gpio_get(keymap.keys[i].col) != 0)) {
            return false;
        }
    }  

    return true;
}