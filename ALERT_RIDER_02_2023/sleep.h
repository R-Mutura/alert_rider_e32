#include "STM32LowPower.h"

//BUTTONS--USED HERE AND IN THE MAIN.C
#define BUTTONPIN1 PA4
#define BUTTONPIN2 PA3
#define BUTTONPIN3 PA2
#define BUTTONPIN4 PA1
//END

int receiveFlag = 0; //used to check is the AUX pin is active showing there is incoming data from the Lora Module
int pwr_btn = PA0;
#define clr_btn PB1

void wakeupFromSleep();

void init_low_power()
{
    pinMode(pwr_btn, INPUT_PULLUP);
    pinMode (clr_btn, OUTPUT); //setting this pin to low => sending a clear signal as the line is pulled high
    digitalWrite(clr_btn, HIGH);//SET THIS PPIN TO HIGH IMPEDANCE---DO NOT CLEAR
    LowPower.begin();
   
}

void PCBshutdown()
{
  //send a clr(clear) signal to the btn monitor chip
   digitalWrite(clr_btn, HIGH); // CUT POWER COMPLETELY FROM ALL OF THE BOARD
   //LowPower.sleep();
}
//check line 546 on main code sheet for more sleep and wakeup functionality
