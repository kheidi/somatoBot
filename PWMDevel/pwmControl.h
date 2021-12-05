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

#include <io.h>
#include "generalFunctions.h"

/*
** ===================================================================
** Method        : pwm_init_timer0_A
**
** Description   : Initializes PWM for motor A that uses timer0, Port D pin 6
**                 and Port D pin 5.
**
** ===================================================================
*/
void pwm_init_timer0_A();

/*
** ===================================================================
** Method        : pwm_init_timer2_B
**
** Description   : Initializes PWM for motor B that uses timer0, Port B pin 3
**                 and Port D pin 3.
**
** ===================================================================
*/
void pwm_init_timer2_B();

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
void runMotor(long percentMaxPower, const char* motorID, const char* direction);