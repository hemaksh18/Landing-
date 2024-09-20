#include "temperature_monitor.h"

// To configure the software timers 
Temperature_LED::Temperature_LED()
    : previousMillis(0), blinkMillisLED2(0), blinkMillisLED3(0),
      led1State(false), led2State(false), led3State(false),
      led1BlinkStart(0), led1BlinkPeriod(1000), led1Blinking(false),
      allLEDsBlinkMillis(0), allLEDsBlinking(false) {}

void Temperature_LED::begin() {
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(LED3_PIN, OUTPUT);

    // set Serial communication
    Serial.begin(9600);
}

// updating the state of LED as per the timers
void Temperature_LED::update() {
    unsigned long currentMillis = millis();

    // Sampling temp every 5 seconds
    if (currentMillis - previousMillis >= 5000) {
        previousMillis = currentMillis;

        float temperature = readTemp(); // reading the temperature from NTC thermistor 

        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" C");

        blinkLEDs(temperature);
    }

    // LED state when temperature is < 20
    if (allLEDsBlinking) {
        if (currentMillis - allLEDsBlinkMillis >= 2000) { // 2-second period
            allLEDsBlinkMillis = currentMillis;
            led1State = !led1State;
            led2State = led1State;
            led3State = led1State;
            digitalWrite(LED1_PIN, led1State);
            digitalWrite(LED2_PIN, led2State);
            digitalWrite(LED3_PIN, led3State);
        }
    }

    // If the condition for led1 blinking is satisfied
    if (led1Blinking) {
        if (currentMillis - led1BlinkStart >= led1BlinkPeriod) {
            led1BlinkStart = currentMillis;
            led1State = !led1State;
            digitalWrite(LED1_PIN, led1State);
        }
    }

    // If the condition for led2 blinking is satisfied
    if (led2State && (currentMillis - blinkMillisLED2 >= 1000)) { // 1-second period
        blinkMillisLED2 = currentMillis;
        digitalWrite(LED2_PIN, !digitalRead(LED2_PIN));
    }

    // If the condition for led3 blinking is satisfied
    if (led3State && (currentMillis - blinkMillisLED3 >= 500)) { // 0.5-second period
        blinkMillisLED3 = currentMillis;
        digitalWrite(LED3_PIN, !digitalRead(LED3_PIN));
    }
}

// calculates the temprature 
float Temperature_LED::readTemp() {
    int analogValue = analogRead(THERMISTOR_PIN);// reading analog value from thermistor 

    //analog value to temperature in Celsius
    float voltage = analogValue * (3.3 / 1023.0);
    float resistance = (10 * 3.3 / voltage) - 10;
    float temperature = 1 / (log(resistance / 10) / 3950 + 1 / (25 + 273.15)) - 273.15;

    return temperature;
}

//function that checks the conditions of LED blinking
void Temperature_LED::blinkLEDs(float temperature) {
    // Resetting LEDs
    led1Blinking = false;
    allLEDsBlinking = false;
    led2State = false;
    led3State = false;

    // between 20 and 25 degrees
    if (temperature >= 20 && temperature <= 25) {
        digitalWrite(LED1_PIN, HIGH); 
        digitalWrite(LED2_PIN, LOW);  
        digitalWrite(LED3_PIN, LOW);  

    // between 25 and 30 degrees
    } else if (temperature > 25 && temperature <= 30) {
        digitalWrite(LED1_PIN, LOW);  
        digitalWrite(LED2_PIN, LOW);  
        digitalWrite(LED3_PIN, LOW);  
        led2State = true;             

    // above 30 degrees
    } else if (temperature > 30) {
        digitalWrite(LED1_PIN, LOW);  
        digitalWrite(LED2_PIN, LOW);  
        digitalWrite(LED3_PIN, LOW);  
        led2State = true;             
        led3State = true;             

    // below 20 degrees 
    } else if (temperature < 20) {
        allLEDsBlinking = true; // All LED blink with interval of two seconds 
        allLEDsBlinkMillis = millis();
    }
}
