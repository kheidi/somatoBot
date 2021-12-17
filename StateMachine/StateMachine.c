/************************************************************************************
Copyright 2021 - K. Heidi Fehr & Stephanie B. Hernández
  Project : State Machine for the robot's different simulations
  File    : StateMachine.c
  Author  : K. Heidi Fehr & Stephanie B. Hernández
  Company : University of Wisconsin - Madison
            1513 Univ. Ave. Madison WI 53706
Revision history    Date         Name                      Reason
        -------    --------     ------                     -------------------------------
          1.00     12/07/21     K. Fehr & S. Hernández     Development

State machine used to control the robot's simulations based on the button pressed.
************************************************************************************/

#include "StateMachine.h" 
#include "../LCD/lcdFunctions.h"
#include <delay.h>

 extern volatile long int motorACount;
 extern volatile long int motorBCount;
 extern float theta1_counts, theta2_counts; 

int S0, S1, S1, S2, S3, S4, S5, BP1, BP2, BP3, BP4, Normal, Noise, ReadyToStart, EStop, Surprise,test, ActionCompleted, Restart;
int S0 = 1; 
int counter;
void StateMachine (){
	
float x0, y0, r, w, t;
int theta1_counts, theta2_counts;

struct theta mytheta;

if ((PINC & Button1Pressed) == 0b0000001) {
    BP1 = 1;    
} else{
    BP1 = 0;
}

if ((PINC & Button2Pressed) == 0b0000010) {
    BP2 = 1;    
} else{
    BP2 = 0;
}

if ((PINC & Button3Pressed) == 0b00000100) {
    BP3 = 1;    
} else{
    BP3 = 0;
}

if ((Buttons & Button4Pressed) == 0b00001000) {
    BP4 = 1;    
} else{
    BP4 = 0;

}

// State 0: Waiting to start 
// State 1: Button 1 Pressed -> normal mode
// State 2: Button 2 Pressed -> Noise mode
// Sate 3: Button 3 & 1 pressed -> MERRY CHRISTMAS!
// State 4: Button 4 pressed -> E-stop -> yellow buttom
// State 5: Button 3 pressed -> Restart - move arm initial position

S0 = (S0 || (S5&&BP3)) &&!S1 &&!S2;
S1 = (S1 || (S0&&BP1) &&!BP4) &&!S3;
S2 = (S2 || (S0&&BP2) &&!BP4) &&!S3;
S3 = (S3 || (S1&&BP4) || (S2&&BP4)) &&! S0;
S5 = (S5 || (S2&&ActionCompleted) || (S1&&ActionCompleted)) &&!S0;


ReadyToStart = (S0)&&!S1&&!S2&&!S3&&!S4;
Normal = (S1)&&!S0&&!S2&&!S3&&!S4&!ActionCompleted;
Noise = (S2)&&!S0&&!S1&&!S3&&!S4&!ActionCompleted;
EStop = (S3)&&!S0&&!S1&&!S2&&!S4;
Restart = (S5)&&!S0 &&!S1 &&!S2 &&!S3 &&!S4;

if (ReadyToStart)
{
  //  E_Stop ();
	setLCDColor(CHARTREUSE);
	printStringLCD("Ready...");
	
}

if (Normal)
{
    setLCDColor(PINK);
	printStringLCD("Normal Mode");
	ActionCompleted = 1;

} 

if (Noise)
{ 
	setLCDColor(BLUE);
	printStringLCD("Noise Added");
	ActionCompleted = 1;
	
}

if (EStop)
{
	setLCDColor(RED);
	printStringLCD("E-Stop Pressed!");
	counter++;
	ActionCompleted = 0;
	if (counter>50)
	{
		counter = 0;
		S3 = 0;
	}
	
}

if(Restart) 
{
	setLCDColor(PURPLE);
	printStringLCD("Move arm to           initial pos-PB3");
}

}
