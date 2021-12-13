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

// Declare your global variables here

#define DATA_REGISTER_EMPTY (1<<UDRE0)
#define RX_COMPLETE (1<<RXC0)
#define FRAMING_ERROR (1<<FE0)
#define PARITY_ERROR (1<<UPE0)
#define DATA_OVERRUN (1<<DOR0)

// USART Transmitter buffer
#define TX_BUFFER_SIZE0 8

#endif

