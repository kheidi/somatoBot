/*
* Author: K. Heidi Fehr (kfehr@wisc.edu)
* Github: @kheidi
* Filename: lcdFunctions.h
* Description: description
* Created:  2021-12-06T01:18:31.693Z
* (c)Copyright 2021
*/

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


void clearLCD(void);
void printStringLCD(char *ch);
void makePink(void);
void setLCDColor(char colorMacro);
void setLCDbrightness(char value);

#endif
