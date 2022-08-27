/***********************************************************************
* Header File :
*    Projectile : A projectile/bullet, how it moves and its position
*    Nathan Wood
* Summary :
*    An object that subject to physics
************************************************************************/

#pragma once

#include <vector>     // For Vector
#include "position.h" // For Point
#include "velocity.h" // For Velocity
#include "table.h"    // For Table
#include "uiDraw.h"   // For ogstream
#include "ground.h"   // For ogstream

using namespace std;

class TestProjectile;

class Projectile
{
private:
   bool flying;
   Position position;
   Velocity velocity;
   vector<Position> trajectory;
   //Position trajectory[20];
   double mass;
   double diameter;
   double initialVelocity;

   bool hitGround(Ground& ground);
   bool hitGround(double groundElevation);
   double computeAirResistance() const;
   double getAngle() const;
   void applyAirResistance(double angleRad, double time);

   void addCurrentToTrajectory();

public:
   friend TestProjectile;

   // Default Constructor
   Projectile() : flying(false),
                  mass(46.7),
                  initialVelocity(827.0),
                  diameter(0.15489),
                  position(Position(0.0, 0.0)),
                  velocity(Velocity(0.0, 0.0)),
                  trajectory() {}

   void nextPosition(double time);
   void draw(ogstream &gout) const;
   bool hitTarget(Ground& ground);
   bool hitTarget(double groundElevation, Position targetPxX);
   void reset();
   void release(Angle fireAngleRadians);
   bool isFlying()                { return flying; }
   double getDistance()           { return position.getMetersX(); }
   double getAltitude()           { return position.getMetersY(); }
   void setPosition(Position pos) { position = pos; }
   Position getPosition() const   { return position; }
};






