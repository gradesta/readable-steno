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

// Flag to signal abort from main loop
static volatile bool abort_compute = false;

void compute(const uint8_t *chords) {
    uint8_t keys[MAX_CHORD_LENGTH];

    while (*chords != '\0' && !abort_compute) {
        int keys_i = 0;
        bool final = false;
        memset(keys, 0xFF, sizeof(keys));

        while (*chords != '\0' && *chords != '/') {
            const uint8_t *vowels = (const uint8_t *)"AOEU";
            if (*chords == '*' || strchr((const char *)vowels, *chords)) final = true;
            keys[keys_i++] = key_to_led(*chords, final);
            chords++;
        }

        send(keys, keys_i);

        if (*chords == '/') chords++;

        // Wait for correct keys - but keep USB alive
        while (wait_for(keys, keys_i) == false && !abort_compute) {
            tud_task();
            sleep_us(100);  // Small delay to prevent tight spinning
        }

        if (abort_compute) break;

        sleep_ms(5);

        // Wait for release
        while (wait_for(keys, keys_i) == true && !abort_compute) {
            tud_task();
            sleep_us(100);
        }
        
        if (abort_compute) break;
        
        sleep_ms(5);
    }

    abort_compute = false;
    clear();
}

void search(char *word) {
    for (int i = 0; i < steno_dict.size; i++) {
        if (strcmp(word, steno_dict.steno_entries[i].output) == 0) {
            compute(steno_dict.steno_entries[i].chord);
            return;
        }
    }
    test();
    clear();
}

int main(void) {
    tusb_init();
    setup();
    setup_keys();

    char line_buf[BUF_SIZE];
    uint16_t line_pos = 0;
    bool initialized = false;
    uint32_t last_char_time = 0;
    bool waiting_for_word = false;

    while (1) {
        tud_task();

        if (tud_cdc_connected()) {
            if (!initialized) {
                sleep_ms(1000);
                
                // Drain any stale data
                while (tud_cdc_available()) {
                    tud_cdc_read_char();
                    tud_task();
                }
                
                // Send first 'n' and blink to show we sent it
                char init = 'n';
                tud_cdc_write(&init, 1);
                tud_cdc_write_flush();
                test();
                initialized = true;
                waiting_for_word = true;
                line_pos = 0;
            }

            // Process available CDC data
            while (tud_cdc_available()) {
                char ch = tud_cdc_read_char();
                last_char_time = board_millis();
                
                // Word delimiter - process the buffered word
                if (ch == '\r' || ch == '\n') {
                    if (line_pos > 0) {
                        line_buf[line_pos] = '\0';
                        search(line_buf);

                        // Request next word
                        char next_word = 'n';
                        tud_cdc_write(&next_word, 1);
                        tud_cdc_write_flush();

                        line_pos = 0;
                        waiting_for_word = true;
                    }
                } 
                // Printable character - add to buffer
                else if (ch >= 32 && ch < 127) {
                    if (line_pos < BUF_SIZE - 1) {
                        line_buf[line_pos++] = ch;
                    }
                    waiting_for_word = false;
                }
                // Ignore other control characters
            }
            
        } else {
            initialized = false;
            line_pos = 0;
            waiting_for_word = false;
            abort_compute = true;
            clear();
        }
        
        sleep_us(100);
    }
}

void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool rts) {
    (void) itf; (void) rts;
    if (!dtr) {
        abort_compute = true;  // Abort if DTR drops
    }
}

void tud_cdc_rx_cb(uint8_t itf) {
    (void) itf;
}