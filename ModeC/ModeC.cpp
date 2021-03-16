#include "ModeC.h"
#include "mbed.h"
#include "Tone.h"

Tone dac(p18);


void mode_C()
{

    lcd.clear();
    lcd.printString("Mode C",0,0);
    lcd.refresh();
    wait_ms(250);  // small delay to prevent previous press being detected again
    dac.init();

    while (button_c.read() == 0) {

        lcd.clear();
        lcd.printString("Mode C",0,0);

        lcd.drawRect(0,24,60,6,FILL_TRANSPARENT);       // Drawing the empty rectangles for bar levels

        float pot0_val = pot_0.read();                   // returns a float in the range 0.0 to 1.0

        int width0 = int(pot0_val*60.0f);               // convert to an int in the range 0.0 to 60.0

        lcd.drawRect(1,24,width0,6,FILL_BLACK);         // draws a filled in rectangle with variabkle width relative to pot values

        float distance = int(pot0_val*200.0f);                // converts pot value into a value between 0 - 200

        printf("Distance (cm) = %.2f %\n",distance);             // sends values to coolterm

        lcd.printString("Distance",0,2);                      // prints strings above bar graphs on lcd



        int sprite_dist[8][12] = {
            { 0,0,0,0,0,0,0,0,0,0,1,1 },
            { 0,0,0,0,1,1,0,0,0,0,1,1 },
            { 1,1,1,1,1,1,1,0,0,0,1,1 },
            { 1,1,1,1,1,1,1,1,0,0,1,1 },
            { 1,1,1,1,1,1,1,1,0,0,1,1 },
            { 1,1,1,1,1,1,1,0,0,0,1,1 },
            { 0,0,0,0,1,1,0,0,0,0,1,1 },
            { 0,0,0,0,0,0,0,0,0,0,1,1 },
        };

        lcd.drawSprite(68,23,8,12,(int *)sprite_dist);

        //warning lights

        if (distance < 20.0f) {
            red_led.write(0);
        } else if (distance > 20.0f) {
            red_led.write(1);
        }
        
        
        
        dac.play(1000.f,0.1f);
        wait(pot0_val*0.5f);








        // update the LCD
        lcd.refresh();
        // small delay between readings
        //wait(0.2);





    }

}