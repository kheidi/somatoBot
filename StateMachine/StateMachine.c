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
int S1, S1, S2, S3, S4, NormalMode, NoiseMode, ReadyToStart, E_Stop, Surprise;

void StateMachine (){

if ((Buttons | 0b0000001) == 0b0000001) {
    Button1Pressed = 1;    
} else{
    Button1Pressed = 0;
}

if ((Buttons | 0b0000010) == 0b0000010) {
    Button2Pressed = 1;    
} else{
    Button2Pressed = 0;
}

if ((Buttons | 0b00000100) == 0b00000100) {
    Button3Pressed = 1;    
} else{
    Button3Pressed = 0;
}

if ((Buttons | 0b00001000) == 0b00001000) {
    Button4Pressed = 1;    
} else{
    Button4Pressed = 0;

}

// State 0: Waiting to start 
// State 1: Button 1 Pressed -> normal mode
// State 2: Button 2 Pressed -> Noise mode
// Sate 3: Button 3 pressed -> MERRY CHRISTMAS!
// State 4: Button 4 pressed -> E-stop -> yellow buttom

S0 = (S0 || (S3&&Button4Pressed)) &&!S1 &&!S3 &&!S4:
S1 = (S1 || (S0&&Button1Pressed)) &&!S3;
S2 = (S2 || (S0&&Button2Pressed)) &&!S3;
S3 = (S3 || (S1&&Button4Pressed) || (S2&&Button4Pressed) || (S3&&Button4Pressed)) &&! S0);
S4 = (S4 || (S0&&Button3Pressed) &&!S3);

ReadyToStart = (S0)&&!S1&&!S2&&!S3&&!S4;
NormalMode = (S1)&&!S0&&!S2&&!S3&&!S4;
NoiseMode = (S2)&&!S0&&!S1&&!S3&&!S4;
Surprise = (S3)&&!S0&&!S1&&!S2&&!S4; 
E_Stop = (S4)&&!S0&&!S1&&!S2&&!S3;

if (ReadyToStart)
{
    E_Stop (); 
}
if (NormalMode)
{
    NormalMode(motorACount, theta1_counts, motorBCount, theta2_counts);
}
if (NoiseMode)
{
    NoiseMode(motorACount, theta1_counts, motorBCount, theta2_counts);
}
if (E_Stop)
{
    E_Stop();
}
if (Surprise)
{
    //code to display MERRY CHIRSTMAS
}

}
