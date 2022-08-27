/***********************************************************************
 * Source File:
 *    Howitzer : Represents the howitzer in the artillery simulation
 * Author:
 *    Team One
 * Summary:
 *    Where the howitzer is located and where the is pointing
 ************************************************************************/

#pragma once

#include "position.h" // For Point
#include "angle.h" // For Point
#include "uiDraw.h"
#include "projectile.h"  // for PROJECTILE

class Howitzer
{
private:
   Position position;
   Angle fireAngle;
   double lastTimeFired;

public:
   Howitzer() : position(Position()), fireAngle(Angle()), lastTimeFired(0.0) {}
   Howitzer(double ptHowitzer): position(ptHowitzer, 0.0), fireAngle(Angle()), lastTimeFired(0.0) {}

   void addAngleRadians(double angle) { fireAngle.addRadians(angle); }

   void fire(Projectile& projectile) 
   {
      if (lastTimeFired > 30.0)
      {
         lastTimeFired = 0.0;
         projectile.setPosition(position);
         projectile.release(fireAngle);
      }
   }
   void draw(ogstream &gout) { gout.drawHowitzer(position, fireAngle.getRadians(), lastTimeFired); }


   // getters
   Angle getAngle() const           { return fireAngle; }

   double getAngleRadians() const   {  return fireAngle.getRadians(); }

   double getAngleDegrees() const   { return fireAngle.getDegrees(); }

   Position getPosition()           {  return position;   }
                                    
   double getElevation() const      {  return position.getMetersY();  }

   double getLastTimeFired() const  {  return lastTimeFired;      }

   double getDistance() const       {  return position.getMetersX();  }

   void setPosition(Position newPos){  position = newPos; }

   void setAngleRadians(double angleRadians) { fireAngle.setRadians(angleRadians); }

   void setAngleDegrees(double angleDegrees) { fireAngle.setDegrees(angleDegrees); }

   void incrementTime(double time)  {  lastTimeFired += time; }

   void reset()                     { lastTimeFired = 0.0; fireAngle = 0.0; }
};