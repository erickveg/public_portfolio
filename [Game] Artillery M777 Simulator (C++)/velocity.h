#pragma once

#include <cmath>          // for math defines
#define _USE_MATH_DEFINES // for M_PI
#include <math.h>         // for COS and SIN ans ATAN functions
#include "angle.h"

using namespace std;

class TestVelocity;
class TestProjectile;

class Velocity
{
   
private:  
   double dx;
   double dy;

public:
   friend TestVelocity;
   friend TestProjectile;

   // Default constructor
   Velocity(): dx(0.0), dy(0.0) {}

   // Non-default constrcutor
   Velocity(double dx, double dy);

   // Non-default constructor
   Velocity(double totalVelocity, Angle angleRadians);

   //
   double computeHorizontalVelocity(double angleRadians, double ddx, double time);
   // 
   double computeVerticalVelocity(double angleRadians, double ddy, double time);
   // 
   double getTotal() const;
   // 
   double computeMach(double speedSound) const;

   double getDirection() const;
   
   double getDx() const;
   double getDy() const;

   void setDx(double dx) { this->dx = dx; };
   void setDy(double dy) { this->dy = dy; };
};