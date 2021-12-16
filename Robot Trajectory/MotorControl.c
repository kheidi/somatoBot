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

 extern float theta1_counts, theta2_counts;  // for the control law
 extern unsigned int e1, m1, e2, m2; //or float? -->  for the control law
 extern struct theta mytheta; //get thetas from the struct

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
	float x, y, l1, l2, alpha, beta ,phi, denominator, numerator; // variable will be time dependent
    struct theta mytheta;
	int i;
	
    //circular trajectory
    l1 = 0.153; //[m]
    l2 = 0.140; //[m]
	
	//x0 = 0.03 , y0 = 0.02
	
    x = ((r*cos(2*PI*w*t))+x0);
    y = ((r*sin(2*PI*w*t))+y0);
// 	denominator= (2*l1*(sqrt(pow(x,2)+pow(y,2))));
// 	numerator = (pow(x,2)+pow(y,2)-pow(l1,2)-pow(l2,2));	
	
	alpha = acos((pow(l1,2)+pow(l2,2)-pow(x,2)-pow(y,2))/(2*l1*l2));
	mytheta.theta2 = (PI -  alpha)*(180/PI);
	
	denominator = sqrt(pow(x,2)+pow(y,2));
	numerator = sin(alpha)*l1 ;
	//beta = atan2(y,x);
	beta = atan(y/x);
	phi = asin(numerator/denominator);
	mytheta.theta1 = (beta - phi)*(180/PI);

	mytheta.theta1 = abs(mytheta.theta1);
    // Inverse Kinematics
// 	  mytheta.theta2 = acos((pow(x,2)+pow(y,2)-pow(l1,2)-pow(l2,2))/(2*l1*l2)); //wrist down
// 	  mytheta.theta1 = atan(y/x) - atan((l2*sin(mytheta.theta2))/(l1+l2*sin(mytheta.theta2))) ; //wrist down

    
    return mytheta; 
	i =0;

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
  theta1_counts = 0;
  theta2_counts = 0;

}


