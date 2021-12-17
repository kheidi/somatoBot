/************************************************************************************
Copyright 2021 - K. Heidi Fehr & Stephanie B. Hernández
  Project : General Functions
  File    : generalFunctions.h
  Author  : K. Heidi Fehr & Stephanie B. Hernández
  Company : University of Wisconsin - Madison
            1513 Univ. Ave. Madison WI 53706
Revision history    Date         Name                      Reason
        -------    --------     ------                     -------------------------------
          1.00     12/4/2021    K. Fehr                    Development

************************************************************************************/
#ifndef GENERALFUNCTIONS_H_
#define GENERALFUNCTIONS_H_
/*
** ===================================================================
** Method        : map
**
** Description   :  Takes a number and re-maps it to another scale.
**
** Parameters:
**      NAME            - DESCRIPTION
**      x               - Number in original scale
**      in_min          - Minimum value of initial scale
**      in_max          - Max value of initial scale
**      out_min          - Minimum value of target scale
**      out_min          - Max value of target scale
**
** Returns:
**       x_new scale     - Returns x in the new scale
**             
**
** ===================================================================
*/
long map(long x, long in_min, long in_max, long out_min, long out_max);

int flt2fxd(float x);

#endif