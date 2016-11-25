#include <Arduino.h>


void blinksetup(){
        pinMode(LED_PIN, OUTPUT);
        now = millis();
        
    
}

void blinkloop(){
    
    
    if (millis() > (now + 1000)){
        now = millis();
        digitalWrite(LED_PIN, !(digitalRead(LED_PIN)));
    }
    
    
    
    
}