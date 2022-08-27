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

#pragma once

#define _USE_MATH_DEFINES // for M_PI
#include <math.h>         // for sin and cos

#include <iostream>

/******************************************************
 * ANGLE
 * A single angle
 ******************************************************/
class Angle
{
private:

   double angleRadians;

   // Converts radians to degrees
   double convertToDegrees(double r) const;

   // Convert degrees to radians
   double convertToRadians(double d) const;

   // Get rid of extra rotations in the angle.
   // It will return a value from 0 to 2pi.
   double normalize(double angleRadians) const;

public:
   // default constructor
   Angle()
   {
      angleRadians = 0.0;
   }

   // non-default constructor
   Angle(double d)
   {
      angleRadians = normalize(d);
   }

   // copy constructor
   Angle(const Angle& rhs)
   {
      angleRadians = rhs.angleRadians;
   }

   // assignment operator
   void operator=(const Angle& rhs);

   // negative operator
   Angle operator-();

   // increment prefix
   Angle& operator++();

   // increment postfix
   Angle operator++(int postfix);

   // decrement prefix
   Angle& operator--();

   // decrement postfix
   Angle operator--(int postfix);

   // Get the angle in degrees
   double getDegrees() const
   {
      return convertToDegrees(angleRadians);
   }

   // Get the angle in radians
   double getRadians() const
   {
      return angleRadians;
   }

   // Set a normalized value for angleRadians 
   // when the angle is provided in degrees.
   void setDegrees(double angleDegrees);

   // Set a normalized value for angleRadians
   void setRadians(double angleRadians);

   // Display the value, in degrees, to 1 decimal place of accuracy.
   void display() const;

   // Adds the amount of degrees to the current angle
   void addRadians(double angleRadians);

   // INPUT for ANGLE
   friend std::istream& operator>>(std::istream& in, Angle& rhs)
   {
      double angleDegrees;
      in >> angleDegrees;
      rhs.setDegrees(angleDegrees);
      return in;
   }

   /********************************
    * OUTPUT for ANGLE
    ********************************/
   friend std::ostream& operator<<(std::ostream& out, Angle& rhs)
   {
      out << rhs.getDegrees();
      return out;
   }

   /********************************
    * EQUALS for ANGLE
    ********************************/
   bool operator==(const Angle& rhs)
   {
      return this->getRadians() == rhs.getRadians();
   }

   /********************************
   * NOT EQUALS for ANGLE
   ********************************/
   bool operator!=(const Angle& rhs)
   {
      return this->getRadians() != rhs.getRadians();
   }
};