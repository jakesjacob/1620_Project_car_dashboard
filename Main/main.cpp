#include "main.h"

// objects defined here with pin numbers (if required)
DigitalIn button_a(p29);
DigitalIn button_b(p28);
DigitalIn button_c(p27);
DigitalIn button_d(p26);

N5110 lcd(p8,p9,p10,p11,p13,p21);
BusOut leds(LED4,LED3,LED2,LED1);

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

AnalogIn ldr(p15);

PwmOut red_led(p24);
PwmOut green_led(p23);
PwmOut blue_led(p22);

AnalogIn tmp36(p16);

AnalogIn pot_0(p20);
AnalogIn pot_1(p19);
AnalogIn pot_2(p17);

Tone speaker(p18);
ShiftReg shift;

int main()
{
    init();  // initialise peripherals
    welcome();  // display welcome message

    while(1) {  // infinite loop

        print_menu();  // this re-prints the menu at the start of every loop

        // if any buttons pressed then jump to appropriate menu function
        if (button_a.read() == 1) {
            mode_A();
        }
        if (button_b.read() == 1) {
            mode_B();
        }
        if (button_c.read() == 1) {
            mode_C();
        }
        if (button_d.read() == 1) {
            mode_D();
        }

        // delay to prevent multiple button presses being detected
        wait_ms(250);
        
        red_led.write(1);
        blue_led.write(1);
        green_led.write(1);
        
        led1.write(0);
        led2.write(0);
        led3.write(0);
        led4.write(0);
        
        shift.write(0x00);

    }
}

void init()
{
    // turn off LEDs
    red_led = 1.0;
    green_led = 1.0;
    blue_led = 1.0;
    
    led1.write(0);
    led2.write(0);
    led3.write(0);
    led4.write(0);
    
    
    // turn off 7-seg display
    shift.write(0x00);

    // initialise LCD
    lcd.init();

    // PCB has external pull-down resistors so turn the internal ones off
    button_a.mode(PullNone);
    button_b.mode(PullNone);
    button_c.mode(PullNone);
    button_d.mode(PullNone);
}

void print_menu()
{
    lcd.clear();
    lcd.printString("Press button",0,0);
    lcd.printString("to select",0,1);
    lcd.printString("A: Mode A",0,2);
    lcd.printString("B: Mode B",0,3);
    lcd.printString("C: Mode C",0,4);
    lcd.printString("D: Mode D",0,5);
    lcd.refresh();
}

void welcome()
{
    lcd.clear();
    lcd.printString("  Automotive",0,0);
    lcd.printString("  Electronics",0,1);
    lcd.printString("   Simulator",0,2);
    lcd.printString("Craig A. Evans",0,4);
    lcd.printString("  0123456789",0,5);
    lcd.refresh();
    wait(1.0);
}