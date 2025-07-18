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

      Velocity v;
      v.set(angle, muzzleVelocity);
      pvt.v = v;
      pvt.t = 1.0;

      flightPath.clear();
      flightPath.push_back(pvt);
   }

   void fire(const Position& pos, double degrees, double muzzleVelocity)
   {
      Angle angle;
      angle.setDegrees(degrees);
      fire(pos, angle, muzzleVelocity);
   }

   // advance the round forward until the next unit of time
   void advance(double simulationTime)
   {
      if (flightPath.empty())
         return;

      PositionVelocityTime prev = flightPath.back();
      PositionVelocityTime next;

      // Gravity
      const double gravity = -9.8064;

      // Step 1: Compute speed
      double speed = sqrt(prev.v.getDx() * prev.v.getDx() + prev.v.getDy() * prev.v.getDy());

      // Step 2: Compute drag force = 0.5 * rho * Cd * A * v^2
      // We'll use approximate constants for now
      double airDensity = 1.225;         // kg/m^3
      double dragCoefficient = 0.47;     // sphere
      double area = M_PI * radius * radius;
      double dragForce = 0.5 * airDensity * dragCoefficient * area * speed * speed;

      // Step 3: Compute drag acceleration components
      double dragAx = (speed > 0.0) ? (-dragForce * prev.v.getDx()) / (mass * speed) : 0.0;
      double dragAy = (speed > 0.0) ? (-dragForce * prev.v.getDy()) / (mass * speed) : 0.0;

      // Step 4: Total acceleration
      Acceleration a;
      a.setDDX(dragAx);
      a.setDDY(gravity + dragAy);

      // Step 5: Update velocity
      next.v.setDx(prev.v.getDx() + a.getDDX());
      next.v.setDy(prev.v.getDy() + a.getDDY());

      // Step 6: Update position
      next.pos.setMetersX(prev.pos.getMetersX() + prev.v.getDx() + 0.5 * a.getDDX());
      next.pos.setMetersY(prev.pos.getMetersY() + prev.v.getDy() + 0.5 * a.getDDY());

      // Step 7: Time advance
      next.t = prev.t + 1.0;

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
};