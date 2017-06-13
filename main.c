/*
 * main.c
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

extern int fib(int n);

int main(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
        {
        }
	//call fibb

    //figure out num of digits in results
    //segment of digits and call blink
	return 0;
}

//This function takes in a number "n" and blinks it
void blink(int n){


    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);

    char pattern = convert_to_morse(n);
    int i = 0;
    for(i = 0; i < 5; i++){
        int state = (pattern << i) & 0b10000;
        //Set LED state
        if (state == 0b10000){

        }
        else{

        }
        //Wait between lights
    }
    //Long wait between numbers
}

//convert to morse code
//Takes in a number "n" and converts to morse code binary
//"1" is long "0" is short

char convert_to_morse(int n){
    switch(n){
    case 0:
        return 0b11111;
        break;
    case 1:
        return 0b01111;
        break;
    case 2:
        return 0b00111;
        break;
    case 3:
        return 0b00011;
        break;
    case 4:
        return 0b00001;
        break;
    case 5:
        return 0b00000;
        break;
    case 6:
        return 0b10000;
        break;
    case 7:
        return 0b11000;
        break;
    case 8:
        return 0b11100;
        break;
    case 9:
        return 0b11110;
        break;

    default:

    }
}
