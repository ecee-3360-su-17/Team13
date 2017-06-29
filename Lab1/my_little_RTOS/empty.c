/*============================*/
/*           empty.c          */
/*============================*/


#include <stdint.h>
#include "inc/tm4c1294ncpdt.h"
/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Mailbox.h>

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>

/* Board Header file */
#include "Board.h"

/* Other Headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EK_TM4C1294XL.h"

#define Board_LED_ON                EK_TM4C1294XL_LED_ON
#define Board_LED_OFF               EK_TM4C1294XL_LED_OFF
#define Board_LED0                  EK_TM4C1294XL_D1
#define Board_LED1                  EK_TM4C1294XL_D2
#define Board_LED2                  EK_TM4C1294XL_D2
//#define GPIO_PF0_EN0LED0            0x00050005


//#define Board_LED3                  EK_TM4C1294XL_USR_D3
//#define Board_LED4                  EK_TM4C1294XL_USR_D4


// GPIOPinConfigure(GPIO_PF0_EN0LED0);  /* EK_TM4C1294XL_USR_D3 */
//GPIOPinConfigure(GPIO_PF4_EN0LED1);  /* EK_TM4C1294XL_USR_D4 */


/* Definitions */
#define TASKSTACKSIZE 768
#define NUMMSGS 3

/* Declare Task structs */
Task_Struct senderFxnStruct;        // Sender function
Char senderFxnStack[TASKSTACKSIZE];
Task_Struct recieverFxnStruct;      // Reciever function
Char recieverFxnStack[TASKSTACKSIZE];

Void senderFxn(UArg arg0, UArg arg1);
Void recieverFxn(UArg arg0, UArg arg1);


/* Message struct defintion */
typedef struct MsgObj {
    int val;            // Message value
} MsgObj, *Msg;



/*======== main ========*/

int main(void)
{
    Task_Params senderFxnParams;
    Task_Params recieverFxnParams;

    /* Call board init functions */
    Board_initGeneral();
    Board_initGPIO();
    Board_initUART();


    Mailbox_Struct mbxStruct;
    Mailbox_Params mbxParams;
    Mailbox_Params_init(&mbxParams);
    Mailbox_construct(&mbxStruct,sizeof(MsgObj), 2, &mbxParams, NULL);

    Mailbox_Handle mbxHandle = Mailbox_handle(&mbxStruct);


    Task_Params_init(&senderFxnParams);
    senderFxnParams.arg0 = (UArg)mbxHandle;
    senderFxnParams.stackSize = TASKSTACKSIZE;
    senderFxnParams.stack = &senderFxnStack;
    Task_construct(&senderFxnStruct, (Task_FuncPtr)senderFxn, &senderFxnParams, NULL);
    //RTOS will schedual and configure our tasks

    Task_Params_init(&recieverFxnParams);
    recieverFxnParams.arg0 = (UArg)mbxHandle;
    recieverFxnParams.stackSize = TASKSTACKSIZE;
    recieverFxnParams.stack = &recieverFxnStack;
    Task_construct(&recieverFxnStruct, (Task_FuncPtr)recieverFxn, &recieverFxnParams, NULL);
    //RTOS will schedual and configure our tasks

    System_printf("Starting the example\nSystem provider is set to SysMin. "
                  "Halt the target to view any SysMin contents in ROV.\n");
    /* SysMin will only print to the console when you call flush or exit */
    System_flush();

    /* Start BIOS */
    BIOS_start();

    return (0);
}

Void senderFxn(UArg arg0, UArg arg1)
{
    /* Messages */
    const char flickMsg[] = "\fFlicker enabled\r\n";
    const char DoneMsg[] = "\fLED D1 is toggled\r\n";
    const char DtwoMsg[] = "\fLED D2 is toggled\r\n";
    const char onMsg[] = "\fLEDs are on\r\n";
    const char offMsg[] = "\fLEDs are off\r\n";
    const char message[] = "\fEnter a command: \r\n";

    char input;
    UART_Handle uart;
    UART_Params uartParams;

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 9600;
    uart = UART_open(Board_UART0, &uartParams);

    if (uart == NULL) {
       System_abort("Error opening the UART");
    }

    UART_write(uart, message, sizeof(message));

    Mailbox_Handle mbxHandle = (Mailbox_Handle)arg0;

    char *buffer = (char*)malloc(5);
    int cnt = 0;

    while(1){    // While the input character is not empty...

        UART_read(uart, &input, 1);      // Read character from UART.
        UART_write(uart, &input, 1);
        if(input == '\r'){
            if(!strcmp("flick",buffer)){
                UART_write(uart, flickMsg, sizeof(DoneMsg));
                MsgObj msg;
                msg.val = 0;
                Mailbox_post(mbxHandle, &msg, BIOS_WAIT_FOREVER);
            }
            if(!strcmp("d1",buffer)){
                UART_write(uart, DoneMsg, sizeof(DoneMsg));
                MsgObj msg;
                msg.val = 1;
                Mailbox_post(mbxHandle, &msg, BIOS_WAIT_FOREVER);
            }
            if(!strcmp("d2",buffer)){
                UART_write(uart, DtwoMsg, sizeof(DtwoMsg));
                MsgObj msg;
                msg.val = 2;
                Mailbox_post(mbxHandle, &msg, BIOS_WAIT_FOREVER);
            }
            if(!strcmp("on",buffer)){
                UART_write(uart, onMsg, sizeof(onMsg));
                MsgObj msg;
                msg.val = 4;
                Mailbox_post(mbxHandle, &msg, BIOS_WAIT_FOREVER);
            }
            if(!strcmp("off",buffer)){
                UART_write(uart, offMsg, sizeof(offMsg));
                MsgObj msg;
                msg.val = 3;
                Mailbox_post(mbxHandle, &msg, BIOS_WAIT_FOREVER);
            }

            /* Reset buffer */
            cnt = 0;

            int x;
            for(x = 0; x < 5; x++){
                buffer[x] = 0;
            }

        }
        else if((cnt < 5)){
            buffer[cnt] = input;            // Copy into out buffer.
            cnt++;                          // Increment count.
        }
    }

}

Void recieverFxn(UArg arg0, UArg arg1)
{

    Mailbox_Handle mbxHandle = (Mailbox_Handle)arg0;
    while(1){
        MsgObj msg;
        Mailbox_pend(mbxHandle, &msg, BIOS_WAIT_FOREVER);
        if(msg.val == 0){
            //flicker LED
            altLED();
        }
        if(msg.val == 1) GPIO_toggle(Board_LED0);
        if(msg.val == 2) GPIO_toggle(Board_LED1);
        if(msg.val == 3){
            GPIO_write(Board_LED0,0x0);
            GPIO_write(Board_LED1,0x0);
        }
        if(msg.val == 4){
            GPIO_write(Board_LED0,1);
            GPIO_write(Board_LED1,1);

        }

    }

}

void altLED(){
    volatile uint32_t ui32Loop;

                    // Loop forever.
                    int i;
                    for(i = 0; i<10; i++)
                    {

                        GPIO_write(Board_LED0,1);
                        GPIO_write(Board_LED1,1);

                        //
                        // Delay for a bit.
                        //
                        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
                        {
                        }

                        //
                        // Turn off the LED.
                        GPIO_write(Board_LED0,0);
                        GPIO_write(Board_LED1,0);

                        //
                        // Delay for a bit.
                        //
                        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
                        {
                        }
                    }
}

