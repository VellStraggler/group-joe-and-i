/**********************************************************************
 * Header File:
 * SIMULATION
 * Author:
 * David Wells
 * Summary:
 * Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once
#include "position.h"
#include "howitzer.h"
#include "projectile.h"
#include "uiInteract.h"
#include "ground.h"
#include "simulateProjectile.h"
#include "velocity.h" // Needed for Velocity type in function signature
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
   Simulator(const Position& posUpperRight);
   static void callBack(const Interface* pUI, void* p);
   void update(const Interface* pUI);
   void draw(ogstream& gout);

private:
   Howitzer h;
   Projectile p;
   Ground g;
   double flightTime = 0.0;
   bool hasFired = false;
   bool isResetting = false;
   double lastConsoleUpdateTime = 0.0;
};