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


 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
   Simulator(const Position& posUpperRight)
      : h(posUpperRight.getMetersX()/2, 0)
   {
      h.setElevation(0);
      p.fire(h.getPosition(), h.getElevation(), h.getMuzzleVelocity());
      p.advance(1.0);
   }

   void callBack(const Interface* pUI, void* p)
   {
      Simulator* pSim = static_cast<Simulator*>(p);
      ogstream gout;

      // Update your simulation here (advance projectile, etc)
      pSim->p.advance(1.0);

      // Draw howitzer and projectile
      pSim->draw(gout);
   }

   void draw(ogstream& gout)
   {
      h.draw(gout, 1.0);

      if (!p.flightPath.empty())
      {
         gout.drawProjectile(p.flightPath.back().pos, 1.0);
      }
   }

private:
   Howitzer h;
   Projectile p;
};