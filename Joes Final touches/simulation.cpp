/**********************************************************************
 * Source File:
 * SIMULATION
 * Author:
 * <your name here>
 * Summary:
 * Execute one simulation of a projectile being fired.
 ************************************************************************/

#include "simulation.h"
#include <iostream>
#include <cmath>

Simulator::Simulator(const Position& posUpperRight)
   : h(0.0, 0.0),
   g(posUpperRight)
{
   p.setWorldBoundary(posUpperRight);
   h.setElevation(M_PI / 4);
   g.reset(h.getPosition());
   p.reset();
   flightTime = 0.0;
}

void Simulator::callBack(const Interface* pUI, void* p)
{
   Simulator* pSim = static_cast<Simulator*>(p);
   pSim->update(pUI);
}

void Simulator::update(const Interface* pUI)
{
   ogstream gout;

   if (isResetting)
   {
      isResetting = false;
      return;
   }

   if (pUI->isRight())
      h.rotate(0.02);
   if (pUI->isLeft())
      h.rotate(-0.02);

   if (p.flightPath.empty())
   {
      std::cout << "Firing at elevation: " << h.getElevation().getRadians()
         << " radians (waiting to fire...)\n";
   }

   if (pUI->isSpace() && p.flightPath.empty())
   {
      double muzzleVelocity = 827.0;
      double angleDegrees = h.getElevation().getDegrees();

      auto [predictedDistance, predictedTime] = simulateProjectile(angleDegrees);
      std::cout << "Predicted distance: " << predictedDistance
         << " meters, hang time: " << predictedTime << " seconds\n";

      p.fire(h.getPosition(), h.getElevation(), muzzleVelocity);

      flightTime = 0.0;
      hasFired = true;
      lastConsoleUpdateTime = 0.0;
   }

   if (pUI->isDown())
   {
      p.reset();
      flightTime = 0.0;
      hasFired = false;
      g.reset(h.getPosition());
      h.setElevation(M_PI / 4);
      isResetting = true;
      lastConsoleUpdateTime = 0.0;
   }

   if (!p.flightPath.empty())
   {
      const double SIM_TIME_STEP = .025;
      p.advance(SIM_TIME_STEP);
      flightTime += SIM_TIME_STEP;

      const double UPDATE_INTERVAL = 0.5;

      if (flightTime - lastConsoleUpdateTime >= UPDATE_INTERVAL)
      {
         std::cout << "\033[2J\033[H\r";

         Position pos = p.flightPath.back().pos;
         Velocity v = p.flightPath.back().v;

         std::cout << "Projectile Data" << std::endl
            << "-------------------" << std::endl
            << "Position:    " << pos.getMetersX() << "m (x), " << pos.getMetersY() << "m (y)" << std::endl
            << "Velocity:    " << v.getSpeed() << "m/s" << std::endl
            << "Altitude:    " << pos.getMetersY() << "m" << std::endl
            << "Flight Time: " << flightTime << "s" << std::endl
            << "Status:      " << "In Flight" << std::endl;

         lastConsoleUpdateTime = flightTime;
      }
   }
   else
   {
      flightTime = 0.0;
   }

   draw(gout);
}

void Simulator::draw(ogstream& gout)
{
   gout.setf(std::ios::fixed | std::ios::showpoint);
   gout.precision(1);

   g.draw(gout);

   double flameDuration = 1.3;
   double flameTime = (hasFired && flightTime < flameDuration) ? flightTime : -1.0;
   h.draw(gout, flameTime);

   if (hasFired && !p.flightPath.empty())
   {
      Position pos = p.flightPath.back().pos;
      gout.drawProjectile(pos, 1.0);

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