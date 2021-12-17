/************************************************************************************
Copyright 2021 - K. Heidi Fehr & Stephanie B. Hernández
  Project : lcdFunctions
  File    : lcdFunctions.c
  Author  : K. Heidi Fehr & Stephanie B. Hernández
  Company : University of Wisconsin - Madison
            1513 Univ. Ave. Madison WI 53706
Revision history    Date         Name                      Reason
        -------    --------     ------                     -------------------------------
          1.00     12/06/2021    K. Fehr                    Development

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

Info on LCD: https://cdn-learn.adafruit.com/downloads/pdf/usb-plus-serial-backpack.pdf
************************************************************************************/

#ifndef LCDFUNCTIONS_H_
#define LCDFUNCTIONS_H_

#include <mega328p.h>
#include <stdio.h>
#include <stdlib.h>
#include <delay.h>

#define LCDdelay 10  //us Pick a nice delay time to ramp up motor speed
#define RED 0
#define GREEN 1
#define BLUE 2
#define PINK 3
#define CHARTREUSE 4
#define WHITE 5
#define PURPLE 6
#define YELLOW 7

/*
** ===================================================================
** Method        : clearLCD
**
** Description   : Clears the LCD
**
** ===================================================================
*/
void clearLCD(void);


void printStringLCD(char *ch);

/*
** ===================================================================
** Method        : makePink
**
** Description   : Sets LCD color to pink.
**
** ===================================================================
*/
void makePink(void);

/*
** ===================================================================
** Method        : setLCDColor
**
** Description   : Set LCD backlight to colors as defined in .h
**
** ===================================================================
*/
void setLCDColor(char colorMacro);

/*
** ===================================================================
** Method        : setLCDbrightness
**
** Description   : Sets brightness to user defined value from 0 255
**
** ===================================================================
*/
void setLCDbrightness(char value);

#endif

