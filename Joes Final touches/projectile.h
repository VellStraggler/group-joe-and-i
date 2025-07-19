/**********************************************************************
 * Header File:
 *    PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/

#pragma once

#include <list>
#include "position.h"
#include "velocity.h"
#include "uiDraw.h"
#include "angle.h"
#include "acceleration.h"

#define DEFAULT_PROJECTILE_WEIGHT 46.7       // kg
#define DEFAULT_PROJECTILE_RADIUS 0.077545   // m

 // forward declaration for the unit test class
class TestProjectile;

/**********************************************************************
 * Projectile
 *    Everything we need to know about a projectile
 ************************************************************************/
class Projectile
{
public:
   // Friend the unit test class
   friend ::TestProjectile;

   // create a new projectile with the default settings
   Projectile() : mass(DEFAULT_PROJECTILE_WEIGHT), radius(DEFAULT_PROJECTILE_RADIUS) {}

   // Function to set the world boundaries
   void setWorldBoundary(const Position& boundary) { worldBoundary = boundary; }


   void reset()
   {
      mass = DEFAULT_PROJECTILE_WEIGHT;
      radius = DEFAULT_PROJECTILE_RADIUS;
      flightPath.clear();
   }

   void fire(const Position& pos, const Angle& angle, double muzzleVelocity)
   {
      PositionVelocityTime pvt;
      pvt.pos = pos;

      if (std::isnan(muzzleVelocity) || std::isinf(muzzleVelocity) || muzzleVelocity <= 0.0)
      {
         std::cerr << "ERROR: Invalid muzzle velocity: " << muzzleVelocity << "\n";
         return;
      }

      Velocity v;
      v.set(angle, muzzleVelocity);  
      pvt.v = v;
      pvt.t = 1.0;

      std::cout << "Firing at elevation: " << angle.getRadians() << " radians\n";
      std::cout << "Speed: " << muzzleVelocity << "\n";

      flightPath.clear();
      flightPath.push_back(pvt);
   }

   // advance the round forward until the next unit of time
   void advance(double simulationTime)
   {
      if (flightPath.empty())
         return;

      PositionVelocityTime prev = flightPath.back();
      PositionVelocityTime next;

      // Debug output for velocity
      std::cout << "Prev pos: " << prev.pos.getMetersX()
         << ", " << prev.pos.getMetersY() << std::endl;

      // Step 1: Acceleration due to gravity and air resistance
      // Assumes drag is always against direction of motion
      Acceleration a;

      // Gravity
      a.setDDY(-9.8064);

      // Simplified air resistance
      double dragX = 0.0;
      if (prev.v.getDX() > 0)
         dragX = -0.0487;
      else if (prev.v.getDX() < 0)
         dragX = 0.0487;

      double dragY = 0.0;
      if (prev.v.getDY() > 0)
         dragY = -0.3893;
      else if (prev.v.getDY() < 0)
         dragY = 0.0638;

      a.setDDX(dragX);

      // Combine
      a.addDDY(dragY); // total vertical = gravity + drag

      // Step 2: New velocity = v + a·t
      next.v = prev.v;
      next.v.add(a, simulationTime);

		// Debug output for velocity
      std::cout << "Velocity: dx=" << next.v.getDX()
         << ", dy=" << next.v.getDY() << std::endl;

      if (std::isnan(next.v.getDX()) || std::isnan(next.v.getDY()))
      {
         std::cerr << "ERROR: Velocity went NaN. Aborting update.\n";
         return;
      }

      // Step 3: New position = p + v·t + ½·a·t²
      next.pos.setMetersX(prev.pos.getMetersX() + prev.v.getDX() * simulationTime + 0.5 * a.getDDX() * simulationTime * simulationTime);
      next.pos.setMetersY(prev.pos.getMetersY() + prev.v.getDY() * simulationTime + 0.5 * a.getDDY() * simulationTime * simulationTime);

      // Step 4: Time
      next.t = simulationTime;

      // End sim if projectile out of range.
      if (next.pos.getMetersY() < 0.0 || next.pos.getMetersY() > worldBoundary.getMetersY() ||
         next.pos.getMetersX() < 0.0 || next.pos.getMetersX() > worldBoundary.getMetersX())
      {
         std::cout << "Projectile out of range. Stopping advance.\n";
         return;
      }

      // Step 5: Store new position
      flightPath.push_back(next);
   }




   // keep track of one moment in the path of the projectile
   struct PositionVelocityTime
   {
      PositionVelocityTime() : pos(), v(), t(0.0) {}
      Position pos;
      Velocity v;
      double t;
   };

   double mass;           // weight of the M795 projectile. Defaults to 46.7 kg
   double radius;         // radius of M795 projectile. Defaults to 0.077545 m
   std::list<PositionVelocityTime> flightPath;

private:
	Position worldBoundary; // The world boundary for the projectile
};