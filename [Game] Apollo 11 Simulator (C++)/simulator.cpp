/*************************************************************
 * 1. Name:
 *      Team One
 *      Erick Vega, Nathan Wood, Penelope Sanchez
 * 2. Assignment Name:
 *      Lab 06: Final Submission
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      
 * 5. How long did it take for you to complete the assignment?
 *      
 *****************************************************************/

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include "star.h"
#include "lunarModule.h"
#include "angle.h"

using namespace std;

/*************************************************************************
 * Simulation
 * The structure to handle physics and visuals.
 *************************************************************************/
class Simulation
{
private:
   Point ptUpperRight;   // size of the screen
   Ground ground;
   Stars stars;
   LunarModule LM;       // The Lunar Module

public:
   Simulation(const Point& ptUpperRight) :
      ground(ptUpperRight),
      stars(ptUpperRight, 200),
      LM(Point(ptUpperRight.getX() / 2.0, ptUpperRight.getY() - 50.0))
   { }

   // Displays stars, ground and the LM on the screen
   void drawScene(ogstream& gout, bool isDown, bool isLeft, bool isRight, double time)
   {
      stars.draw(gout);
      ground.draw(gout);
      LM.drawNext(gout, isDown, isLeft, isRight, time);
   }

   void checkCollision()
   {
      if (ground.onPlatform(LM.getPosition(), 20) and LM.getSpeed() <= 4.0 and (LM.getAngleDegrees() <= 15 or LM.getAngleDegrees() >= 345))
      {
         LM.hitPlatform();
      }

      else if (ground.hitGround(LM.getPosition(), 20))
      {
         LM.hitGround();
      }
   }

   int getFuel() const { return (int)LM.getFuel(); }

   int getAngleDegrees() const { return (int)LM.getAngleDegrees(); }

   int getAltitude() const { return (int)LM.getPosition().getY(); }

   int getSpeed() const { return (int)LM.getSpeed(); }

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
   ogstream gout;

   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Simulation* pSimulation = (Simulation*)p;

   pSimulation->checkCollision();
   pSimulation->drawScene(gout, pUI->isDown(), pUI->isLeft(), pUI->isRight(), pUI->frameRate());

   // put some text on the screen
   gout.setPosition(Point(10.0, 370.0));
   gout << "Fuel: " << pSimulation->getFuel() << " lbs" << "\n";
   gout << "Altitude: " << pSimulation->getAltitude() << "meters" "\n";
   gout << "Speed: " << pSimulation->getSpeed() << " m/s" << "\n";
   //gout << "Angle: " << pSimulation->getAngleDegrees() << " degrees" << "\n";
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my Simulation type and call the display engine.
 * That is all!
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
   // Initialize OpenGL
   Point ptUpperRight(400.0, 400.0);
   Interface ui(0, NULL,
      "Open GL Demo",
      ptUpperRight);

   // Initialize the game class
   Simulation simulation(ptUpperRight);

   // set everything into action
   ui.run(callBack, &simulation);

   return 0;
}