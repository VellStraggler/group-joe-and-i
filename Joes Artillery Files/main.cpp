/***********************************************************************
 * Source File:
 *    MAIN
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Launches the unit tests - that is all!
 ************************************************************************/

#include "test.h"
#include "position.h"
#include "simulation.h"
#include "uiInteract.h"

double Position::metersFromPixels = 5.0;

void callBack(const Interface* pUI, void* p)
{
   Simulator* pSim = static_cast<Simulator*>(p);
   pSim->callBack(pUI, p);
}

/************************************
 * MAIN
 * There can be only one!
 ************************************/
int main()
{
   // run the test code.
   testRunner();
   Position pos(400, 400);
   Interface ui("Howitzer Sim", pos);
   Simulator s = Simulator(pos);

   ui.run(callBack, &s);

   // return success
   return 0;

}