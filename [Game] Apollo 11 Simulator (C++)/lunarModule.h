/***********************************************************************
 * Header File:
 *    Lunar Module : Represents the Lunar Module (LM) in the lunar lander simulation
 * Author:
 *    Team One
 * Summary:
 *    Where the LM is located, its next position, and fuel information.
 ************************************************************************/

#pragma once

#include "point.h"     // for Point
#include "velocity.h"  // for Velocity
#include "angle.h"     // for Angle
#include "uiDraw.h"  // for ogstream

/*************************************************************************
* LUNAR MODULE
* The structure to handle physics and visuals specifically for the Lunar Module.
*************************************************************************/
class LunarModule
{
private:
   // Member Attributes
   Point position;
   Velocity velocity;
   Angle angle;
   double fuel;
   double mass;
   bool mainThrust;
   bool clockThrust;
   bool counterThrust;
   bool landed;

   // Private Functions
   void consumeFuel();
   void changeAngleRadians(bool isLeft, bool isRight);
   void computePosition(double time);
   double computeHorizontalAcceleration(double totalThrust) const;
   double computeVerticalAcceleration(double totalThrust) const;

public:
   // Constructor
   LunarModule(Point position);

   // Public methods
   void drawNext(ogstream& gout, bool isDown, bool isLeft, bool isRight, double time);
   double getFuel() const;
   double getAngleDegrees() const;
   double getSpeed() const;
   Point getPosition() const;
   void hitGround();
   void hitPlatform();
   void manageThrust(bool isDown, bool isLeft, bool isRight);
};