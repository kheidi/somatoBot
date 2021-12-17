/*
* Author: K. Heidi Fehr (kfehr@wisc.edu)
* Github: @kheidi
* Filename: lcdFunctions.c
* Description: Functions to use with Adafruit LCD with serial backpack
*              https://cdn-learn.adafruit.com/downloads/pdf/usb-plus-serial-backpack.pdf
* Created:  2021-12-06T01:18:31.679Z
* (c)Copyright 2021
*/

/**
 * Non-backpack vid: https://www.youtube.com/watch?v=_J3Dp9TGdLY
 */


/** LCD is connected by three wires, GND, 5V and DATA
 * According to the PDF link above the actions are controled by 
 * messages it gets.
 * ? Not sure how things are sent to serial? simply written? LCD library?
 * For now will just map based on the PDF 
 **/

#include "lcdFunctions.h"

void clearLCD(void){
// 	putchar(0xFE);
// 	putchar(0x58);
// 	delay_ms(LCDdelay);
}
void makePink(void){
// 	putchar(0xFE);
// 	putchar(0xD0);
// 	putchar(0xef);
// 	putchar(0x00);
// 	putchar(0x8c);
// 	delay_ms(LCDdelay);
}

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
