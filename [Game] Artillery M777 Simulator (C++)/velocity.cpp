
#include "velocity.h"



// Non-default constructor definition
Velocity::Velocity(double dx, double dy)
{
   this->dx = dx;
   this->dy = dy;
};

// Non-default constructor definition
Velocity::Velocity(double totalVelocity, Angle angle)
{
   this->dx = totalVelocity * sin(angle.getRadians());
   this->dy = totalVelocity * cos(angle.getRadians());
};

double Velocity::computeHorizontalVelocity(double angleRadians, double ddx, double time)
{
   dx = sin(angleRadians) * getTotal() + ddx * time;
   return dx;
}

double Velocity::computeVerticalVelocity(double angleRadians, double ddy, double time)
{
   dy = cos(angleRadians) * getTotal() + ddy * time;
   return dy;
}

double Velocity::getTotal() const
{
   return sqrt((dx * dx) + (dy * dy));
}

double Velocity::computeMach(double speedSound) const
{
   return getTotal() / speedSound;
}

/*************************************************
* ANGLE FRON COMPONENTS
* Convert degrees to radians:
* The equation is:
*     a = atan(dx, dy)
* INPUT
      dx = horizontal component of speed (m/s)
*     dy = verti cal component of speed (m/s)
* OUTPUT
*     a = directon of travel where 0 is pointi ng up (radians)
**************************************************/
double Velocity::getDirection() const
{
   double angleRad = atan2(dx, dy);
   // Normalize angle in radians
   return angleRad - (floor(angleRad / (2.0 * M_PI)) * (2.0 * M_PI));
}

double Velocity::getDx() const
{
   return dx;
}

double Velocity::getDy() const
{
   return dy;
}

