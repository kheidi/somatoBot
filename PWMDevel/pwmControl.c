/************************************************************************************
Copyright 2021 - K. Heidi Fehr & Stephanie B. Hernández
  Project : General Functions
  File    : generalFunctions.h
  Author  : K. Heidi Fehr & Stephanie B. Hernández
  Company : University of Wisconsin - Madison
            1513 Univ. Ave. Madison WI 53706
Revision history    Date         Name                      Reason
        -------    --------     ------                     -------------------------------
          1.00     12/4/2021    K. Fehr                    Development

Parts of this program were created by the CodeWizardAVR V3.31 
Automatic Program Generator
� Copyright 1998-2017 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Chip type               : ATmega328P
Program type            : Application
AVR Core Clock frequency: 16.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
************************************************************************************/

#include <delay.h>
#include <stdio.h>
#include <string.h>
#include "pwmControl.h" 
#define __DELAY_BACKWARD_COMPATIBLE__ //Needed for delay function/library

/*
** ------------------------------------------------------------------
* Global Variables
** -----------------------------------------------------------------
*/
//
// --- For encoder counter:
extern volatile long int motorACount;
extern volatile long int motorBCount;

//pin history time
volatile int PINBhistory = 0x00;  //this could cause an error depending on start state

signed char stateChangeTable[4][4] = //
{
	{ 0,-1, 1, 0},
	{ 1, 0, 0,-1},
	{-1, 0, 0, 1},
	{ 0, 1,-1, 0}
};


/*
** ===================================================================
** Method        : pwm_init_timer0_A
**
** Description   : Initializes PWM for motor A that uses timer0, Port D pin 6
**                 and Port D pin 5.
**
** ===================================================================
*/
void pwm_init_timer0_A()
{
    // Timer/Counter 0 initialization
    // Clock source: System Clock
    // Clock value: 16000.000 kHz
    // Mode: Fast PWM top=0xFF
    // OC0A output: Non-Inverted PWM
    // OC0B output: Non-Inverted PWM
    // Timer Period: 0.016 ms
    // Output Pulse(s):
    // OC0A Period: 0.016 ms Width: 0 us
    // OC0B Period: 0.016 ms Width: 0 us  
    
    // Set 1:  WGM01 and WGM00 -> Fast PWM  
    // Set 1 to COM0A1             -> Clear OC0A on Compare Match
    // Set 1 to COM0B1             -> Clear OC0B on Compare Match
    TCCR0A=(1<<COM0A1) | (0<<COM0A0) | (1<<COM0B1) | (0<<COM0B0) | (1<<WGM01) | (1<<WGM00);
    
    // No prescale
    TCCR0B=(0<<WGM02) | (0<<CS02) | (0<<CS01) | (1<<CS00);
    TCNT0=0x00;
                                   
    // Set initial duty cycles to 0
    OCR0A=0x00; //Port D, pin 6 set duty cycle, direction A
    OCR0B=0x00; //Port D, pin 5 set duty cycle, direction B

}

/*
** ===================================================================
** Method        : pwm_init_timer2_B
**
** Description   : Initializes PWM for motor B that uses timer0, Port B pin 3
**                 and Port D pin 3.
**
** ===================================================================
*/
void pwm_init_timer2_B()
{
    // Change corresponding ports to inputs
    DDRB |= (1<<DDB3);
     // Timer/Counter 2 initialization
    // Clock source: System Clock
    // Clock value: 16000.000 kHz
    // Mode: Fast PWM top=0xFF
    // OC2A output: Non-Inverted PWM
    // OC2B output: Non-Inverted PWM
    // Timer Period: 0.016 ms
    // Output Pulse(s):
    // OC2A Period: 0.016 ms Width: 0 ms
    // OC2B Period: 0.016 ms Width: 0 us 
    
    ASSR=(0<<EXCLK) | (0<<AS2);       
    
    // Set 1:  WGM21 and WGM20 -> Fast PWM  
    // Set 1 to COM2A1             -> Clear OC0A on Compare Match
    // Set 1 to COM2B1             -> Clear OC0B on Compare Match
    TCCR2A=(1<<COM2A1) | (0<<COM2A0) | (1<<COM2B1) | (0<<COM2B0) | (1<<WGM21) | (1<<WGM20);    
    
    // No prescale
    TCCR2B=(0<<WGM22) | (0<<CS22) | (0<<CS21) | (1<<CS20);
    TCNT2=0x00;
    
    // Set initial duty cycles to 0
    OCR2A=0x00; //Port B, pin 3 set duty cycle, direction A
    OCR2B=0x00; //Port D, pin 3 set duty cycle, direction B
}

void PCINT_Encoder_init()
{
    // Only the following PCINTs are enabled
    // as they are where the encoders are connected.
    //
    // PCINT0 / D8 / PB0
    // PCINT1 / D9 / PB1
    // PCINT2 / D10 / PB2
    // PCINT4 / D12 / PB4
    //
    // External Interrupt(s) initialization
    // INT0: Off
    // INT1: Off
    // Interrupt on any change on pins PCINT0-7: On
    // Interrupt on any change on pins PCINT8-14: Off
    // Interrupt on any change on pins PCINT16-23: Off
    EICRA=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
    EIMSK=(0<<INT1) | (0<<INT0);
    PCICR=(0<<PCIE2) | (0<<PCIE1) | (1<<PCIE0);
    PCMSK0=(0<<PCINT7) | (0<<PCINT6) | (0<<PCINT5) | (1<<PCINT4) | (0<<PCINT3) | (1<<PCINT2) | (1<<PCINT1) | (1<<PCINT0);
    PCIFR=(0<<PCIF2) | (0<<PCIF1) | (1<<PCIF0);
}

/*
** ===================================================================
** Method        : PI_INT encoder counter
**
** Description   :  Reads rising edges of encoders and either adds
                    or subtracts counts to the global motor
                    counters.
**
**
** ===================================================================
*/

// Pin change 8-14 interrupt service routine
interrupt [PC_INT0] void pin_change_isr0(void)
{
    // Only the following PCINTs are enabled
    // as they are where the encoders are connected.
    //
    // PCINT0 / D8 / PB0
    // PCINT1 / D9 / PB1
    // PCINT2 / D10 / PB2
    // PCINT4 / D12 / PB4

    // Adapted from encoderCounter.ino by Alex Dawson-Elli

	unsigned char changeIA = 0;
	unsigned char changeIB = 0;
	unsigned char changeJA = 0;
	unsigned char changeJB = 0;

    //history and current pin terms
    unsigned char PINBcurrent = PINB & 0b00010111; //grab only the relevant pins
    unsigned char changedbits = PINBcurrent ^ PINBhistory;
    
    //mask bits
    char motorAMask = 0b00000011;
    char motorBMask = 0b00010100;
	
    //read and update Crank 
     if(changedbits & motorAMask) //something has changed in Crank's state
    {
        motorACount += stateChangeTable[(PINBhistory & motorAMask)][(PINBcurrent & motorAMask)];
    }
    
    //read and update RightPedal
    if(changedbits & motorBMask) //something has changed in RightPedal's state
    {
        changeIA = ((PINBhistory & motorBMask) & 0b00000100) >> 2;
		changeIB = ((PINBhistory & motorBMask) & 0b00010000) >> 3;
		changeJA = ((PINBcurrent & motorBMask) & 0b00000100) >> 2;
		changeJB = ((PINBcurrent & motorBMask) & 0b00010000) >> 3;
		
        motorBCount += stateChangeTable[(changeIA | changeIB)][(changeJA | changeJB)];  
    }

    PINBhistory = PINBcurrent;   

}

void resetAllEncoderCounts(void){
	motorACount = 0;
	motorBCount = 0;
}

/*
** ===================================================================
** Method        : runMotor
**
** Description   : Run specified motor based on percent max power.
**
** Parameters:
**      NAME            - DESCRIPTION
**      percentMaxPower - Number from 0-100 that indicates amount of power to supply to motor
**      motorID         - String to indicate desired motor either 0 for "A" or 1 for "B"
**      direction       - Direction to spin motor, string either 0 for "CCW" or 0 for "CCW"
**
**      **If using macros from pwmControl.h use MOTOR_A and MOTOR_B for motor ID
**        and CCW and CW for direction.
**
** ===================================================================
*/
void runMotor(long percentMaxPower, int motorID, int direction)
{
    int sendToMotor;
    int speed;
    sendToMotor = (int)map(percentMaxPower,0,100,153,170); //Converts the percent power to a value from 0 255 for the 8-bit timers

    // ------- MOVE MOTOR A
    if (motorID == 0) // 
    {
        if (direction == 0) //Port D, pin 6 set duty cycle, direction A
        {
            for (speed = 0; speed < sendToMotor; speed++)
            {
                OCR0A = speed;
				OCR0B = 0;
                delay_us(delayTime);
            }
        }
        if (direction == 1) //Port D, pin 5 set duty cycle, direction B
        {
            for (speed = 0; speed < sendToMotor; speed++)
            {
				OCR0A = 0;
                OCR0B = speed;
                delay_us(delayTime);
            }
        }

    // ------- MOVE MOTOR B    
    } else if ((motorID == 1) != 0) // Move motor B
    {
        if ((direction == 0) != 0) //Port B, pin 3 set duty cycle, direction A
        {
            for (speed = 0; speed < sendToMotor; speed++)
            {
                OCR2A = speed;
				OCR2B = 0;
                delay_us(delayTime);
            }
        }
        if (direction == 1) //Port D, pin 3 set duty cycle, direction B
        {
            for (speed = 0; speed < sendToMotor; speed++)
            {
				OCR2A = 0;
                OCR2B = speed;
                delay_us(delayTime);
            }
        }
    }
    
}

void stopMotors(void)
{

	OCR0A = 0;
	OCR0B = 0;
	OCR0A = 0;
	OCR0B = 0;
	OCR2A = 0;
	OCR2B = 0;
	OCR2A = 0;
	OCR2B = 0;
	delay_us(delayTime);
      
    
}

