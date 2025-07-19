#include "test.h"
#include "position.h"
#include "simulation.h"
#include "uiInteract.h"

// This changes the number of pixels per meter. Smaller number means larger world map.
double Position::metersFromPixels = 0.035; //.7 WHEN 600, 500

/************************************
 * MAIN
 * There can be only one!
 ************************************/
int main()
{
   // Run tests (if any)
   testRunner();

   // Set up the simulation
	Position pos(70, 50); // 600, 500   this alters the size of the simulation window
   Interface ui("Howitzer Sim", pos);
   Simulator s(pos);

   // Run the UI with callback
   ui.run(Simulator::callBack, &s);

   return 0;
}
