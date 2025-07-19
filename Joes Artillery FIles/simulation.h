/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *    David Wells
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once
#include "position.h"
#include "howitzer.h"
#include "projectile.h"
#include "uiInteract.h"
#include "ground.h"
#include "simulateProjectile.h"

 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
   Simulator(const Position& posUpperRight)
      : h(posUpperRight.getMetersX() / 2, 0),
      g(posUpperRight)
   {
      h.setElevation(M_PI / 4);  // 45 degrees to start Auto target with fire mode
      g.reset(h.getPosition());  // Reset ground using howitzer position
      p.reset();
      flightTime = 0.0;
   }

   // This is the callback UI expects. Must be static.
   static void callBack(const Interface* pUI, void* p)
   {
      Simulator* pSim = static_cast<Simulator*>(p);
      pSim->update(pUI);
   }

   // This is the real-time update logic, fully inside class scope.
   void update(const Interface* pUI)
   {
      ogstream gout;

      // Skip one frame after reset to prevent bad advance
      if (isResetting)
      {
         isResetting = false;
         return;
      }

      // Aiming controls
      if (pUI->isRight())
         h.rotate(0.02);
      if (pUI->isLeft())
         h.rotate(-0.02);

      if (p.flightPath.empty())
      {
         std::cout << "Firing at elevation: " << h.getElevation().getRadians()
            << " radians (waiting to fire...)\n";
      }

      // Fire control
      if (pUI->isSpace() && p.flightPath.empty())
      {
         double muzzleVelocity = 827.0; // currently hardcoded
         double angleDegrees = h.getElevation().getDegrees();

         // Simulate trajectory for diagnostics only
         auto [predictedDistance, predictedTime] = simulateProjectile(angleDegrees);
         std::cout << "Predicted distance: " << predictedDistance
            << " meters, hang time: " << predictedTime << " seconds\n";

         // Fire the projectile for real
         p.fire(h.getPosition(), h.getElevation(), muzzleVelocity);

         flightTime = 0.0;
         hasFired = true;
      }


      // Reset control
      if (pUI->isDown())
      {
         p.reset();
         flightTime = 0.0;
         hasFired = false;
         g.reset(h.getPosition());
         h.setElevation(M_PI / 4);
         isResetting = true;
      }

      // Advance projectile
      if (!p.flightPath.empty())
      {
         const double SIM_TIME_STEP = .025; // simulate 0.1 seconds per frame
         p.advance(SIM_TIME_STEP);
         flightTime += SIM_TIME_STEP;

         // DEBUG: show position
         auto pos = p.flightPath.back().pos;
         std::cout << "Projectile at: " << pos.getMetersX()
            << "m, " << pos.getMetersY() << "m\n";
      }
      else
      {
         flightTime = 0.0;
      }

      draw(gout);
   }

   void draw(ogstream& gout)
   {
      g.draw(gout);

      double flameDuration = 1.3;
      double flameTime = (hasFired && flightTime < flameDuration) ? flightTime : -1.0;
      h.draw(gout, flameTime);

      if (hasFired && !p.flightPath.empty())
      {
         Position pos = p.flightPath.back().pos;
         gout.drawProjectile(pos, 1.0);  // Show shell

         // Simulate flame trail
         if (flightTime < 0.3)
         {
            Position tail = pos;
            double flameLength = 20.0;
            tail.addMetersX(-cos(h.getElevation().getRadians()) * flameLength);
            tail.addMetersY(-sin(h.getElevation().getRadians()) * flameLength);
            gout.drawLine(tail, pos, 1.0, 0.4, 0.0);
         }
      }
   }


private:
   Howitzer h;
   Projectile p;
   Ground g;
   double flightTime = 0.0;
   bool hasFired = false;
   bool isResetting = false;
};
