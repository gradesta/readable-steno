#include "keymap.h"

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