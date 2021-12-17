/************************************************************************************
Copyright 2021 - K. Heidi Fehr & Stephanie B. Hernández
  Project : Robot Links Trajectories Custom Functions
  File    : Trajectory.h
  Author  : K. Heidi Fehr & Stephanie B. Hernández
  Company : University of Wisconsin - Madison
            1513 Univ. Ave. Madison WI 53706
Revision history    Date         Name                      Reason
        -------    --------     ------                     -------------------------------
          1.00     12/07/21     K. Fehr & S. Hernández     Development

Functions used to control the trajectory of a two link robot.
************************************************************************************/
#ifndef TRAJECTORY_H_
#define TRAJECTORY_H_ 


#include <stdio.h> 
#include <stdlib.h>
#include <math.h>  
#include "PWMDevel/pwmControl.h"



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
**      x0              - initial position in the x coordinate of the end of link 2 
**      y0              - initial position in the y coordinate of the end of link 
**      r               - radius of the circular trajectory of link 2
**      w               - frequency to do a full rotation of the circular trajectory
**      t               - actual time of computation
**
** ===================================================================
*/

struct theta {

  float theta1;
  float theta2;
  float theta1_prev;
  float theta2_prev;

};

struct theta Trajectory(float x0, float y0, float r, float w, float t);
int AngleToCountsConversion (float theta);
void NormalMode (int LOCALmotorACount, int LOCALtheta1_counts, int LOCALmotorBCount, int LOCALtheta2_counts);
void NoiseMode (int motorACount, int theta1_counts, int motorBCount, int theta2_counts);
void E_Stop(void);
void StopMotorA();
void StopMotorB();
	
	
#endif