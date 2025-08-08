#include "led_driver.h"
#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdio.h>

void setup() {
    //Init the pins
    gpio_init(LED_PIN);
    gpio_init(SRCLK);
    gpio_init(RCLK);
    //gpio_init(SRCLR);

    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_set_dir(SRCLK, GPIO_OUT);
    gpio_set_dir(RCLK, GPIO_OUT);
    //gpio_set_dir(SRCLR, GPIO_OUT);

    clear();
}

void clear() {
    gpio_put(LED_PIN, true);
    for (int i = 0; i < SIZE; i++) {
        gpio_put(SRCLK, true);
        sleep_ms(10);
        gpio_put(SRCLK, false);
        sleep_ms(10);
    }

    gpio_put(RCLK, true);
    sleep_ms(10);
    gpio_put(RCLK, false);
    sleep_ms(10);
}

int compare_ints(const void *a, const void *b) {
    uint8_t ua = *(const uint8_t *)a;
    uint8_t ub = *(const uint8_t *)b;

    if (ua < ub) return 1;  
    if (ua > ub) return -1;  
    return 0;   
}              

void send(uint8_t *leds, size_t size) {
    qsort(leds, size, sizeof(uint8_t), compare_ints); //Sorts into descending order
    clear();
    size_t led_i = 0;

    for (int board_led = 29; board_led >= 0; board_led--) {
        if (led_i < size && board_led == leds[led_i]) {
            gpio_put(LED_PIN, false);
            led_i += 1;
        } else {
            gpio_put(LED_PIN, true);
        }

        gpio_put(SRCLK, true);
        sleep_ms(10);
        gpio_put(SRCLK, false);
        sleep_ms(10);
    }

    gpio_put(RCLK, true);
    sleep_ms(10);
    gpio_put(RCLK, false);
    sleep_ms(10);
}