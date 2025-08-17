#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>
#include <sys/types.h>

//#define LED_PIN 10
#define LED_PIN 10 //Input pin for the shift registers, IMPORTANT: in case of liatris controller you have to change the pin and hardwire it there
                   // I used pin 21
#define SRCLK 1 //Shift register clock, used when shifting bits in 
#define RCLK 0 //Clock, used when using parallel output of registers

//#define SRCLR //Used to clear shift registers, but because of the wiring it turns on all leds.
                //Pulled high using a resistor, can be used, but not necessary

#define SIZE 30 //Number of leds

void setup(); //Called before using leds, to initialize the gpio pins
void clear(); //Turns off all leds
void send(uint8_t *leds, size_t size); //Lights up leds based on the indices provided using <leds>
void test(); //Test whether all leds are working

#endif