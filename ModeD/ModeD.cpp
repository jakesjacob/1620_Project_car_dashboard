#include "ModeD.h"

void mode_D()
{

    lcd.clear();
    lcd.printString("Mode D",0,0);
    lcd.refresh();
    wait_ms(250);
    int gear = 0.0f;
    float gearR = 0.0f;
    shift.write(0x00);
    

    while (button_d.read() == 0) {

        lcd.clear();
        lcd.printString("Mode D",0,0);
        red_led.write(1);



        while (button_a.read() == 1) {                  //acting as the clutch button
            red_led.write(0);
            float pot0_val = pot_0.read();
            

            if (pot0_val > 0.8f) {                      //if joystick is flicked up, goes up a gear
                gear = gear + 1.0f;
                break;
            }
            if (pot0_val < 0.2f) {                      //if joystick is flicked down, goes down a gear
                gear = gear - 1.0f;
                break;
                }
            wait_ms(250);
        }
        
        

        if (gear > 5.0f) {                                      //keeps it between gear 5 and -1
            gear = 5.0f;
        }
        if (gear < -1.0f) {
            gear = -1.0f;
        }




        printf("gear = %d %\n",gear);                           //sends to coolterm
        
        
        
        if (gear == 1.0f) {                                 //setting the 7 segment display and also the gear ratio
            shift.write(0x06);
            gearR = 3.85f;
            }
            else if (gear == 2.0f) {
                shift.write(0x5B);
                gearR = 2.04f;
                }
                else if (gear == 3.0f) {
                    shift.write(0x4F);
                    gearR = 1.28f;
                    }
                    else if (gear == 4.0f) {
                        shift.write(0x66);
                        gearR = 0.95f;
                        }
                        else if (gear == 5.0f) {
                            shift.write(0x6D);
                            gearR = 0.76f;
                            }
                            else if (gear == 0.0f) {
                                shift.write(0x3F);
                                gearR = 1.00f;
                                }
                                else if (gear == -1.0f) {
                                    shift.write(0x80);
                                    gearR = 3.62f;
                                    }
                                    
        






        float pot1_val = pot_1.read();                   // returns a float in the range 0.0 to 1.0
        int rpm = (pot1_val*5300.0f)+700.0f;          // convert to an int in the range 700.0 to 6000.0
        int width1 = int(pot1_val*60.0f);                   // convert to an int in the range 0.0 to 60.0
        
        int rph = (rpm*60.0f);
        

        float speed = (0.001174392f*rph)/(gearR*4.07f);     //calculating the speed=(wheel circumference(miles)*rph)/(gear ratio * drive ration)
        if (gear == 0.0f) {
            speed = 0.0f;
            }
        float width2 = (speed/2.2784f);                     //fitting the values into 60 for the bar graph

        lcd.drawRect(1,24,60,6,FILL_TRANSPARENT);       // Drawing the empty rectangles for bar levels
        lcd.drawRect(1,40,60,6,FILL_TRANSPARENT);

        lcd.drawRect(1,24,width1,6,FILL_BLACK);         // draws a filled in rectangle with variable width relative to pot values
        lcd.drawRect(1,40,width2,6,FILL_BLACK);

        printf("RPM = %d %\n",rpm);                   // sends values to coolterm
        printf("Speed = %.1f mph\n",speed);

        //lcd.printString("RPM",0,2);                      // prints strings above bar graphs on lcd
        //lcd.printString("Speed",0,4);
        
        char buffer[14];                                    // max screen witdth is 14                                                    // print message to buffer
        sprintf(buffer,"RPM=%d",rpm);                                                  // print to screen (x pixel, line number)
        lcd.printString(buffer,0,2);
        lcd.refresh();
        
        sprintf(buffer,"Speed=%.1fmph",speed);
        lcd.printString(buffer,0,4);

        lcd.refresh();
        wait(0.2);



    }

}