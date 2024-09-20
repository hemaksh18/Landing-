#ifndef GPIO_DEAKIN_H
#define GPIO_DEAKIN_H

#include <Arduino.h> // includes in built functions
#include <stdbool.h> 

// defining macro values for input and output
#define INPUT 0
#define OUTPUT 1
#define HIGH true
#define LOW false

// structure defined to store pointers towards methods
typedef struct {
    bool (*Config_GPIO)(char PortNum, char PinNum, char Mode); // Pointer to a method that configures pin 
    bool (*Write_GPIO)(char PortNum, char PinNum, bool State);// Pointer to a method that writes values to pin
    bool (*Read_GPIO)(char PortNum, char PinNum); // Pointer to method reads value from pin
} GPIO_DEAKIN;

// calling the methods from cpp file
bool Config_GPIO(char PortNum, char PinNum, char Mode); 
bool Write_GPIO(char PortNum, char PinNum, bool State);
bool Read_GPIO(char PortNum, char PinNum);

extern GPIO_DEAKIN gpio; // variable declaration that will be allocated memory

#endif 