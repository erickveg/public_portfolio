/***********************************************************************
 * Header File:
 *    Stars : Represents stars in the LM simulation
 * Author:
 *    Br. Helfrich
 * Summary:
 *    A collection of instances of stars with different positions and phases
 ************************************************************************/

#pragma once

#include "point.h"     // for Point
#include "uiDraw.h"    // for random method      
#include "uiDraw.h"    // for ogstream
#include <vector>
using namespace std;   // for std:vector

/*************************************************************************
 * STAR
 * A single star
 *************************************************************************/
class Star
{
public:
   Point ptStar;
   unsigned char phase;

   // default constructor
   Star(const Point& screenSize);

private:
   //
   void setRandomPtStar(double maxX, double maxY)
   {
      ptStar = Point(random(0.0, maxX), random(0.0, maxY));
   }

   //
   void setRandomPhase()
   {
      phase = random(0, 255);
   }

};

/*************************************************************************
 * STARS 
 * Holds a vector of multiple Star instances
 *************************************************************************/
class Stars
{
private:
   vector <Star> multipleStars;
   Point screenSize;   
   int numStars;

public:
   Stars(const Point& screenSize, int numStars);

   // Create n stars
   void createStars(int numStars);

   // Display all the stars on the screen
   void draw(ogstream& gout);
};