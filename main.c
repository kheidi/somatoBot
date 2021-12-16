/*******************************************************
This program was created by the CodeWizardAVR V3.38 UL 
Automatic Program Generator
� Copyright 1998-2019 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 12/11/2021
Author  : 
Company : 
Comments: 


Chip type               : ATmega328P
Program type            : Application
AVR Core Clock frequency: 16.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega328p.h>
#include <delay.h>
#include "PWMDevel/generalFunctions.h"
#include "Robot Trajectory/MotorControl.h"
#include "LCD/lcdFunctions.h"
#include "PWMDevel/pwmControl.h"

// Declare your global variables here

volatile long int motorACount;
volatile long int motorBCount;

// --- For position control:
float x0, y0, r, w, t; // for the trajectory function
float kp_1, kp_2, kd_1, kd_2, k1_1, k1_2, k0_1, k0_2, theta1_counts, theta2_counts;  // for the control law
unsigned int e1, m1, e2, m2; //or float? -->  for the control law
struct theta mytheta; //get thetas from the struct

//(x0,y0) -> initial position of the robot ---- move the robot back to position (x0, y0) always
//r -> radios of the circle the link will move
//w -> how fast I want to make a full circle (Hz)


// Standard Input/Output functions
#include <stdio.h>

// Timer1 output compare A interrupt service routine
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{

	if (abs(motorACount)<theta1_counts)
	{
		runMotor(20, MOTOR_A, CCW);
	}
	else
	{
		OCR0A = 0;
		OCR0B = 0;
		OCR0A = 0;
		OCR0B = 0;

	}
	if(motorBCount<theta2_counts)
	{
	
		runMotor(20, MOTOR_B, CW);
		//stopMotors();
	} 
	else 
	{
		OCR2A = 0;
		OCR2B = 0;
		OCR2A = 0;
		OCR2B = 0;
	}
	

}

void main(void)
{
// Declare your local variables here

// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=(1<<CLKPCE);
CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Input/Output Ports initialization
// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=Out Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (1<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (1<<DDD6) | (1<<DDD5) | (0<<DDD4) | (1<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0A output: Disconnected
// OC0B output: Disconnected
pwm_init_timer0_A();

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 16000.000 kHz
// Mode: CTC top=OCR1A
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 2.0001 ms
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: On
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (0<<CS12) | (0<<CS11) | (1<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x7D;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// -------- I want to change to a lower frequency

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2A output: Disconnected
// OC2B output: Disconnected
pwm_init_timer2_B();

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=(0<<OCIE0B) | (0<<OCIE0A) | (0<<TOIE0);

// Timer/Counter 1 Interrupt(s) initialization
TIMSK1=(0<<ICIE1) | (0<<OCIE1B) | (0<<OCIE1A) | (0<<TOIE1);

// Timer/Counter 2 Interrupt(s) initialization
TIMSK2=(0<<OCIE2B) | (0<<OCIE2A) | (0<<TOIE2);

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// Interrupt on any change on pins PCINT0-7: Off
// Interrupt on any change on pins PCINT8-14: Off
// Interrupt on any change on pins PCINT16-23: Off
PCINT_Encoder_init();

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: Off
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 9600
UCSR0A=(0<<RXC0) | (0<<TXC0) | (0<<UDRE0) | (0<<FE0) | (0<<DOR0) | (0<<UPE0) | (0<<U2X0) | (0<<MPCM0);
UCSR0B=(0<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (0<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
UCSR0C=(0<<UMSEL01) | (0<<UMSEL00) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPOL0);
UBRR0H=0x00;
UBRR0L=0x67;

// Analog Comparator initialization
// Analog Comparator: Off
// The Analog Comparator's positive input is
// connected to the AIN0 pin
// The Analog Comparator's negative input is
// connected to the AIN1 pin
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
ADCSRB=(0<<ACME);
// Digital input buffer on AIN0: On
// Digital input buffer on AIN1: On
DIDR1=(0<<AIN0D) | (0<<AIN1D);

// ADC initialization
// ADC disabled
ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);

// SPI initialization
// SPI disabled
SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

// TWI initialization
// TWI disabled
TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

// Globally enable interrupts

delay_ms(600);
stopMotors();
resetAllEncoderCounts();
setLCDbrightness(255);
setLCDColor(CHARTREUSE);
printStringLCD("My message");

TIMSK1=(0<<ICIE1) | (0<<OCIE1B) | (1<<OCIE1A) | (0<<TOIE1);

// delay_ms(1000);
// 
//runMotor(50,MOTOR_B,CW);
//delay_ms(5000);
// stopMotors();
// delay_ms(1000);
// runMotor(50,MOTOR_A,CCW);
// delay_ms(5000);
// stopMotors();
// delay_ms(1);

// delay_ms(1000);
// 
// runMotor(50,MOTOR_B,CW);
// delay_ms(5000);
// stopMotors();
// delay_ms(1000);
// runMotor(50,MOTOR_B,CCW);
// delay_ms(5000);
// stopMotors();
// delay_ms(1);



//  stopMotors();
//  putchar(0xFE);
//  putchar(0x58); //Clear
//  delay_ms(20);
//  
//  //putchar(0xFE);
//  putchar('H'); // H
//  putchar(0x73); //S
//  delay_ms(20);
//  //delay_ms(1000);
//  
//  putchar(0xFE);
//  putchar(0x58); //Clear
//  delay_ms(20);
//  
//  putchar(0xFE);
//  putchar('S'); //S
 
#asm("sei")

			// Link Trajectory calculation
			r = 0.03;
			t = 1;
			w = 50; //0.02s
			x0=.03;
			y0=.02;
			mytheta = Trajectory(x0, y0, r, w, t); // variable to get thet1 & theta2

			//convert to encoder count to send to the motor
			theta1_counts =  AngleToCountsConversion (mytheta.theta1);
			theta2_counts =  AngleToCountsConversion (mytheta.theta2);
 
while (1)

      {
					
			// Command law gains:
			kp_1 = 0.1;
			kp_2 = 0.1;
			kd_1 = 0;
			kd_2 = 0;

			// k0_1 = Kp_1 + kd_1/delta_t;
			// k1_1 = - kd_1/delta_t;
			// k0_2 = Kp_2 + kd_2/delta_t;
			// k1_2 = - kd_2/delta_t;
		  
		  // Motor Control Laws: 

			//------Command Law: Link 1------
			//Simple Law:
			// e1 = theta1_counts - motorACount; // our end position was calculated with IK
			// m1 = kp_1*e1;

			//PD on Error:
			//e1 = theta1_counts - motorACount; // our end position was calculated with IK
			//m1 = k0_1*e1 + k1_1*e1;


			//------Command Law: Link 2------

			//Simple Law:
			// e2 = theta2_counts - motorBCount; // our end position was calculated with IK
			// m2 = kp_2*e2;

			//PD on Error:
			//e2 = theta2_counts - motorBCount; // our end position was calculated with IK
			//m2 = k0_2*e2 + k1_2*e2;


			// Place your code here
// 				runMotor(60, MOTOR_A, CCW);
// 		 		delay_us(1000000);
// 				runMotor(60, MOTOR_B, CW);
// 				delay_us(1000000);
// 				runMotor(70, MOTOR_A, CCW);
//		 		delay_us(1000000);
		// 		runMotor(70, MOTOR_B, CW);
		// 		delay_us(1000000);
		// 		runMotor(80, MOTOR_A, CCW);
		// 		delay_us(1000000);
		// 		runMotor(80, MOTOR_B, CW);
		// 		delay_us(1000000);
		// 		runMotor(90, MOTOR_A, CCW);
		// 		delay_us(1000000);
		// 		runMotor(90, MOTOR_B, CW);
		// 		delay_us(1000000);
		// 		runMotor(100, MOTOR_A, CCW);
		// 		delay_us(1000000);
		// 		runMotor(100, MOTOR_B, CW);
		// 		delay_us(1000000);
		// 		runMotor(0,MOTOR_A,CW);
 		


      }
}
