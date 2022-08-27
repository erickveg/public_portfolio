/***********************************************************************
 * Header File:
 *    Lunar Module : Represents the Lunar Module (LM) in the lunar lander simulation
 * Author:
 *    Team One
 * Summary:
 *    Where the LM is located, its next position, and fuel information.
 ************************************************************************/

#include <math.h>           // For sin() cos()

#include "lunarModule.h"

#define MASS 15103.00       // Weight in KG
#define GRAVITY -1.625      // Vertical acceleration due to gravity, in m/s^2
#define TOTALTHRUST 45000.0 // Thrust of main engine, in Newtons (kg m/s^2)
#define MAXFUEL 5000.0      // Max capacity of the fuel, in lbs

 /*************************************************************************
 * LUNAR MODULE constructor
 * 
 *************************************************************************/
LunarModule::LunarModule(Point position) :
      position(position),
      fuel(MAXFUEL),
      mass(MASS),
      mainThrust(false),
      clockThrust(false),
      counterThrust(false),
      landed(false)
{
}

/*************************************************************************
* LUNAR MODULE :: CONSUME FUEL
*
*************************************************************************/
void LunarModule::consumeFuel()
{
   if(clockThrust or counterThrust)
      fuel -= 1.0;

   if(mainThrust)
      fuel -= 10.0;

   if(fuel < 0)
      fuel = 0;
}

/*************************************************************************
* LUNAR MODULE :: CHANGE ANGLE RADIANS
*
*************************************************************************/
void LunarModule::changeAngleRadians(bool isLeft, bool isRight)
{
   if (clockThrust)
   {
      angle.addRadians(0.1);
   }
   if (counterThrust)
   {
      angle.addRadians(-0.1);
   }
}

/*************************************************************************
* LUNAR MODULE :: COMPUTE POSITION
*
*************************************************************************/
void LunarModule::computePosition(double time)
{
   double ddx = computeHorizontalAcceleration(TOTALTHRUST);
   double ddy = computeVerticalAcceleration(TOTALTHRUST) + GRAVITY;

   double dx = velocity.computeHorizontal(angle.getRadians(), ddx, time);
   double dy = velocity.computeVertical(angle.getRadians(), ddy, time);

   position.computeNewX(dx, ddx, time);
   position.computeNewY(dy, ddy, time);
}

/*************************************************************************
* LUNAR MODULE :: COMPUTE HORIZONTAL ACCELERATION
*
*************************************************************************/
double LunarModule::computeHorizontalAcceleration(double totalThrust) const
{
   if (mainThrust)
   {
      return -1 * sin(angle.getRadians()) * (totalThrust / mass);
   }
   return 0.0;
}

/*************************************************************************
* LUNAR MODULE :: COMPUTE VERTICAL ACCELERATION
*
*************************************************************************/
double LunarModule::computeVerticalAcceleration(double totalThrust) const
{
   if (mainThrust)
   {
      return cos(angle.getRadians()) * (totalThrust / mass);
   }
   return 0.0;
}

/*************************************************************************
* LUNAR MODULE :: DRAW NEXT
*
*************************************************************************/
void LunarModule::drawNext(ogstream& gout, bool isDown, bool isLeft, bool isRight, double time)
{
   if (landed)
   {
      gout.drawLander(position, angle.getRadians());
      return;
   }

   manageThrust(isDown, isLeft, isRight);
   computePosition(time);
   gout.drawLander(position, angle.getRadians());
   gout.drawLanderFlames(position, angle.getRadians(), mainThrust, clockThrust, counterThrust);
}

/*************************************************************************
* LUNAR MODULE :: MANAGE THRUST
*
*************************************************************************/
void LunarModule::manageThrust(bool isDown, bool isLeft, bool isRight)
{
   if (fuel > 0)
   {
      mainThrust = isDown;
      clockThrust = isLeft;
      counterThrust = isRight;

      consumeFuel();
      changeAngleRadians(clockThrust, counterThrust);
   }
   else
   {
      mainThrust = false;
      clockThrust = false;
      counterThrust = false;
   }
}

/*************************************************************************
* LUNAR MODULE :: GET FUEL
*
*************************************************************************/
double LunarModule::getFuel() const
{
   return fuel;
}

/*************************************************************************
* LUNAR MODULE :: GET ANGLE DEGREES
*
*************************************************************************/
double LunarModule::getAngleDegrees() const
{
   return angle.getDegrees();
}

/*************************************************************************
* LUNAR MODULE :: GET SPEED
*
*************************************************************************/
double LunarModule::getSpeed() const
{
   return velocity.getTotal();
}

/*************************************************************************
* LUNAR MODULE :: GET POSITION
*
*************************************************************************/
Point LunarModule::getPosition() const
{
   return position;
}

/*************************************************************************
* LUNAR MODULE :: hitGround
*
*************************************************************************/
void LunarModule::hitGround()
{
   angle = M_PI;
   landed = true;
}

/*************************************************************************
* LUNAR MODULE :: hitPlatform
*
*************************************************************************/
void LunarModule::hitPlatform()
{
   angle = 0.0;
   landed = true;
}