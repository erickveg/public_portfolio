/***********************************************************************
 * Header File:
 *    Velocity : Represents the velocity of the LM in the lunar lander simulation
 * Author:
 *    Team One
 * Summary:
 *    The total velocity of the LM and its vertical and horizontal components.
 ************************************************************************/

#pragma once

#include <iostream>       // for CIN and COUT
#define _USE_MATH_DEFINES // for M_PI
#include <math.h>         // for COS and SIN functions

using namespace std;

 /*************************************************************************
 * VELOCITY
 * A single velocity value influenced by acceleration and time
 *************************************************************************/
class Velocity
{
private:
   double dx;
   double dy;

   double computeVelocity(double v, double acc, double t);

public:
   // Constructors
   Velocity(): dx(0.0), dy(0.0) {}
   //Velocity(double v, double a, double t) {}


   double getTotal() const;
   double getdx() const { return dx; }
   double getdy() const { return dy; }
   double computeHorizontal(double a, double ddx, double t);
   double computeVertical(double a, double ddy, double t);
   
};



