#pragma once

#include <iostream>
#include <cassert>
#include "projectile.h"
#define _USE_MATH_DEFINES
#include <math.h>



using namespace std;

class TestProjectile
{
public:
   void run()
   {
      defaultConstructor_nonFlying();
      reset_valid();
      reset_initialState();
      hitGround_true();
      hitGround_false();
      hitTarget_true();
      hitTarget_falseGroundTrue();
      hitTarget_falseGroundFalse();
      isFlying_true();
      isFlying_false();
      computeAirResistance_altitudeZero();
      computeAirResistance_altitudeOne();
      nextPosition_gravity();
      nextPosition_horizontal();
   }

private:
   
   bool closeEnough(double value, double test, double buffer) const
   {
      double diff = value - test;
      return (diff <= buffer) && (diff >= -buffer);
   }

   void defaultConstructor_nonFlying()
   {
      // Assuming this is the very first moment that the projectile is fired
      // setup  
      Projectile shell;
      // exercise
      // verify
      assert(shell.mass == 46.7);
      assert(shell.flying == false);
      assert(shell.trajectory.empty() == true);
      assert(shell.diameter == 0.15489);
      assert(shell.position.x == 0.0);
      assert(shell.position.y == 0.0);
      assert(shell.initialVelocity == 827.0);
      assert(shell.velocity.dx == 0.0);
      assert(shell.velocity.dy == 0.0);
      // teardown
   }

   void reset_valid() const
   {
      //setup
      Projectile shell;
      shell.mass = 46.7;
      shell.flying = 1;
      shell.diameter = 0.15489;
      shell.initialVelocity = 827.0;
      shell.position.x = 653.0;
      shell.position.y = 156.0;
      shell.velocity.dx = 2.0;
      shell.velocity.dy = 4.0;
      shell.trajectory.push_back(Position(2, 3));
      shell.trajectory.push_back(Position(3, 4));
      shell.trajectory.push_back(Position(4, 5));
      shell.trajectory.push_back(Position(5, 6));
      shell.trajectory.push_back(Position(6, 7));
      //excercise
      shell.reset();
      // verify
      assert(shell.mass == 46.7);
      assert(shell.flying == false);
      assert(shell.diameter == 0.15489);
      assert(shell.initialVelocity == 827.0);
      assert(shell.position.x == 0.0);
      assert(shell.position.y == 0.0);
      assert(shell.velocity.dx == 0.0);
      assert(shell.velocity.dy == 0.0);
      assert(shell.trajectory.empty() == true);
      // teardown
   }


   void reset_initialState() const
   {
      //setup
      Projectile shell;
      shell.mass = 46.7;
      shell.flying = 0;
      shell.diameter = 0.15489;
      shell.initialVelocity = 827.0;
      shell.position.x = 0.0;
      shell.position.y = 0.0;
      shell.velocity.dx = 0.0;
      shell.velocity.dy = 0.0;
      shell.trajectory.clear();
      //excercise
      shell.reset();
      // verify
      assert(shell.mass == 46.7);
      assert(shell.flying == 0);
      assert(shell.diameter == 0.15489);
      assert(shell.initialVelocity == 827.0);
      assert(shell.position.x == 0.0);
      assert(shell.position.y == 0.0);
      assert(shell.velocity.dx == 0.0);
      assert(shell.velocity.dy == 0.0);
      assert(shell.trajectory.empty() == true);
      // teardown
   }

   void hitGround_true() const
   {
      //setup
      Projectile shell;
      shell.position.x = 1.0;
      shell.position.y = 0.0;
      bool result;
      // exercise
      result = shell.hitGround(5.0);
      // verify
      assert(result == true);
      assert(shell.position.x == 0.0);
      assert(shell.position.y == 0.0);
      //teardown
   }

   void hitGround_false() const
   {
      //setup
      Projectile shell;
      shell.position.x = 300.0;
      shell.position.y = 300.0;
      bool result;
      // exercise
      result = shell.hitGround(5.0);
      // verify
      assert(result == false);
      assert(shell.position.x == 300.0);
      assert(shell.position.y == 300.0);
      //teardown
   }

   void hitTarget_true() const
   {
      //setup
      Projectile shell;
      shell.position.x = 0.0;
      shell.position.y = 0.0;
      bool result;
      // exercise
      result = shell.hitTarget(5.0, Position(0.0, 0.0));
      // verify
      assert(result == true);
      assert(shell.position.x == 0.0);
      assert(shell.position.y == 0.0);
      //teardown
   }

   void hitTarget_falseGroundTrue() const
   {
      //setup
      Projectile shell;
      shell.position.x = 1.0;
      shell.position.y = 0.0;
      bool result;
      // exercise
      result = shell.hitTarget(5.0, Position(0.0, 0.0));
      // verify
      assert(result == true);
      assert(shell.position.x == 0.0);
      assert(shell.position.y == 0.0);
      //teardown
   }

   void hitTarget_falseGroundFalse() const
   {
      //setup
      Projectile shell;
      shell.position.x = 1.0;
      shell.position.y = 100.0;
      bool result;
      // exercise
      result = shell.hitTarget(5.0, Position(0.0, 0.0));
      // verify
      assert(result == false);
      assert(shell.position.x == 1.0);
      assert(shell.position.y == 100.0);
      //teardown
   }

   void isFlying_true() const
   {
      //setup
      Projectile shell;
      shell.flying = true;
      // exercise
      // verify
      assert(shell.isFlying() == true);
      //teardown
   }

   void isFlying_false() const
   {
      //setup
      Projectile shell;
      shell.flying = false;
      // exercise
      // verify
      assert(shell.isFlying() == false);
      //teardown
   }

   void computeAirResistance_altitudeZero() const
   {
      // setup 
      Projectile shell;
      shell.mass = 46.7;
      shell.flying = true;
      shell.diameter = 0.15489;
      shell.initialVelocity = 827.0;
      shell.position.x = 0.0;
      shell.position.y = 0.0;
      shell.velocity.dx = 340.0;
      shell.velocity.dy = 0.0;
      // exercise
      double airResistance = shell.computeAirResistance();
      // verify 
      assert(closeEnough(airResistance, 568.0757, 0.0001));
      assert(shell.mass == 46.7);
      assert(shell.flying == true);
      assert(shell.diameter == 0.15489);
      assert(shell.initialVelocity == 827.0);
      assert(shell.position.x == 0.0);
      assert(shell.position.y == 0.0);
      assert(shell.velocity.dx == 340.0);
      assert(shell.velocity.dy == 0.0);
   }

   void computeAirResistance_altitudeOne() const
   {
      // setup 
      Projectile shell;
      shell.mass = 46.7;
      shell.flying = true;
      shell.diameter = 0.15489;
      shell.initialVelocity = 827.0;
      shell.position.x = 0.0;
      shell.position.y = 1.0;
      shell.velocity.dx = 827;
      shell.velocity.dy = 0;
      // exercise
      double airResistance = shell.computeAirResistance();
      // verify
      assert(closeEnough(airResistance, 2048.3964, 0.0001));
      assert(shell.mass == 46.7);
      assert(shell.flying == true);
      assert(shell.diameter == 0.15489);
      assert(shell.initialVelocity == 827.0);
      assert(shell.position.x == 0.0);
      assert(shell.position.y == 1.0);
      assert(shell.velocity.dx == 827.0);
      assert(shell.velocity.dy == 0.0);
   }

   void nextPosition_gravity() const
   {
      // setup
      Projectile shell;
      //shell.angle = M_PI / 6; not used
      shell.mass = 46.7;
      shell.flying = true;
      shell.diameter = 0.15489;
      shell.initialVelocity = 827.0;
      shell.position.x = 0.0;
      shell.position.y = 1000.0;
      shell.velocity.dx = 0.0;
      shell.velocity.dy = 0.0;
      // excercise
      shell.nextPosition(1.0);
      // verify
      assert(shell.flying == true);
      assert(closeEnough(shell.position.x, 0.0, 0.0001));
      assert(closeEnough(shell.position.y, 990.196, 0.0001));
      assert(closeEnough(shell.velocity.dx, 0.0, 0.0001));
      assert(closeEnough(shell.velocity.dy, -9.804, 0.0001));
   }

   void nextPosition_horizontal() const
   {
      // setup
      Projectile shell;
      //shell.angle = M_PI / 6; not used
      shell.mass = 46.7;
      shell.flying = true;
      shell.diameter = 0.15489;
      shell.initialVelocity = 827.0;
      shell.position.x = 0.0;
      shell.position.y = 0.0;
      shell.velocity.dx = 340.0;
      shell.velocity.dy = 0.0;
      // excercise
      shell.nextPosition(1.0);
      // verify
      assert(shell.flying == true);
      assert(closeEnough(shell.position.x, 340.0, 0.0001));
      assert(closeEnough(shell.position.y, -9.807, 0.0001));
      assert(closeEnough(shell.velocity.dx, 327.821, 0.0001));
      assert(closeEnough(shell.velocity.dy, -9.807, 0.0001));

   }
};

