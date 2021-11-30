
/*
file:sensorManager.ino
Author: Alex Dawson-Elli
with aknowledgements to Nick Gammon 2011
for the SPI slave mode code, and PC interrupts
*/


//imports

#include <SPI.h>               //communication protocol
#include <avr/io.h>            //headerfiles for all the macros
#include <stdint.h>            // has to be added to use uint8_t
#include <avr/interrupt.h>     // Needed to use interrupts    
//#include <Arduino.h>           // Needed for analog macros A0 etc.

//------------------globals--------------------------

//command macros
#define READ  0 
#define CRANK 1
#define LEFT  2
#define RIGHT 3

//encoder counter variables
volatile int CrankCount = 0;
volatile int RightPedalCount = 0;
volatile int LeftPedalCount = 0;

//encoder count snapshots
volatile int CrankCountSS = 0;
volatile int RightPedalCountSS = 0;
volatile int LeftPedalCountSS = 0;


//counts per revolution for each encoder
int crankCCR = 24000; //4x because counts on pin change
int pedalCCR = 20000;

//encoder Zstart Flags;
volatile uint8_t ZstartCrank = 0x00;
volatile uint8_t ZstartRightPedal = 0x00;
volatile uint8_t ZstartLeftPedal = 0x00;

//pin history time 
volatile uint8_t PINChistory = 0x00;  //this could cause an error depending on start state
volatile uint8_t PINDhistory = 0x00;  //but should be avoided by Z-start code

//SPI communication variable
volatile char outputFlag = 0x00;


/*lookup table - 4x4 table, defining how to adjust
the counter depending on the transition between
the old state and the new one. the stateChangeTable
should be called as: stateChangeTable[old][new]

note that the state of the bits maps to the index
values of the table as the decimal representation of
their binary values:
00 -> 0
01 -> 1
10 -> 2
11 -> 3
*/

char stateChangeTable[4][4] = //validate correctness
{
    { 0,-1, 1, 0},
    { 1, 0, 0,-1},
    {-1, 0, 0, 1},
    { 0, 1,-1, 0}
};

  
//-------------------------------Encoder ISR's------------------------------------

/*
PIN mapping Table:

_______|_______|______
zCrank | PIND2 | D2         
zRight | PIND3 | D3                    
zLeft  | PIND4 | D4      
*/


//Pin Change ISR for Z channels of all 3 encoders
//Zline of each encoder goes high to signal where the zero of the encoder is
ISR (PCINT2_vect)  //(PORTD arduino pins D2, D3, D4)
{   
    //rollover counter back to zero when zpulse is detected
    if(PIND & 0b00000100){ZstartCrank = 1;           CrankCount = 0;}            
    if(PIND & 0b00001000){ZstartRightPedal = 1; RightPedalCount = 0;}
    if(PIND & 0b00010000){ZstartLeftPedal = 1;   LeftPedalCount = 0;}

}



/*
PIN mapping Table:                  

_______|_______|______
CrankA | PINC0 | A0          
CrankB | PINC1 | A1                  
RightA | PINC2 | A2     
RightB | PINC3 | A3     
leftA  | PINC4 | A4
LeftB  | PINC5 | A5

*/

//Pin Change ISR for A and B channels of all three encoders
ISR (PCINT1_vect) //(PORTC arduino pins A0, A1, A2, A3, A4, A5)
{
    //history and current pin terms
    uint8_t PINCcurrent = PINC & 0b00111111; //grab only the relevant pins
    uint8_t changedbits = PINCcurrent ^ PINChistory;
    
    //mask bits
    uint8_t CrankMask = 0b00000011;
    uint8_t RightMask = 0b00001100;
    uint8_t leftMask  = 0b00110000;

    //read and update Crank 
     if(changedbits & CrankMask) //something has changed in Crank's state
    {
        CrankCount += stateChangeTable[(PINChistory & CrankMask)][(PINCcurrent & CrankMask)];
    }
    
    //read and update RightPedal
    if(changedbits & RightMask) //something has changed in RightPedal's state
    {
        RightPedalCount += stateChangeTable[((PINChistory & RightMask) >> 2)][((PINCcurrent & RightMask) >> 2)];  
    }

    //read and update leftPedal
    if(changedbits & leftMask) //something has changed in LeftPedal's state
    {
        LeftPedalCount += stateChangeTable[((PINChistory & leftMask)>> 4)][((PINCcurrent & leftMask)>> 4)];
    }

    PINChistory = PINCcurrent;    
}


//-------------------------------SPI ISR------------------------------------
/* the SPI is operating here in slave mode, so that is recieves a byte 
 that contains an instruction regarding what data is desired by the  master device
 and then writes the desired data into the buffer, which is read next time
 */

ISR (SPI_STC_vect)
{
    //outline of how SPI handler logic will work. 
    byte command = SPDR; //grab byte from SPI data register

    //consider turning on interrupts to allow counting of pulses here
    //sei(); //if missing pulses @higher rpm's

    //make sure that all Zstart's have been triggered before sending ANYTHING other than zero
    if(ZstartCrank & ZstartRightPedal & ZstartLeftPedal)
    {
        //ajust output flag depending on what is requested by master
        if( command == 's' | command == CRANK){outputFlag = 5;} 
        else if(command == RIGHT){outputFlag = 3;}
        else if (command == LEFT){outputFlag = 1;}


        //perform a read operation if one of 4 allowed commands
        if( command == READ | command == 's' | command == RIGHT | command == LEFT ) 
        {
            if(outputFlag == 5){CrankCountSS = CrankCount; SPDR = CrankCountSS >> 8;} //buffer upper
            else if(outputFlag == 4){SPDR = CrankCountSS & 0x00FF;}                   //buffer lower
            else if(outputFlag == 3){RightPedalCountSS = RightPedalCount; SPDR = RightPedalCountSS >> 8;}
            else if(outputFlag == 2){SPDR = RightPedalCountSS & 0x00FF;}
            else if(outputFlag == 1){LeftPedalCountSS = LeftPedalCount; SPDR = LeftPedalCountSS >> 8;}
            else if(outputFlag == 0){SPDR = LeftPedalCountSS & 0x00FF;}
            
            outputFlag = outputFlag - 1;
        }

    }
    else {SPDR = 0;} //return zero's until all Z's have been triggered

  }


/*
SPDR = encoderCount >> 8       // buffer upper
SPDR = encoderCount & 0x00FF   //buffer lower

these commands add the encoder count to the buffer to be sent on the next SPI call
remember we can only send one byte at a time per transfer, and the byte added to the
buffer during this ISR call will be sent NEXT time the ISR is entered, because the
master initiated a transfer
*/



void setup()  
{   
    //--------------------------------encoder setup-----------------------------------------------
    //setup PC ISR for A and B channels
    DDRC &= ~((1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3) | (1 << DDC4) | (1 << DDC5)); // DDRC = 0bxx000000, PC0 - PC5 are now inputs
    PORTC &= ~((1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC4) |  (1 << PORTC5)); // turn off the Pull-ups on b  PORTB = xx000000;
   
    PCICR  |= (1 << PCIE1);     // enable pin change interrupts for A0 to A5, AKA PORTC set PCIE1 to enable PCMSK1 scan
    PCMSK1  = 0b00111111;       // enable PC interrupts on pins 0-5  
    PCIFR  |= (1 << PCIF1);     // clear any outstanding interrupts in PC flag register


    //setup PC ISR for Z channels
    DDRD &=  ~((1 << DDD2) | (1 << DDD3) | (1 << DDD4)); // DDRD = 0bxxx000xx, PD2,PD3,PD4, are now inputs
    PORTD &= ~((1 << PORTD2) | (1 << PORTD3) | (1 << PORTD4)); // turn off the Pull-ups on b  PORTD = xxx000xx;
   
    PCICR  |= (1 << PCIE2);     // enable pin change interrupts for D8 to D13, aka PORTD. set PCIE2 to enable PCMSK0 scan
    PCMSK2  = 0b00011100;       // enable PC interrupts only on pins 2,3,4
    PCIFR  |= (1 << PCIF2);     // clear any outstanding interrupts in PC flag register

    //-----------------------------------SPI Setup-------------------------------------------------

    // have to send on master in, *slave out*
    pinMode(MISO, OUTPUT);

    // turn on SPI in slave mode
    SPCR |= _BV(SPE);

    // turn on interrupts
    SPCR |= _BV(SPIE);

    // turn on interrupts
    sei();

}

void loop()
{;}






