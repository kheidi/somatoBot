/************************************************************************************
Copyright 2021 - K. Heidi Fehr & Stephanie B. Hernández
  Project : Robot Links Trajectories Custom Functions
  File    : Trajectory.c
  Author  : K. Heidi Fehr & Stephanie B. Hernández
  Company : University of Wisconsin - Madison
            1513 Univ. Ave. Madison WI 53706
Revision history    Date         Name                      Reason
        -------    --------     ------                     -------------------------------
          1.00     12/07/21     K. Fehr & S. Hernández     Development

Functions used to control the trajectory of a two link robot.
************************************************************************************/

#include "Trajectory.h"

 extern float theta1_counts, theta2_counts;  // for the control law
 extern unsigned int e1, m1, e2, m2; //or float? -->  for the control law
 extern struct theta mytheta; //get thetas from the struct
 extern volatile long int motorACount;
 extern volatile long int motorBCount;

/*
** ===================================================================
** Method        : Trajectory
**
** Description   : Uses two link robot kinematic to find the angles of the 
*                   links for the robot to move in a circular trajectory.
**
**
**
** Parameters:
**      NAME            - DESCRIPTION
**      x0              - initial position in the x cooridnate of the end of link 2 
**      y0              - initial position in the y cooridnate of the end of link 
**      r               - radius of the circulat trajectory of link 2
**      w               - frequency to do a full rotation of the circular trajectory
**      t               - actual time of computation
**
** ===================================================================
*/



struct theta Trajectory(float x0, float y0, float r, float w, float t)
{
	float x, y, l1, l2, theta1Rad, theta2Rad; // variable will be time dependent
	float temp;
    struct theta mytheta;
	
    //circular trajectory
    l1 = 0.153; //[m]
    l2 = 0.140; //[m]
	
	//x0 = 0.03 , y0 = 0.02
	
   // x = ((r*cos(2*PI*w*t))+x0);
   // y = ((r*sin(2*PI*w*t))+y0);
	x = x0;
	y = y0;

    // Inverse Kinematics - thetas in radians
	theta2Rad = acos(((x*x)+(y*y)-(l1*l1)-(l2*l2))/(2*l1*l2)); //wrist down
 	theta1Rad = atan(y/x) - atan((l2*sin(theta2Rad))/(l1+(l2*cos(theta2Rad)))) ; //wrist down
	
	// Radians to angle conversion:
	mytheta.theta1 = (theta1Rad*(180/PI));
	mytheta.theta2 = (theta2Rad*(180/PI));
	
	return mytheta; 

}

int AngleToCountsConversion (float theta)
{


	 float percentage;
	 int theta_counts;
	 percentage = theta/360;
	 theta_counts = percentage*900;
	
	return theta_counts;
}


void StopMotorA (void) 
{
    OCR0A = 0;
    OCR0B = 0;
    OCR0A = 0;
    OCR0B = 0;

}

void StopMotorB (void) 
{
	OCR2A = 0;
	OCR2B = 0;
	OCR2A = 0;
	OCR2B = 0;
}

void NormalMode (int LOCALmotorACount, int LOCALtheta1_counts, int LOCALmotorBCount, int LOCALtheta2_counts)
{
		
    if (abs(LOCALmotorACount)<LOCALtheta1_counts)
	{
		runMotor(20, MOTOR_A, CCW);
	} else
	{
		StopMotorA();
	}
	
	if(LOCALmotorBCount<LOCALtheta2_counts)
	{
	
		runMotor(20, MOTOR_B, CW);

	} else 
	{
	    StopMotorB();
	} 
}

void NoiseMode (int LOCALmotorACount, int LOCALtheta1_counts, int LOCALmotorBCount, int LOCALtheta2_counts)
{
    if (abs((LOCALmotorACount+10))<LOCALtheta1_counts)
	{
		runMotor(20, MOTOR_A, CCW);
	}
	else
	{
		StopMotorA();
	}
	if((LOCALmotorBCount+10)<LOCALtheta2_counts)
	{
	
		runMotor(20, MOTOR_B, CW);

	} 
	else 
	{
	    StopMotorB();
	}
}

void E_Stop (void) 
{
  m1 = 0;
  m2 = 0;
  e1 = 0;
  e2 = 0;
  mytheta.theta1 = 0;
  mytheta.theta1 = 0;
  theta1_counts = 0;
  theta2_counts = 0;
  resetAllEncoderCounts();
  StopMotorB();
  StopMotorA();
}


