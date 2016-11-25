#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

									//define your default values here, if there are different values in config.json, they are overwritten.
char mqtt_server[40];
char mqtt_port[6] = "1883";
char mqtt_topic[60];


long now;

#include "defaults.h"

#define LED_PIN 13



void setup() {
    hardwaresetup();
    blinksetup();
    wifisetup();
    otasetup();
	mqttsetup();
}

void loop() {
    hardwareloop();
    blinkloop();
    wifiloop();
    otaloop();
	mqttloop();
}