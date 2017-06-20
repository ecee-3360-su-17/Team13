/*

 * main.c

 */

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"


#define RED_LED   GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3



extern int fib(int n);
void blink(int n);
uint8_t convert_to_morse(int n);



int main(void) {

    int pw = 1;
    int tmp = 0;
    int digit = 0;
    int val = 0;
    //call fib
    //int n;
    //while(1){
   //for(n = 0; n < 10 ; n++){

    val = fib(4);

    tmp = val;
    //figure out num of digits in results
    while(tmp != 0){

        tmp /= 10; //tmp = tmp/10

        pw = pw * 10;

    }

    //segment of digits and call blink
    while(pw > 1){

        pw = pw / 10;

        digit = val / pw;

        val = val % pw; //val modular pw

        blink(digit);
        //}//end of for loop
                    }//end of while(pw > 1)
   // }//End of while(1)

    return 0;

}





//This function takes in a number "n" and blinks it

void blink(int n){



    uint8_t pattern = convert_to_morse(n);

    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ| SYSCTL_OSC_MAIN);


        // Enable and configure the GPIO port for the LED operation.

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

        GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED);



    int i;

    uint8_t state;

    for(i = 0; i < 5; i++){

        state = (pattern << i) & 0b10000;

        //Set LED state

        if (state == 0b10000){


            //Turn ON RED LED for LONG
            GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, RED_LED);

                  // Delay for a bit

                  SysCtlDelay(3000000);
                  //Clear Register by writing 0x0 to it
                  GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, 0x0);

        }

        else{//If not '1' then '0'
            //Turn BLUE LED ON for SHORT
            GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, BLUE_LED);

                  // Delay for a bit
                  SysCtlDelay(3000000);
                  //Clear LED Register
                  GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, 0x0);

        }

        //Wait between lights
        SysCtlDelay(2000000);

    }//end of for-loop

    //Turn ON GREEN LED for END notification for number segment
    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, GREEN_LED);

    //Long wait between numbers
    SysCtlDelay(4000000);

    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, 0x0);

}



//convert to morse code

//Takes in a number "n" and converts to morse code binary

//"1" is long = BLUE
//"0" is short = RED
//SPACE = GREEN



uint8_t convert_to_morse(int n){

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

        break;

    }

}
