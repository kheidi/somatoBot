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

#include "lcdFunctions.h"

/*
** ===================================================================
** Method        : clearLCD
**
** Description   : Clears the LCD
**
** ===================================================================
*/
void clearLCD(void){
// 	putchar(0xFE);
// 	putchar(0x58);
// 	delay_ms(LCDdelay);
}

/*
** ===================================================================
** Method        : makePink
**
** Description   : Sets LCD color to pink.
**
** ===================================================================
*/
void makePink(void){
// 	putchar(0xFE);
// 	putchar(0xD0);
// 	putchar(0xef);
// 	putchar(0x00);
// 	putchar(0x8c);
// 	delay_ms(LCDdelay);
}

/*
** ===================================================================
** Method        : setLCDColor
**
** Description   : Set LCD backlight to colors as defined in .h
**
** ===================================================================
*/
void setLCDColor(char colorMacro){
// 	putchar(0xFE);
// 	putchar(0xD0);
// 	if (colorMacro == 0) //red
// 	{
// 		putchar(0xFF);
// 		putchar(0x00);
// 		putchar(0x00);
// 	}else if (colorMacro == 1) //blue
// 	{
// 		putchar(0x00);
// 		putchar(0xFF);
// 		putchar(0x00);
// 	}else if (colorMacro == 2) //green
// 	{
// 		putchar(0x00);
// 		putchar(0x00);
// 		putchar(0xFF);
// 	}else if (colorMacro == 3) //pink
// 	{
// 		putchar(0xef);
// 		putchar(0x00);
// 		putchar(0x8c);
// 	}else if (colorMacro == 4) //chartreuse
// 	{
// 		putchar(0xdf);
// 		putchar(0xff);
// 		putchar(0x00);
// 	}else if (colorMacro == 5) //white
// 	{
// 		putchar(0xff);
// 		putchar(0xfa);
// 		putchar(0xfa);
// 	}else if (colorMacro == 6) //purple
// 	{
// 		putchar(0x8A);
// 		putchar(0x2B);
// 		putchar(0xE2);
// 	}else if (colorMacro == 7) //yellow
// 	{
// 		putchar(0xFF);
// 		putchar(0xFF);
// 		putchar(0x00);
// 	}
// 	delay_ms(LCDdelay);
}

/*
** ===================================================================
** Method        : printStrinkLCD
**
** Description   : Sets LCD color to pink.
**
** ===================================================================
*/
void printStringLCD(char *ch)
{
	puts(ch);
// 	clearLCD();
// 	putchar(0xFE);
// 	putchar(0xFE);
//     while (*ch != '\0')
//     {
//         putchar(*ch); /* print letter */
//         ch = ch + 1;  /* point to the next letter. */
//     }
}

void setLCDbrightness(char value){
// 	putchar(0xFE);
// 	putchar(0x99);
// 	putchar(value);
// 	delay_ms(LCDdelay);
}
