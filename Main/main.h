#ifndef MAIN_H
#define MAIN_H

// include the different header files
#include "mbed.h"
#include "N5110.h"
#include "ShiftReg.h"
#include "Tone.h"
#include "ModeA.h"
#include "ModeB.h"
#include "ModeC.h"
#include "ModeD.h"

// extern tells the compiler that these objects are defined in a different file (main.cpp).
// It stops them being defined multiple times when other files include main.h.
// Here we only declare them. They are defined (with pin numbers etc.) in main.cpp
extern DigitalIn button_a;
extern DigitalIn button_b;
extern DigitalIn button_c;
extern DigitalIn button_d;

extern DigitalOut led1;
extern DigitalOut led2;
extern DigitalOut led3;
extern DigitalOut led4;

extern N5110 lcd;
extern BusOut leds;

extern AnalogIn ldr;

extern PwmOut red_led;
extern PwmOut green_led;
extern PwmOut blue_led;

extern AnalogIn tmp36;

extern AnalogIn pot_0;
extern AnalogIn pot_1;
extern AnalogIn pot_2;

extern Tone speaker;
extern ShiftReg shift;

// function prototypes
void init();
void print_menu();
void welcome();

#endif