#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"
#include "dict.h"
#include "led_driver.h"
#include "keymap.h"
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 3000
#define MAX_CHORD_LENGTH 10

void compute(const uint8_t *chords) {
    uint8_t keys[MAX_CHORD_LENGTH];

    while (*chords != '\0') {
        int keys_i = 0;
        bool final = false;
        memset(keys, -1, sizeof(keys));

        while (*chords != '\0' && *chords != '/') {
            const uint8_t *vowels = "AOEU";
            if (*chords == '*' || strchr(vowels, *chords)) final = true;
            keys[keys_i++] = key_to_led(*chords, final);
            chords++;
        }

        send(keys, keys_i);

        if (*chords == '/') chords++;

        //Waiting for the correct keys to be pressed
        while (wait_for(keys, keys_i) == false)
        {
            tud_task();
        }

        sleep_ms(5);

        while (wait_for(keys, keys_i) == true)
        {
            tud_task();
        }
        
        sleep_ms(5);
    }

    clear();
}

void search(char *word) {
    for (int i = 0; i < steno_dict.size; i++) {
        if (strcmp(word, steno_dict.steno_entries[i].output) == 0) {
            compute(steno_dict.steno_entries[i].chord);
            return;
        }
    }
}

int main(void) {
    tusb_init();
    setup();
    setup_keys();

    char line_buf[BUF_SIZE];
    uint8_t ch;
    uint8_t line_pos = 0;

    while (1) {
        tud_task();

        if (tud_cdc_connected() && tud_cdc_available()) {
            while (tud_cdc_available() && line_pos < BUF_SIZE) {
                if (tud_cdc_read(&ch, 1) > 0) {

                    if (ch == 0x08 || ch == 0x7F) {
                        line_pos--;
                        line_buf[line_pos] = '\0';
                        tud_cdc_write_str("\b \b");
                        tud_cdc_write_flush();
                        continue;
                    }

                    tud_cdc_write(&ch, 1);
                    tud_cdc_write_flush();

                    line_buf[line_pos++] = ch;

                    if (ch == '\n' || ch == '\r') {
                        tud_cdc_write(&ch, 1);
                        tud_cdc_write_flush();
                        
                        char *w_start = line_buf;
                        for (int i = 0; i < line_pos; i++) {
                            tud_cdc_write(&line_buf[i], 1);
                            tud_cdc_write_str("\r\n");
                            tud_cdc_write_flush();
                            if (line_buf[i] <= 32) {
                                line_buf[i] = '\0';
                                search(w_start);
                                w_start = line_buf + i + 1;
                            }
                        }

                        memset(line_buf, 0, BUF_SIZE);
                        line_pos = 0;
                    }
                }
            }
        }
    }
}
 
void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool rts) {
    (void) itf; (void) rts;
    if (dtr) {
    }
}

void tud_cdc_rx_cb(uint8_t itf) {
    (void) itf;
}
