#include "pico/stdlib.h"
#include "typey-type-full.h"
#include "led_driver.h"
#include "keymap.h"
#include <stdio.h>
#include <string.h>

#define WORD "guidelines"
#define MAX_CHORD_LENGTH 10

void compute(const uint8_t *chords) {
    uint8_t leds[MAX_CHORD_LENGTH];
    int leds_i = 0;
    bool final = false;
    memset(leds, -1, sizeof(leds));
    while (*chords != '\0') {
        const uint8_t *vowels = "AOEU";
        if (*chords == '*' || strchr(vowels, *chords)) final = true;
            
        leds[leds_i++] = key_to_led(*chords, final);
        chords++;
    }

    send(leds, leds_i);

    while (true) { }
}

int main() {

    stdio_init_all();
    setup();

    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }

    while (true) {
        for (int i = 0; i < steno_dict.size; i++) {
            if (strcmp(WORD, steno_dict.steno_entries[i].output) == 0) {
                printf("Nasiel som\n");
                compute(steno_dict.steno_entries[i].chord);
            }
        }
    }
}