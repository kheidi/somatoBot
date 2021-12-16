/************************************************************************************
Copyright 2021 - K. Heidi Fehr & Stephanie B. Hernández
  Project : State Machine for the robot's different simulations
  File    : StateMachine.h
  Author  : K. Heidi Fehr & Stephanie B. Hernández
  Company : University of Wisconsin - Madison
            1513 Univ. Ave. Madison WI 53706
Revision history    Date         Name                      Reason
        -------    --------     ------                     -------------------------------
          1.00     12/07/21     K. Fehr & S. Hernández     Development

State machine used to control the robot's simulations based on the button pressed.
************************************************************************************/

#include <stdio.h> 
#include "RobotTrajectory/Trajectory.h"
#define Buttons PINC
#define Button1Pressed  //PINC.0 - Normal mode
#define Button2Pressed //PINC.1 - Weird mode
#define Button3Pressed //PINC.2 - Restart
#define Button4Pressed  //PINC.3 - (E-stop)

/* CHANGE / UPDATE INFO
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

void StateMachine ();
