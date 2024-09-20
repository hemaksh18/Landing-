// temperature_monitor.ino

#include "temperature_monitor.h"

// Create an instance of Temperature_LED
Temperature_LED tempLED;

void setup() {
    tempLED.begin();
}

void loop() {
    tempLED.update();
}
