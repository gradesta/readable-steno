#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"
#include "typey-type-full.h"
#include "led_driver.h"
#include "keymap.h"
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 64
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
}

int search(char *word) {

    for (int i = 0; i < steno_dict.size; i++) {
        if (strcmp(word, steno_dict.steno_entries[i].output) == 0) {
            compute(steno_dict.steno_entries[i].chord);
            break;
        }
    }
}

int main(void) {
    tusb_init();
    setup();

    char line_buf[BUF_SIZE];
    uint8_t line_pos = 0;

    while (1) {
        tud_task(); // TinyUSB device task

        if (tud_cdc_connected() && tud_cdc_available()) {
            char ch;
            while (tud_cdc_available() && line_pos < BUF_SIZE - 1) {
                tud_cdc_read(&ch, 1);

                // Check for newline (Enter key)
                if (ch == '\r' || ch == '\n') {
                    line_buf[line_pos] = '\0';      // terminate string
                    line_pos = 0;
                    search(line_buf);                    // reset buffer
                    tud_cdc_write("\r\n", 2);
                    tud_cdc_write_flush();
                } else {
                    line_buf[line_pos++] = ch;        // store character
                    tud_cdc_write(line_buf + line_pos - 1, 1);
                    tud_cdc_write_flush();
                }
            }
        }
    }
}

// TinyUSB callbacks
void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool rts) {
    (void) itf; (void) rts;
    if (dtr) {
        tud_cdc_write_str("USB CDC Connected!\r\n");
        tud_cdc_write_flush();
    }
}

void tud_cdc_rx_cb(uint8_t itf) {
    (void) itf;
}
