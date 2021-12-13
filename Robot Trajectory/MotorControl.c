/************************************************************************************
Copyright 2021 - K. Heidi Fehr & Stephanie B. Hernández
  Project : Motor Control Custom Functions
  File    : MotorControl.c
  Author  : K. Heidi Fehr & Stephanie B. Hernández
  Company : University of Wisconsin - Madison
            1513 Univ. Ave. Madison WI 53706
Revision history    Date         Name                      Reason
        -------    --------     ------                     -------------------------------
          1.00     12/07/21     K. Fehr & S. Hernández     Development

Functions used to control the trajectory of a two link robot.
************************************************************************************/

#include "MotorControl.h"

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
	float x, y, l1, l2; // this variable will be time dependent
    struct theta mytheta;
	
    //circular trajectory
    l1 = 153; //[mm]
    l2 = 140; //[mm]

    x = ((r*cos(2*PI*w*t))+x0);
    y = ((r*sin(2*PI*w*t))+y0);


    // Inverse Kinematics
	  mytheta.theta2 = acos((pow(x,2)+pow(y,2)-pow(l1,2)-pow(l2,2))/(2*l1*l2)); //wrist down
	  mytheta.theta1 = atan(y/x) - atan((l2*sin(mytheta.theta2))/(l1+l2*sin(mytheta.theta2))) ; //wrist down

    
    return mytheta; 

}

float AngleToCountsConversion (float theta)
{


  float percentage, theta_counts;
  percentage = theta/360;
  theta_counts = percentage*900;

return theta_counts;
}


/* inside main
float x0, y0, r, w, t; // for the trajectory function
float kp_1, kp_1, kd_1, kd_2, k1_1, k1_2, k0_1, 0_2, theta1_counts, theta2_counts;  // for the control law
int e1, m1, e2, m2; //or float? -->  for the control law
struct theta mytheta; //get thetas from the stuct

//(x0,y0) -> initial position of the robot ---- move the robot back to position (x0, y0) always
//r -> radios of the circle the link will move
//w -> how fast I want to make a full circle (Hz)

r=0.3

// Command law gains:
kp_1 = 0;
kp_2 = 0;
kd_1 = 0;
kd_2 = 0;
// k0_1 = Kp_1 + kd_1/delta_t;
// k1_1 = - kd_1/delta_t;
// k0_2 = Kp_2 + kd_2/delta_t;
// k1_2 = - kd_2/delta_t;

mytheta = Trajectory(x0, y0, r, w, t); // variable to get thet1 & theta2

//convert to encoder count to send to the motor
 theta1_counts =  AngleToCountsConversion (mytheta.theta1);
 theta2_counts =  AngleToCountsConversion (mytheta.theta2);
 
 */

/*inside the interrupt 

//------Command Law: Link 1------
//Simple Law:
e1 = theta1_counts - motorACount; // our end position was calculated with IK
m1 = kp_1*e1;

//PD on Error:
//e1 = theta1_counts - motorACount; // our end position was calculated with IK
//m1 = k0_1*e1 + k1_1*e1;


//------Command Law: Link 2------

//Simple Law:
e2 = theta2_counts - motorBCount; // our end position was calculated with IK
m2 = kp_2*e2;

//PD on Error:
//e2 = theta2_counts - motorBCount; // our end position was calculated with IK
//m2 = k0_2*e2 + k1_2*e2;

//Move the motors
runMotor(50, Motor_A, CCW);
runMotor(50, Motor_B, CW);

*/

