#pragma once

#include <iostream>
#include <cassert>
#include "velocity.h"
#define _USE_MATH_DEFINES
#include <math.h>


using namespace std;

class TestVelocity
{
public:
   void run() 
   {
      defaultConstructor();
      nonDefaultConstructor_ones();
      nonDefaultConstructor_unique();
      nonDefaultConstructor_negative();
      nonDefaultConstructor_angle0();
      nonDefaultConstructor_anglePI2();
      computeHorizontalVelocity_positive();
      computeHorizontalVelocity_negative();
      computeHorizontalVelocity_time();
      computeHorizontalVelocity_angle();
      computeVerticalVelocity_positive();
      computeVerticalVelocity_negative();
      computeVerticalVelocity_time();
      computeVerticalVelocity_angle();
      getTotal_positive();
      getTotal_negative();
      getTotal_zero();
      computeMach_0();
      computeMach_1dx();
      computeMach_2dx();
      computeMach_1dy();
      computeMach_2dy();
      getDirection_positive();
      getDirection_negative();
      getDx_1();
      getDx_2();
      getDy_1();
      getDy_2();
   }     

private:

   bool closeEnough(double value, double test, double buffer) const
   {
      double diff = value - test;
      return (diff <= buffer) && (diff >= -buffer);
   }

   void defaultConstructor()
   {
      // setup
      // exercise
      Velocity  vel;

      // verify
      assert(vel.dx == 0.0);
      assert(vel.dy == 0.0);

      // teardown
   }
   void nonDefaultConstructor_ones()
   {
      // setup
      // exercise
      Velocity  vel(1.0, 1.0);

      // verify
      assert(vel.dx == 1.0);
      assert(vel.dy == 1.0);

      // teardown
   }
   void nonDefaultConstructor_unique()
   {
      // setup
      // exercise
      Velocity  vel(1.0, 2.0);

      // verify
      assert(vel.dx == 1.0);
      assert(vel.dy == 2.0);

      // teardown
   }
   void nonDefaultConstructor_negative()
   {
      // setup
      // exercise
      Velocity  vel(-1.0, -2.0);

      // verify
      assert(vel.dx == -1.0);
      assert(vel.dy == -2.0);

      // teardown
   }
   void nonDefaultConstructor_angle0()
   {
      // setup
      // exercise
      Velocity  vel(1.0, Angle(0.0));

      // verify
      assert(vel.dx == 0.0);
      assert(vel.dy == 1.0);

      // teardown
   }
   void nonDefaultConstructor_anglePI2()
   {
      // setup
      // exercise
      Velocity  vel(1.0, Angle(M_PI/2));

      // verify
      //assert(vel.dx == 1.0);
      assert(closeEnough(vel.dx, 1.0, 0.0001));
      //assert(vel.dy == 0.0);
      assert(closeEnough(vel.dy, 0.0, 0.0001));

      // teardown
   }
   void computeHorizontalVelocity_positive()
   {
      // setup
      double angleRadians = 0.0;
      double ddx = 1.0;
      double time = 1.0;

      Velocity vel;
      vel.dx = 0.0;
      vel.dy = 0.0;

// exercise
      vel.computeHorizontalVelocity(angleRadians, ddx, time);

// verify
      assert(vel.dx == 1.0);
      assert(vel.dy == 0.0);
// teardown
   }
   void computeHorizontalVelocity_negative()
   {
      // setup
      double angleRadians = 0.0;
      double ddx = -1.0;
      double time = 1.0;

      Velocity vel;
      vel.dx = 0.0;
      vel.dy = 0.0;

      // exercise
      vel.computeHorizontalVelocity(angleRadians, ddx, time);

      // verify
      assert(vel.dx == -1.0);
      assert(vel.dy == 0.0);
      // teardown
   }
   void computeHorizontalVelocity_time()
   {
      // setup
      double angleRadians = 0.0;
      double ddx = 10.0;
      double time = 0.1;

      Velocity vel;
      vel.dx = 0.0;
      vel.dy = 0.0;

      // exercise
      vel.computeHorizontalVelocity(angleRadians, ddx, time);

      // verify
      assert(vel.dx == 1.0);
      assert(vel.dy == 0.0);
      // teardown
   }
   void computeHorizontalVelocity_angle()
   {
      // setup
      double angleRadians = M_PI/2.0;
      double ddx = 1.0;
      double time = 1.0;

      Velocity vel;
      vel.dx = 0.0;
      vel.dy = 0.0;

      // exercise
      vel.computeHorizontalVelocity(angleRadians, ddx, time);

      // verify
      assert(vel.dx == 1.0);
      assert(vel.dy == 0.0);
      // teardown
   }
   void computeVerticalVelocity_positive()
   {
      // setup
      double angleRadians = 0.0;
      double ddy = 1.0;
      double time = 1.0;

      Velocity vel;
      vel.dx = 0.0;
      vel.dy = 0.0;

      // exercise
      vel.computeVerticalVelocity(angleRadians, ddy, time);

      // verify
      assert(vel.dx == 0.0);
      assert(vel.dy == 1.0);
      // teardown
   }
   void computeVerticalVelocity_negative()
   {
      // setup
      double angleRadians = 0.0;
      double ddy = -1.0;
      double time = 1.0;

      Velocity vel;
      vel.dx = 0.0;
      vel.dy = 0.0;

      // exercise
      vel.computeVerticalVelocity(angleRadians, ddy, time);

      // verify
      assert(vel.dx == 0.0);
      assert(vel.dy == -1.0);
      // teardown
   }
   void computeVerticalVelocity_time()
   {
      // setup
      double angleRadians = 0.0;
      double ddy = 10.0;
      double time = 0.1;

      Velocity vel;
      vel.dx = 0.0;
      vel.dy = 0.0;

      // exercise
      vel.computeVerticalVelocity(angleRadians, ddy, time);

      // verify
      assert(vel.dx == 0.0);
      assert(vel.dy == 1.0);
      // teardown
   }
   void computeVerticalVelocity_angle()
   {
      // setup
      double angleRadians = M_PI / 2.0;
      double ddy = 1.0;
      double time = 1.0;
      double verticalVelocity = -1.0;

      Velocity vel;
      vel.dx = 0.0;
      vel.dy = 0.0;

      // exercise
      verticalVelocity = vel.computeVerticalVelocity(angleRadians, ddy, time);

      // verify
      assert(vel.dx == 0.0); //
      assert(vel.dy == 1.0);
      // teardown
   }
   void getTotal_positive()
   {
      // setup
      Velocity vel;
      vel.dx = 3.0;
      vel.dy = 4.0;
      double totalVel = -1.0;
      // exercise
      totalVel = vel.getTotal();
      // verify
      assert(totalVel == 5.0);
      // teardown
   }
   void getTotal_negative()
   {
      // setup
      Velocity vel;
      vel.dx = -3.0;
      vel.dy = -4.0;
      double totalVel = -1.0;
      // exercise
      totalVel = vel.getTotal();
      // verify
      assert(totalVel == 5.0);
      // teardown
   }
   void getTotal_zero()
   {
      // setup
      Velocity vel;
      vel.dx = 0.0;
      vel.dy = 0.0;
      double totalVel = -1.0;
      // exercise
      totalVel = vel.getTotal();
      // verify
      assert(totalVel == 0.0);
      // teardown
   }
   void computeMach_0()
   {
      // setup
      Velocity vel;
      vel.dx = 0.0;
      vel.dy = 0.0;
      double totalMach = -1.0;
      // exercise
      totalMach = vel.computeMach(340.0);
      // verify
      assert(totalMach == 0.0);
      assert(vel.dx == 0.0);
      assert(vel.dy == 0.0);
      // teardown
   }
   void computeMach_1dx() 
   {
      // setup
      Velocity vel;
      vel.dx = 340.0;
      vel.dy = 0.0;
      double totalMach = -1.0;
      // exercise
      totalMach = vel.computeMach(340.0);
      // verify
      assert(totalMach == 1.0);
      assert(vel.dx == 340.0);
      assert(vel.dy == 0.0);
      // teardown
   }
   void computeMach_2dx()
   {
      // setup
      Velocity vel;
      vel.dx = 680.0;
      vel.dy = 0.0;
      double totalMach = -1.0;
      // exercise
      totalMach = vel.computeMach(340.0);
      // verify
      assert(totalMach == 2.0);
      assert(vel.dx == 680.0);
      assert(vel.dy == 0.0);
      // teardown
   }
   void computeMach_1dy()
   {
      // setup
      Velocity vel;
      vel.dx = 0.0;
      vel.dy = 340.0;
      double totalMach = -1.0;
      // exercise
      totalMach = vel.computeMach(340.0);
      // verify
      assert(totalMach == 1.0);
      assert(vel.dx == 0.0);
      assert(vel.dy == 340.0);
      // teardown
   }
   void computeMach_2dy()
   {
      // setup
      Velocity vel;
      vel.dx = 0.0;
      vel.dy = 680.0;
      double totalMach = -1.0;
      // exercise
      totalMach = vel.computeMach(340.0);
      // verify
      assert(totalMach == 2.0);
      assert(vel.dx == 0.0);
      assert(vel.dy == 680.0);
      // teardown
   }
   void getDirection_positive()
   {
      // setup
      Velocity vel;
      vel.dx = 1.0;
      vel.dy = 1.0;
      double direction = -1.0;
      // exercise
      direction = vel.getDirection();
      
      // verify
      assert(direction == M_PI / 4);
      assert(vel.dx == 1.0);
      assert(vel.dy == 1.0);
      // teardown
   }
   void getDirection_negative()
   {
      // setup
      Velocity vel;
      vel.dx = -1.0;
      vel.dy = -1.0;
      double direction = -1.0;
      // exercise
      direction = vel.getDirection();

      // verify
      assert(direction == 5 * M_PI / 4);
      assert(vel.dx == -1.0);
      assert(vel.dy == -1.0);
      // teardown
   }
   void getDx_1() 
   {
      // setup
      Velocity vel;
      vel.dx = 1.0;
      vel.dy = 1.0;
      double horizontalVelocity = -1.0;
      
      // exercise
      horizontalVelocity = vel.getDx();

      // verify
      assert(horizontalVelocity == 1.0);
      assert(vel.dx == 1.0);
      assert(vel.dy == 1.0);
// teardown
   }
   void getDx_2()
   {
      // setup
      Velocity vel;
      vel.dx = 2.0;
      vel.dy = 2.0;
      double horizontalVelocity = -1.0;

      // exercise
      horizontalVelocity = vel.getDx();

      // verify
      assert(horizontalVelocity == 2.0);
      assert(vel.dx == 2.0);
      assert(vel.dy == 2.0);
      // teardown
   }
   void getDy_1()
   {
      // setup
      Velocity vel;
      vel.dx = 1.0;
      vel.dy = 1.0;
      double verticalVelocity = -1.0;

      // exercise
      verticalVelocity = vel.getDy();

      // verify
      assert(verticalVelocity == 1.0);
      assert(vel.dx == 1.0);
      assert(vel.dy == 1.0);
      // teardown
   }
   void getDy_2()
   {
      // setup
      Velocity vel;
      vel.dx = 2.0;
      vel.dy = 2.0;
      double verticalVelocity = -1.0;

      // exercise
      verticalVelocity = vel.getDy();

      // verify
      assert(verticalVelocity == 2.0);
      assert(vel.dx == 2.0);
      assert(vel.dy == 2.0);
      // teardown
   }
};