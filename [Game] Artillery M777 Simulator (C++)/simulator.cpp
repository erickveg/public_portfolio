/*************************************************************
 * 1. Name:
 *      Team one
 * 2. Assignment Name:
 *      Lab 13: Artillery Final
 * 3. Assignment Description:
 *      Simulate firing the M777 howitzer 15mm artillery piece
 * 4. What was the hardest part? Be as specific as possible.
 *      ??
 * 5. How long did it take for you to complete the assignment?
 *      ??
 *****************************************************************/

#include <cassert>      // for ASSERT
#include "testRunner.h" // for testRunner
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "ground.h"     // for GROUND
#include "position.h"   // for POSITION
#include "projectile.h" // for PROJECTILE
#include "howitzer.h"   // for HOWITZER

using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Simulator
{
private:
   Ground ground;                 // the ground
   Howitzer howitzer;             // the howitzer
   Projectile projectile;         // the projectile
   Position  ptUpperRight;        // size of the screen

public:
   Simulator(Position ptUpperRight) :
      ptUpperRight(ptUpperRight),
      ground(ptUpperRight),
      howitzer()
   {
      reset();
   }

   void reset()
   {
      Position ptHowitzer;
      ptHowitzer.setPixelsX(Position(this->ptUpperRight).getPixelsX() * random(0.2, 0.8));
      this->ground.reset(ptHowitzer);
      this->howitzer.setPosition(ptHowitzer);
      this->howitzer.reset();
   }

   void drawAll()
   {
      ogstream gout(Position(10.0, this->ptUpperRight.getPixelsY() - 20.0));

      // draw the ground first
      this->ground.draw(gout);

      // draw the howitzer
      this->howitzer.draw(gout);

      // draw the projectile
      this->projectile.draw(gout);

      // draw some text on the screen
      gout.setf(ios::fixed | ios::showpoint);
      gout.precision(1);
      gout << "Time since the bullet was fired: "
         << this->howitzer.getLastTimeFired() << "s\n";
      //gout << "Angle of Howitzer: "
      //   << this->howitzer.getAngleDegrees() << "\n";
   }

   void applyInput(const Interface* pUI)
   {
      if (this->howitzer.getAngleRadians() <= (M_PI / 2.0) || 
          this->howitzer.getAngleRadians() >= (3.0 * M_PI / 2.0))
      {
         // move a large amount
         if (pUI->isRight())
            this->howitzer.addAngleRadians(0.05);

         if (pUI->isLeft())
            this->howitzer.addAngleRadians(-0.05);

         // move by a little
         if (pUI->isUp())
            this->howitzer.addAngleRadians((this->howitzer.getAngleRadians() < M_PI) ? -0.003 : 0.003);

         if (pUI->isDown())
            this->howitzer.addAngleRadians((this->howitzer.getAngleRadians() > M_PI) ? -0.003 : 0.003);
      }
      else
         this->howitzer.setAngleRadians((this->howitzer.getAngleRadians() < M_PI) ? (M_PI / 2.0) : (3.0 * M_PI / 2.0));

      // fire that gun
      if (pUI->isSpace())
         this->howitzer.fire(this->projectile);
   }

   void advanceGame(double time) // Needs cleanup
   {
      // advance time.
      this->howitzer.incrementTime(time);

      // move the projectile across the screen
      this->projectile.nextPosition(time);

      // has the projectile hit the ground?
      if (this->projectile.getAltitude() <= this->ground.getElevationMeters(this->projectile.getPosition()))
      {
         Position target = this->ground.getTarget();
         target.addPixelsX(-5.0);
         double targetMin = target.getMetersX();
         target.addPixelsX(10.0);
         double targetMax = target.getMetersX();
         if (this->projectile.getDistance() >= targetMin &&
             this->projectile.getDistance() <= targetMax)
         {
            this->reset();
         }
         this->projectile.reset();
      }
   }
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Simulator* pSimulator = (Simulator*)p;

   // accept input
   pSimulator->applyInput(pUI);

   // perform all the game logic
   pSimulator->advanceGame(0.5);

   // draw everything
   pSimulator->drawAll();
}

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Run tests
   testRunner();

   Position().setZoom(42.0 /* 42 meters equals 1 pixel */);

   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setPixelsX(700.0);
   ptUpperRight.setPixelsY(500.0);
   Interface ui(0, NULL,
      "Howitzer M777 Simulator",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   Simulator simulator(ptUpperRight);

   // set everything into action
   ui.run(callBack, &simulator);


   return 0;
}