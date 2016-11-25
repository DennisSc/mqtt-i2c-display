#include <Arduino.h>

void hardwaresetup(){
        Serial.begin(115200);
        delay(19);
        Serial.println("Hello Cloud9!");

		Wire.pins(0, 2);
		lcd.begin(); // initialize the lcd

					 // Print a message to the LCD.
		lcd.backlight();
        
}

void hardwareloop(){}