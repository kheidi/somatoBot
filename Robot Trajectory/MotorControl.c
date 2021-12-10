/************************************************************************************
Copyright 2021 - K. Heidi Fehr & Stephanie B. Hernández
  Project : Motor Control Custom Functions
  File    : MotorControl.c
  Author  : K. Heidi Fehr & Stephanie B. Hernández
  Company : University of Wisconsin - Madison
            1513 Univ. Ave. Madison WI 53706
Revision history    Date         Name                      Reason
        -------    --------     ------                     -------------------------------
          1.00     12/09/21     K. Fehr & S. Hernández     Development

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

#include <stdio.h> // not sure where it goes (main.c?)
#include <math.h>  // not sure where it goes (main.c?)
#include "MotorControl.h"

#define pi = 3.1514926535897

struct theta Trajectory(float x0, float y0, float r, float w, float t)
{
    struct theta mytheta;
    //circular trajectory
    float x, y, l1, l2; // this variable will be time dependent

    l1 = 153; //[mm]
    l2 = 140; //[mm]
    x=r*cos(2*pi*w*t)+x0;
    y=r*sin(2*pi*w*t)+y0;

    // Inverse Kinematics
    mytheta.theta2 = acos((pow(x,2)+pow(y,2)-pow(l1,2)-pow(l2,2))/(2*l1*l2)); //wrist down
    mytheta.theta1 = atan(y/x) - atan((l2*sin(output.theta.theta2))/(l1+l2*sin(output.theta.theta2))) ; //wrist down
    
    return mytheta; 

}

/* inside main
float x0, y0, r, w, t, delta_t, theta1_current, theta2_current, kp_1, kp_1, kd_1, kd_2, k1_1, k1_2, k0_1, 0_2; 
int e1, m1, r1, e2, m2, r2, t_final; //or float?
//(x0,y0) -> initial position of the robot ---- Not sure if this should be updated or move the robot back to position (x0, y0) always...
//r -> radios of the circle the link will move
//w -> how fast I want to make a full circle (Hz)
//theta#_current -> read angle of the link from the encoder

t=0; // calculate time based on the frequency
delta_t= 1/interrupt freq; //
t_final = 1; // duration of movement,

Struct theta;
k0_1 = Kp_1 + kd_1/delta_t;
k1_1 = - kd_1/delta_t;
k0_2 = Kp_2 + kd_2/delta_t;
k1_2 = - kd_2/delta_t;

*/

/*inside the interrupt 
if(t < t_final) //need this to get final thetas. If not here, it will run "forever"
{ 
theta = Trajectory(x0, y0, r, w, t); // variable to get thet1 & theta2
 

//Add code to read ecoder position for theta1_current & theta2_current

//------Command Law: Link 1------
//Simple Law:
e1 = theta.theta1 - theta1_current; //theta1 from the IK function
m1 = kp_1*e1;
//PD on Error:
e1 = theta.theta1 - theta1_current; //theta1 from the IK function
m1 = k0_1*e1 + k1_1*e1;


//------Command Law: Link 2------

//Simple Law:
e2 = theta.theta2 - theta2_current; //theta2 from the IK function
m2 = kp_2*e2;

//PD on Error:
e2 = theta.theta2 - theta2_current; //theta2 from the IK function
m2 = k0_2*e2 + k1_2*e2;

//PWM Code to move the motors...

} // end of if statement
t+=delta_t;
*/

