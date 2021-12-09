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

#include <mega2560.h> // change to our MCU

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

float Trajectory(float x0, float y0, float r, float w, float t);

	