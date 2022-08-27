/***********************************************************************
 * Header File:
 *    Velocity : Represents the velocity of the LM in the lunar lander simulation
 * Author:
 *    Team One
 * Summary:
 *    The total velocity of the LM and its vertical and horizontal components.
 ************************************************************************/

#include "velocity.h"

#include <iostream>       // for CIN and COUT
#define _USE_MATH_DEFINES // for M_PI
#include <math.h>         // for COS and SIN functions

using namespace std;

#define WEIGHT 15103.00   // Weight in KG
#define GRAVITY -1.625    // Vertical acceleration due to gravity, in m/s^2
#define THRUST 45000.00   // Thrust of main engine, in Newtons (kg m/s^2) 

double Velocity :: computeVelocity(double v, double acc, double t)
{
   return v + acc * t; // Return new velocity
}

/***********************************************
* COMPUTE VERTICAL COMPONENT
* Find the vertical component of a velocity or acceleration.
* The equation is:
*     cos(a) = y / total
* This can be expressed graphically:
*      x
*    +-----
*    |   /
*  y |  / total
*    |a/
*    |/
* INPUT
*     a : angle, in radians
*     total : total velocity or acceleration
* OUTPUT
*     y : the vertical component of the total
***********************************************/
double Velocity::computeVertical(double a, double ddy, double time)
{
   //dy += cos(a) * ddy * time;
   dy += ddy * time;
   return dy; // Return the vertical component
}

/***********************************************
* COMPUTE HORIZONTAL COMPONENT
* Find the horizontal component of a velocity or acceleration.
* The equation is:
*     sin(a) = x / total
* This can be expressed graphically:
*      x
*    +-----
*    |   /
*  y |  / total
*    |a/
*    |/
* INPUT
*     a : angle, in radians
*     total : total velocity or acceleration
* OUTPUT
*     x : the vertical component of the total
***********************************************/
double Velocity::computeHorizontal(double a, double ddx, double time)
{
   //dx += sin(a) * ddx * time;
   dx += ddx * time;
   return dx; //Return the horizontal component
}

/************************************************
* COMPUTE TOTAL COMPONENT
* Given the horizontal and vertical components of
* something (velocity or acceleration), determine
* the total component. To do this, use the Pythagorean Theorem:
*    x^2 + y^2 = t^2
* where:
*      x
*    +-----
*    |   /
*  y |  / total
*    | /
*    |/
* INPUT
*    x : horizontal component
*    y : vertical component
* OUTPUT
*    total : total component
***********************************************/
double Velocity::getTotal() const
{
   return sqrt(dx * dx + dy * dy); // Return the total value of the component
}