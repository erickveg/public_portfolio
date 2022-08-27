/***********************************************************************
 * Header File:
 *    Angle : Represents an angle in radians and degrees
 * Author:
 *    Team One
 * Summary:
 *    This class represents an angle and will display the angle in degrees.
 *    The angle can be passed in as radians or degrees.
 *    The program will automatically normalize the angle and store it radians.
 ************************************************************************/

#include <iostream>
#define _USE_MATH_DEFINES // for M_PI
#include <math.h>         // for sin and cos
#include "angle.h"

using namespace std;

/******************************************************
 * ANGLE :: CONVERT TO DEGREES
 * Converts radians to degrees
 ******************************************************/
double Angle::convertToDegrees(double r) const
{
   return (r * 180.0) / M_PI; // return degrees
}

/******************************************************
 * ANGLE :: CONVERT TO RADIANS
 * Convert degrees to radians
 ******************************************************/
double Angle::convertToRadians(double d) const
{
   return (d * 2.0 * M_PI) / 360.0; // return radians
}

/******************************************************
 * ANGLE :: NORMALIZE
 * Get rid of extra rotations in the angle.
 * It will return a value from 0 to 2pi.
 ******************************************************/
double Angle::normalize(double angleRad) const
{
   return angleRad - (floor(angleRad / (2.0 * M_PI)) * (2.0 * M_PI));
}

/******************************************************
 * ANGLE :: SET DEGREES
 * Set a normalized value for angleRadians
 * when the angle is provided in degrees.
 ******************************************************/
void Angle::setDegrees(double angleDegrees)
{
   angleRadians = normalize(convertToRadians(angleDegrees));
}

/******************************************************
 * ANGLE :: SET RADIANS
 * Set a normalized value for angleRadians
 ******************************************************/
void Angle::setRadians(double angleRad)
{
   angleRadians = normalize(angleRad);
}

/******************************************************
 * ANGLE :: DISPLAY
 * Display the value, in degrees, to 1 decimal place of accuracy.
 ******************************************************/
void Angle::display() const
{
   cout.setf(ios::fixed | ios::showpoint);
   cout.precision(1);
   cout << convertToDegrees(angleRadians) << endl;
}

/******************************************************
 * ANGLE :: ADD RADIANS
 * Adds the amount of radians to the current angle
 ******************************************************/
void Angle::addRadians(double angleRad)
{
   angleRadians = normalize(angleRadians + angleRad);
}