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

void ResetControlLaw (void) 
{
  m1 = 0;
  m2 = 0;
  e1 = 0;
  e2 = 0;
  mytheta.theta1 = 0;
  mytheta.theta1 = 0;
  theta1_count = 0;
  theta2_counts = 0;
]
}


