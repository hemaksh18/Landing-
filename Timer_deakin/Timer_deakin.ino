#include "GPIO_DEAKIN.h"
#include "TIMER_DEAKIN.h"


TIMER_DEAKIN timer; //instance of the TIMER_DEAKIN class

void setup() {
    gpio.Config_GPIO('A', 7, OUTPUT);
    timer.config_timer(0, 9999, 100.0); // start count = 0, end count = 9999 resolutions 100 for delay of 1 ms
}

void loop() {

    gpio.Write_GPIO('A', 7, HIGH);
    timer.wait(1000.0); // delay of 1 second

    gpio.Write_GPIO('A', 7, LOW);

    timer.wait(1000.0);
}
