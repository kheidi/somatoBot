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
	putchar(0xFE);
	putchar(0x58);
	delay_ms(10);
}
