#include "ModeA.h"

void mode_A() {
    
    lcd.clear();
    lcd.printString("Mode A",0,0);
    lcd.refresh();
    wait_ms(250);                                       // small delay to prevent previous press being detected again

    while (button_a.read() == 0) {
        
        lcd.clear();
        lcd.printString("Mode A",0,0);
        
        
        lcd.drawRect(0,24,60,6,FILL_TRANSPARENT);       // Drawing the empty rectangles for bar levels
        lcd.drawRect(0,40,60,6,FILL_TRANSPARENT);
        
        float pot0_val = pot_0.read();                   // returns a float in the range 0.0 to 1.0
        float pot1_val = pot_1.read();
        
        int width0 = int(pot0_val*60.0f);               // convert to an int in the range 0.0 to 60.0
        int width1 = int(pot1_val*60.0f);
        
        lcd.drawRect(1,24,width0,6,FILL_BLACK);         // draws a filled in rectangle with variabkle width relative to pot values
        lcd.drawRect(1,40,width1,6,FILL_BLACK);
        
        float fuel_gauge = int(pot0_val*100.0f);                // converts pot value into a value between 0 - 100
        float eng_temp = int(pot1_val*80.0f)+50.0f;             // converts pot value into a value between 50 - 130

        printf("Fuel gauge = %.2f %%\n",fuel_gauge);             // sends values to coolterm
        printf("Engine temperature = %.2f 'C\n",eng_temp);

        lcd.printString("Fuel gauge",0,2);                      // prints strings above bar graphs on lcd
        lcd.printString("Eng temp",0,4);
        
        lcd.drawRect(70,39,5,9,FILL_TRANSPARENT);               // drawing the thermometer image
        lcd.drawCircle(72,36,3,FILL_TRANSPARENT);
        lcd.drawRect(72,36,1,10,FILL_TRANSPARENT);       
        lcd.drawRect(71,39,1,1,FILL_WHITE);
        lcd.drawRect(73,39,1,1,FILL_WHITE);
        
        lcd.drawRect(68,19,10,11,FILL_BLACK);                   // drawing the petrol pump image
        lcd.drawRect(69,20,8,4,FILL_WHITE);
        lcd.drawRect(65,21,4,2,FILL_BLACK);
        lcd.drawRect(65,21,2,8,FILL_BLACK);
        
        
        //warning lights
        
        if (fuel_gauge < 20.0f) {
            led4.write(1);
        } 
        else if (fuel_gauge > 20.0f) {
            led4.write(0);
        }

        if (eng_temp > 110.0f) {
            led1.write(1);
        } 
        else if (eng_temp < 110.0f) {
            led1.write(0);
        }
        
        
                                                            // update the LCD
        lcd.refresh();
                                                            // small delay between readings
        wait(0.2);

    }

}