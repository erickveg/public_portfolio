/***********************************************************************
 * Header File:
 *    Stars : Represents stars in the LM simulation
 * Author:
 *    Br. Helfrich
 * Summary:
 *    A collection of instances of stars with different positions and phases
 ************************************************************************/

#include "star.h"
#include <cassert>

/************************************************************************
 * STAR constructor
 * Create a new star
 ************************************************************************/
Star::Star(const Point& screenSize)
{
   assert(screenSize.getX() > 0.0);
   assert(screenSize.getY() > 0.0);

   double maxX = screenSize.getX();
   double maxY = screenSize.getY();

   setRandomPtStar(maxX, maxY);
   setRandomPhase();
}

/************************************************************************
 * STARS constructor
 * Create a new set of stars
 ************************************************************************/
Stars :: Stars(const Point& screenSize, int numStars) : screenSize(screenSize), numStars(numStars)
{
   createStars(numStars);
}

/************************************************************************
// STARS :: CREATE STARS
// Create n stars, each one has a random position and phase
 ************************************************************************/
void Stars::createStars(int numStars)
{
   for (int i = 0; i < numStars; i++)
   {
      Star s(screenSize);
      multipleStars.push_back(s);
   }
}

/************************************************************************
* STARS :: DRAW
// Display all the starts on the screen
 ************************************************************************/
void Stars::draw(ogstream& gout)

{
   for (int i = 0; i < multipleStars.size(); i++)
   {
      Point star = multipleStars[i].ptStar;
      unsigned char phase = multipleStars[i].phase++;
      gout.drawStar(star, phase);
   }
}