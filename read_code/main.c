#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"
#include "typey-type-full.h"
#include "led_driver.h"
#include "keymap.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 64
#define MAX_CHORD_LENGTH 10

void compute(const uint8_t *chords) {
    uint8_t leds[MAX_CHORD_LENGTH];
    while (true) {
        int leds_i = 0;
        bool final = false;
        memset(leds, -1, sizeof(leds));
        while (*chords != '\0' && *chords != '/') {
            const uint8_t *vowels = "AOEU";
            if (*chords == '*' || strchr(vowels, *chords)) final = true;
            int led_num = key_to_led(*chords, final);    
            leds[leds_i++] = led_num;
            chords++;
        }

        send(leds, leds_i);

        if (*chords == '\0') return;
        chords++;
        sleep_ms(1000);
    }
    
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
    int initial = 97; //bytes to be skipped

    while (1) {
        tud_task(); // TinyUSB device task

        if (tud_cdc_connected() && tud_cdc_available()) {
            uint8_t ch;
            while (tud_cdc_available()) {
                
                uint8_t ch[64];
                uint8_t num;
                // show raw numeric value of the received byte
                // if ((num = tud_cdc_read(ch, 64)) > 0) {
                //     char hello[64];
                //     int len = snprintf(hello, 64, "%d", num);
                //     int out = 0;
                //     char out_buff[64 * 4];
                //     for (int i = 0; i < num; i++) {
                //         out += snprintf(out_buff + out, 64 - out, "%d ", ch[i]);
                //     }
                //     tud_cdc_write(hello, len);
                //     tud_cdc_write_char('-');
                //     tud_cdc_write(out_buff, out);
                //     tud_cdc_write("\r\n", 2);
                //     tud_cdc_write_flush();
                    
                // }
                if ((num = tud_cdc_read(ch, 64)) > 0) {
                    if (initial > 0) {
                        initial -= num;
                        continue;
                    }
                    tud_cdc_write(ch, num);
                } else {
                    tud_cdc_write_str("\r\n");
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
        // tud_cdc_write_str("USB CDC Connected!\r\n");
        // tud_cdc_write_flush();
    }
}

void tud_cdc_rx_cb(uint8_t itf) {
    (void) itf;
}
