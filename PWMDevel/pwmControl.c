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
#define delayTime 3  //Pick a nice delay time to ramp up motor speed

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

/*
** ===================================================================
** Method        : runMotor
**
** Description   : Run specified motor based on percent max power.
**
** Parameters:
**      NAME            - DESCRIPTION
**      percentMaxPower - Number from 0-100 that indicates amount of power to supply to motor
**      motorID         - String to indicate desired motor either "A" or "B"
**      direction       - Direction to spin motor, string either "CW" or "CCW"
**
** ===================================================================
*/
void runMotor(long percentMaxPower, const char* motorID, const char* direction)
{
    int sendToMotor;
    int speed;
    sendToMotor = (int)map(percentMaxPower,0,100,0,255); //Converts the percent power to a value from 0 255 for the 8-bit timers

    // ------- MOVE MOTOR A
    if (strcmp(motorID, "A") != 0) // 
    {
        if (strcmp(direction, "CCW") != 0) //Port D, pin 6 set duty cycle, direction A
        {
            for (speed = 0; speed < sendToMotor; speed++)
            {
                OCR0A = speed;
                delay_us(delayTime);
            }
        }
        if (strcmp(direction, "CW") != 0) //Port D, pin 5 set duty cycle, direction B
        {
            for (speed = 0; speed < sendToMotor; speed++)
            {
                OCR0B = speed;
                delay_us(delayTime);
            }
        }

    // ------- MOVE MOTOR B    
    } else if (strcmp(motorID, "B") != 0) // Move motor B
    {
        if (strcmp(direction, "CCW") != 0) //Port B, pin 3 set duty cycle, direction A
        {
            for (speed = 0; speed < sendToMotor; speed++)
            {
                OCR2A = speed;
                delay_us(delayTime);
            }
        }
        if (strcmp(direction, "CW") != 0) //Port D, pin 3 set duty cycle, direction B
        {
            for (speed = 0; speed < sendToMotor; speed++)
            {
                OCR2B = speed;
                delay_us(delayTime);
            }
        }
    }
    
}