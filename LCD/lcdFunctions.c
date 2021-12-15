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

/*

// USART Transmitter buffer
char tx_buffer0[TX_BUFFER_SIZE0];

#if TX_BUFFER_SIZE0 <= 256
volatile unsigned char tx_wr_index0=0,tx_rd_index0=0;
#else
volatile unsigned int tx_wr_index0=0,tx_rd_index0=0;
#endif

#if TX_BUFFER_SIZE0 < 256
volatile unsigned char tx_counter0=0;
#else
volatile unsigned int tx_counter0=0;
#endif

// USART Transmitter interrupt service routine
interrupt [USART_TXC] void usart_tx_isr(void)
{
	if (tx_counter0)
	{
		--tx_counter0;
		UDR0=tx_buffer0[tx_rd_index0++];
		#if TX_BUFFER_SIZE0 != 256
		if (tx_rd_index0 == TX_BUFFER_SIZE0) tx_rd_index0=0;
		#endif
	}
}

// Write a character to the USART Transmitter buffer
#define _ALTERNATE_PUTCHAR_
#pragma used+
void putchar(char c)
{
	while (tx_counter0 == TX_BUFFER_SIZE0);
	#asm("cli")
	if (tx_counter0 || ((UCSR0A & DATA_REGISTER_EMPTY)==0))
	{
		tx_buffer0[tx_wr_index0++]=c;
		#if TX_BUFFER_SIZE0 != 256
		if (tx_wr_index0 == TX_BUFFER_SIZE0) tx_wr_index0=0;
		#endif
		++tx_counter0;
	}
	else
	UDR0=c;
	#asm("sei")
}
#pragma used-

*/