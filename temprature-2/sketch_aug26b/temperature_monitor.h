#ifndef TEMPERATURE_MONITOR_H
#define TEMPERATURE_MONITOR_H

#include <Arduino.h>

// LED pins
#define LED1_PIN 2
#define LED2_PIN 3
#define LED3_PIN 4

// thermistor pin
#define THERMISTOR_PIN A0

class Temperature_LED {
public:
    Temperature_LED();
    // functions for setting up and updating the state of sensors and LEDs
    void begin();
    void update();

    float readTemp();
    void blinkLEDs(float temperature);

    //functions accessing timers called 
    unsigned long previousMillis;
    unsigned long blinkMillisLED2;
    unsigned long blinkMillisLED3;
    unsigned long allLEDsBlinkMillis;

    //functions accessing states of LEDs called 
    bool led1State;
    bool led2State;
    bool led3State;
    bool led1Blinking;
    bool allLEDsBlinking;
    unsigned long led1BlinkStart;
    unsigned long led1BlinkPeriod;
};

#endif 
