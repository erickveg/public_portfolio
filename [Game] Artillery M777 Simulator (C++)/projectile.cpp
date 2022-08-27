/***********************************************************************
* Header File :
*    Projectile : A projectile/bullet, how it moves and its position
*    Nathan Wood
* Summary :
*    An object that subject to physics
************************************************************************/
//#include "uiDraw.h"   // For ogstream
#include "projectile.h"
#include "table.h"
#include "position.h"
#include "ground.h"
#include <cmath>          // for math defines
#define _USE_MATH_DEFINES // for M_PI
#include <math.h>         // for ATAN2 COS and SIN

/*************************************************************************
* COMPUTE AIR RESISTANCE
*************************************************************************/
double Projectile::computeAirResistance() const
{
   map<double, double> machAndDragCoefficientMap
   {
      {0.300 , 0.1629},
      {0.500 , 0.1659},
      {0.700 , 0.2031},
      {0.890 , 0.2597},
      {0.920 , 0.3010},
      {0.960 , 0.3287},
      {0.980 , 0.4002},
      {1.000 , 0.4258},
      {1.020 , 0.4335},
      {1.060 , 0.4483},
      {1.240 , 0.4064},
      {1.530 , 0.3663},
      {1.990 , 0.2897},
      {2.870 , 0.2297},
      {2.890 , 0.2306},
      {5.000 , 0.2656}
   };
   Table<double> machDragTable(machAndDragCoefficientMap);

   map<double, double> altitudeAndDensityMap
   {
      {0.0 , 1.2250000},
      {1000.0 , 1.1120000},
      {2000.0 , 1.0070000},
      {3000.0 , 0.9093000},
      {4000.0 , 0.8194000},
      {5000.0 , 0.7364000},
      {6000.0 , 0.6601000},
      {7000.0 , 0.5900000},
      {8000.0 , 0.5258000},
      {9000.0 , 0.4671000},
      {10000.0 , 0.4135000},
      {15000.0 , 0.1948000},
      {20000.0 , 0.0889100},
      {25000.0 , 0.0400800},
      {30000.0 , 0.0184100},
      {40000.0 , 0.0039960},
      {50000.0 , 0.0010270},
      {60000.0 , 0.0003097},
      {70000.0 , 0.0000828},
      {80000.0 , 0.0000185}
   };
   Table<double> altitudeDensityTable(altitudeAndDensityMap);

   map <double, double> altitudeAndSpeedSoundMap
   {
      {0.0 , 340.0},
      {1000.0 , 336.0},
      {2000.0 , 332.0},
      {3000.0 , 328.0},
      {4000.0 , 324.0},
      {5000.0 , 320.0},
      {6000.0 , 316.0},
      {7000.0 , 312.0},
      {8000.0 , 308.0},
      {9000.0 , 303.0},
      {10000.0 , 299.0},
      {15000.0 , 295.0},
      {20000.0 , 295.0},
      {25000.0 , 295.0},
      {30000.0 , 305.0},
      {40000.0 , 324.0}
   };
   Table<double> altitudeSpeedSoundTable(altitudeAndSpeedSoundMap);

   double altitude = position.getMetersY();
   double dragCoefficient = machDragTable.interpolate(velocity.computeMach(altitudeSpeedSoundTable.interpolate(altitude)));
   double airDensity = altitudeDensityTable.interpolate(altitude);
   double areaCircle = (M_PI) * ((diameter / 2.0) * (diameter / 2.0));
   // Drag force equation
   return 0.5 * dragCoefficient * airDensity * velocity.getTotal() * velocity.getTotal() * areaCircle;
}


/*************************************************************************
* COMPUTE POSITION
*************************************************************************/
void Projectile::nextPosition(double time)
{
   map <double, double> altitudeAndGravityMap
   {
      {0.0 , 9.807},
      {1000.0 , 9.804},
      {2000.0 , 9.801},
      {3000.0 , 9.797},
      {4000.0 , 9.794},
      {5000.0 , 9.791},
      {6000.0 , 9.788},
      {7000.0 , 9.785},
      {8000.0 , 9.782},
      {9000.0 , 9.779},
      {10000.0 , 9.776},
      {15000.0 , 9.761},
      {20000.0 , 9.745},
      {25000.0 , 9.730}
   };
   Table<double> altitudeGravityTable(altitudeAndGravityMap);

   double gravity = altitudeGravityTable.interpolate(position.getMetersY());
   double angleRadians = getAngle();

   double ddx = 0;
   double ddy = -gravity;

   double dx = velocity.computeHorizontalVelocity(angleRadians, ddx, time);
   double dy = velocity.computeVerticalVelocity(angleRadians, ddy, time);

   applyAirResistance(angleRadians, time);

   double diffX = (dx * time);
   double diffY = (dy * time);

   position.addMetersX(diffX);
   position.addMetersY(diffY);

   addCurrentToTrajectory();
}


bool Projectile::hitGround(Ground& ground)
{
   return hitGround(ground.getElevationMeters(getPosition()));
}

bool Projectile::hitTarget(Ground& ground)
{
   return hitTarget(ground.getElevationMeters(getPosition()), ground.getTarget());
}

bool Projectile::hitGround(double groundElevation)
{
   if (getAltitude() <= groundElevation)
   {
      this->reset();
      return true;
   }
   return false;
}

bool Projectile::hitTarget(double groundElevation, Position targetPxX)
{
   if (hitGround(groundElevation))
   {
      targetPxX.addPixelsX(-5.0);
      double targetMin = targetPxX.getMetersX();
      targetPxX.addPixelsX(10.0);
      double targetMax = targetPxX.getMetersX();
      if (getDistance() >= targetMin &&
          getDistance() <= targetMax)
      {
         return true;
      }
   }
   return false;
}

void Projectile::reset()
{
   flying = false;

   velocity.setDx(0.0);
   velocity.setDy(0.0);

   position.setMeters(0.0, 0.0);

   trajectory.clear();
}

/*************************************************************************
* GET ANGLE
*************************************************************************/
double Projectile::getAngle() const
{
   //return atan2(velocity.getDx(), velocity.getDy()); // Return radians
   return velocity.getDirection();
}

/*************************************************************************
* APPLY AIR RESISTANCE
*************************************************************************/
void Projectile::applyAirResistance(double angleRad, double time)
{
   //if (angleRad == 0) // needs to be fixed
   if (angleRad == 0 && velocity.getDy() < 9.805 && velocity.getDy() > -9.805)
      return;

   double airAcceleration = computeAirResistance() / mass;
   double horizontalAcceleration = airAcceleration * sin(angleRad);
   velocity.setDx(velocity.getDx() - (horizontalAcceleration * time));

   double verticalAcceleration = airAcceleration * cos(angleRad);
   velocity.setDy(velocity.getDy() - (verticalAcceleration * time));
}

void Projectile::addCurrentToTrajectory()
{
   if (trajectory.size() >= 20)
      trajectory.pop_back();
   trajectory.insert(trajectory.begin(), position);
}

void Projectile::draw(ogstream &gout) const
{
   double count = 0;
   for (auto it = trajectory.begin(); it != trajectory.end(); ++it)
   {
      gout.drawProjectile(*it, 0.5 * count++);
   }
}

void Projectile::release(Angle fireAngleRadians)
{
   velocity = Velocity(initialVelocity, fireAngleRadians);
   flying = true;
}