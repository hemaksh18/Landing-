#include "GPIO_DEAKIN.h"

#define PORT_PIN_MASK(pin) (1 << (pin))

// function to configure a gpio pin on the board
bool Config_GPIO(char PortNum, char PinNum, char Mode) {
    //configuration for port A
    if (PortNum == 'A') {
        if (Mode == OUTPUT) {
            PORT->Group[0].DIRSET.reg = PORT_PIN_MASK(PinNum); // setting the corresponding bit in direction register for pin mode to be output
        } else {
            PORT->Group[0].DIRCLR.reg = PORT_PIN_MASK(PinNum); // clearing the bit in the direction register 
        }
        // configuration for port B
    } else if (PortNum == 'B') {
        if (Mode == OUTPUT) {
            PORT->Group[1].DIRSET.reg = PORT_PIN_MASK(PinNum);
        } else {
            PORT->Group[1].DIRCLR.reg = PORT_PIN_MASK(PinNum);
        }
    } else {
      return false; // for invalid port connection
    }
    return true;
}

//function to set the state of a gpio pin on the board
bool Write_GPIO(char PortNum, char PinNum, bool State) {
    if (PortNum == 'A') {
        if (State == HIGH) {
            PORT->Group[0].OUTSET.reg = PORT_PIN_MASK(PinNum); // the state of the pin is set high by setting the bit in the output set register
        } else {
            PORT->Group[0].OUTCLR.reg = PORT_PIN_MASK(PinNum); //the state of the pin is set low by setting the bit in the output clear register
        }
    } else if (PortNum == 'B') {
        if (State == HIGH) {
            PORT->Group[1].OUTSET.reg = PORT_PIN_MASK(PinNum);
        } else {
            PORT->Group[1].OUTCLR.reg = PORT_PIN_MASK(PinNum);
        }
    } else {
        return false;
    }
    return true;
}

bool Read_GPIO(char PortNum, char PinNum) {
    if (PortNum == 'A') {
        return (PORT->Group[0].IN.reg & PORT_PIN_MASK(PinNum)) != 0; //the current state of pin by checking the bit in input register
    } else if (PortNum == 'B') {
        return (PORT->Group[1].IN.reg & PORT_PIN_MASK(PinNum)) != 0;// state of pin checked for port b
    }
    return false;
}

// the gpio variable creates instance that intitalises pointers to their methods/fucntions
GPIO_DEAKIN gpio = { 
    .Config_GPIO = Config_GPIO,
    .Write_GPIO = Write_GPIO,
    .Read_GPIO = Read_GPIO
};