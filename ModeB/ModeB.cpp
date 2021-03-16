#include "ModeB.h"

void mode_B()
{

    lcd.clear();
    lcd.printString("Mode B",0,0);
    lcd.refresh();
    wait_ms(250);

    while (button_b.read() == 0) {

        lcd.clear();
        lcd.printString("Mode B",0,0);

        float pot0_val = pot_0.read();                            // returns a float in the range 0.0 to 1.0

        int heater = 0.0f;


        //LEDs for heater control

        if (pot0_val > 0.8f && pot0_val <= 1.0f) {                      //4 leds on
            led1.write(1);
            led2.write(1);
            led3.write(1);
            led4.write(1);
            heater = 4.0f;
        }

        else if (pot0_val > 0.6f && pot0_val < 0.8f) {                   //3 leds on
            led1.write(1);
            led2.write(1);
            led3.write(1);
            led4.write(0);
            heater = 3.0f;
        }

        else if (pot0_val > 0.4f && pot0_val < 0.6f) {                   //2 leds on
            led1.write(1);
            led2.write(1);
            led3.write(0);
            led4.write(0);
            heater = 2.0f;
        }

        else if (pot0_val > 0.2f && pot0_val < 0.4f) {                   //1 leds on
            led1.write(1);
            led2.write(0);
            led3.write(0);
            led4.write(0);
            heater = 1.0f;
        }

        else if (pot0_val > 0.0f && pot0_val < 0.2f) {                   //no led
            led1.write(0);
            led2.write(0);
            led3.write(0);
            led4.write(0);
            heater = 0.0f;
        }

        printf("Heater blower level = %d %\n",heater);                  // sends values to coolterm

        //ldr headlights
        float ldr_value = ldr.read();

        if (ldr_value > 0.6f) {
            red_led.write(0);
            blue_led.write(0);
            green_led.write(0);
        } else if (ldr_value < 0.6f) {
            red_led.write(1);
            blue_led.write(1);
            green_led.write(1);
        }
        
        //temperture
        float voltage = 3.3f * tmp36.read();                // read in the ADC value and convert to voltage
        
        float temperature = 100.0f*voltage - 50.0f;         // T = 100V - 50
                                                            // convert voltage to temperature
        
                                                            // we need an array of chars to store the message
        char buffer[14];                                    // max screen witdth is 14
                                                            // print message to buffer
        sprintf(buffer,"Temp=%.2f C",temperature);
                                                            // print to screen (x pixel, line number)
        lcd.printString(buffer,0,3);
                                                            // update the LCD
        lcd.refresh(); 
        printf("Cabin Temp = %.1f C\n",temperature);
                                                            // small delay between readings
        wait(0.2);



    }

}